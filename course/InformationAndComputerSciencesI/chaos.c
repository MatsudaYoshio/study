#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define logistic(a,x) (a)*(x)*(1-(x))
#define DEFAULT_W_SIZE 800
#define DEFAULT_H_SIZE 800

struct de{
  void(*init)(double a[], double x0[]);
  void(*options)(int argc, char *argv[], double a[], double x0[]);
  void(*map)(double a[], double x0[]);
};

void logistic_init(double a[], double x0[])
{
  a[0] = 4.0;
  x0[0] = 0.314;
}

void logistic_map(double a[], double x0[])
{
  x0[0] = logistic(a[0],x0[0]);
}

void logistic_options(int argc, char *argv[], double a[], double x0[])
{
  int i;
  for(i = 1; i < argc; i++)
    if(strcmp(argv[i], "-a") == 0 && i+1 < argc && atof(argv[i+1]) >= 1 && atof(argv[i+1]) <= 4)
        a[0] = atof(argv[i+1]);
    else if(strcmp(argv[i], "-x0") == 0 && i+1 < argc && atof(argv[i+1]) > 0 && atof(argv[i+1]) < 1)
      x0[0] = atof(argv[i+1]);
}

void segment_init(XSegment s[], double a[], double x0[], struct de *de)
{
  s[0].x2 = s[0].x1 = DEFAULT_W_SIZE*(x0[0]*0.8+0.1);
  s[0].y1 = DEFAULT_H_SIZE*0.9;
  de->map(a, x0);
  s[0].y2 = DEFAULT_H_SIZE*(0.8*(1-x0[0])+0.1);
}

struct de logistic_de = {
  logistic_init, logistic_options, logistic_map,
}, *de = &logistic_de;

struct deset{
  struct de *de;
  double *a, *x0;
  XSegment *s;
  void(*segment_init)(XSegment s[], double a[], double x0[], struct de *de);
};

void HSV2RGB(double h, double s, double v, double *r, double *g, double *b)
{
  double R, G, B;
  double f, i, m, n, k;

  h *= 6;
  f = modf(h, &i);
  m = v*(1 - s);
  n = v*(1 - s*f);
  k = v*(1 - s*(1 - f));
  switch ((int)i) {
  case 0: R = v; G = k; B = m; break;
  case 1: R = n; G = v; B = m; break;
  case 2: R = m; G = v; B = k; break;
  case 3: R = m; G = n; B = v; break;
  case 4: R = k; G = m; B = v; break;
  case 5: R = v; G = m; B = n; break;
  }
  *r = R; *g = G; *b = B;
}

struct view{
  int w, h;
  Display *display;
  int screen_number;
  Window parent_window, window;
  Pixmap pixmap;
  GC gc;
  Colormap cmap;
  XColor colors[1024];
  long event_mask;
  XEvent event;
  KeySym keysym;
};

void view_init(struct view *v)
{
  if (!(v->display = XOpenDisplay(NULL)))
    exit(1);
  v->screen_number = DefaultScreen(v->display);
  v->parent_window = RootWindow(v->display, v->screen_number);
  v->window = XCreateSimpleWindow(v->display, v->parent_window,
                                  0, 0, v->w, v->h, 0,
                                  BlackPixel(v->display, v->screen_number),
                                  WhitePixel(v->display, v->screen_number));
  v->gc = DefaultGC(v->display, v->screen_number);
  v->cmap = DefaultColormap(v->display, v->screen_number);
  {
    int c, ncolors = sizeof(v->colors)/sizeof(XColor);
    for (c = 0; c < ncolors; c++) {
      double R, G, B;
      HSV2RGB((double)c/ncolors, 1, 1, &R, &G, &B);
      v->colors[c].red = 65535*R;
      v->colors[c].green = 65535*G;
      v->colors[c].blue = 65535*B;
      XAllocColor(v->display, v->cmap, &v->colors[c]);
    }
  }
  v->event_mask = ExposureMask;
  v->event_mask |= StructureNotifyMask;
  v->event_mask |= KeyPressMask;
  v->event_mask |= KeyReleaseMask;
  XSelectInput(v->display, v->window, v->event_mask);
  XMapWindow(v->display, v->window);
}

void view_draw(struct view *v, void *o, XSegment *diagonal, int i)
{
  struct deset *des = (struct deset *)o;
  double x;
  int dist = (i) ? abs(des->s->x1 - des->s->x2) : abs(des->s->y1 - des->s->y2); // 線分の長さを距離とする
  XSetForeground(v->display, v->gc, BlackPixel(v->display, v->screen_number));
  
  /* 現在のaの値をウィンドウに出力 */
  char str[10];
  snprintf(str, sizeof(str)/sizeof(char),"a = %.1f", des->a[0]);
  XDrawString(v->display, v->window, v->gc, v->w*0.1, v->h*0.1, str, strlen(str));

  /* ロジスティック写像の描画 */
  for(x = 0.0000; x < 1; x += 0.0001)
    XDrawPoint(v->display, v->window, v->gc, v->w*(x*0.8+0.1), v->h*(0.8*(1-logistic(des->a[0],x))+0.1));

  /* 線分の描画 */
  XSetForeground(v->display, v->gc, (0 <= dist && dist < 1024) ? v->colors[dist].pixel : BlackPixel(v->display, v->screen_number)); // distに応じて色を決める
  XDrawSegments(v->display, v->window, v->gc, des->s, 1);

  /* 対角線の描画 */
  XSetForeground(v->display, v->gc, BlackPixel(v->display,v->screen_number));
  XDrawSegments(v->display, v->window, v->gc, diagonal, 1);
  
  XFlush(v->display);

  /* iに応じて次に描く線分の座標を設定 */
  if(i == 0){
    des->s->x1 = v->h - des->s->y2;
    des->s->y1 = des->s->y2;
  }else{
    des->de->map(des->a, des->x0);
    des->s->x2 = des->s->x1;
    des->s->y2 = v->h*(0.8*(1-des->x0[0])+0.1);
  }
}

void set_diagonal(XSegment *d, int n) // 対角線の座標を設定する関数
{
  d->x1 = n*0.1;
  d->y1 = n*0.9;
  d->x2 = n*0.9;
  d->y2 = n*0.1;
}

void view_loop(struct view *v, void *o)
{
  struct deset *des = (struct deset *)o;
  int i = 0;
  XSegment diagonal[1];
  set_diagonal(diagonal, v->w);
  while(1){
    if(XPending(v->display) > 0){
      XNextEvent(v->display, &v->event);
      switch(v->event.type){
      case KeyPress:
        v->keysym = XkbKeycodeToKeysym(v->display, v->event.xkey.keycode, v->screen_number, v->event.xkey.state & ShiftMask ? 1 : 0);
        switch(v->keysym){
        case XK_space: XClearWindow(v->display, v->window); break; // スペースキーが押されたら描いた線分を全て消す
        case XK_Escape: return; // Escキーが押されたら終了
        case XK_Up: // Upキーが押されたらaを0.1増やす
          des->a[0] = (des->a[0] + 0.1 < 4) ? des->a[0] + 0.1 : 4;
          XClearWindow(v->display, v->window);
          break;
        case XK_Down: // Downキーが押されたらaを0.1減らす
          des->a[0] = (des->a[0] - 0.1 > 1) ? des->a[0] - 0.1 : 1;
          XClearWindow(v->display, v->window);
          break;
        }
        break;
      case ConfigureNotify: // ウィンドウサイズが変わったら再び対角線を設定して描き直す
        v->h = v->w = (v->event.xconfigure.width < v->event.xconfigure.height) ? v->event.xconfigure.width : v->event.xconfigure.height; // 縦と横で小さい方に合わせてウィンドウサイズを決める
        set_diagonal(diagonal, v->w);
        break;
      }
    }else{
      view_draw(v, des, diagonal, i);
      usleep(100 * 1000); // 100ミリ秒スリープ
      i = !i;
    }
  }
}

void view_term(struct view *v)
{
  XUnmapWindow(v->display, v->window);
  XCloseDisplay(v->display);
}

int main(int argc, char *argv[])
{
  struct deset deset = {
    de,
    (double*)malloc(sizeof(double)),
    (double*)malloc(sizeof(double)),
    (XSegment*)malloc(sizeof(XSegment)),
    segment_init
  }, *des = &deset;
  struct view view = {DEFAULT_W_SIZE, DEFAULT_H_SIZE, }, *v = &view;
  
  des->de->init(des->a, des->x0);
  des->de->options(argc, argv, des->a, des->x0);
  des->segment_init(des->s, des->a, des-> x0, des->de);
  view_init(v);
  view_loop(v, des);
  view_term(v);
  
  return 0;
}

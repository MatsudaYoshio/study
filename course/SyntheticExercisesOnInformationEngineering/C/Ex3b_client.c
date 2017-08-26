#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <arpa/inet.h>

#define BUFSIZE 2048
#define LIMITTIME 30 // 制限時間[s]
#define W 50 // 画面サイズ(横)
#define H 20 // 画面サイズ(縦)

typedef struct{
  int x, y;
  char m;
}Player;

typedef struct{
  WINDOW *w;
  Player *p[2];
}Data;

typedef struct{
  Data *d;
  void(*init)(Data *d);
  void(*renew)(Data *d, char *buf, Player *p);
}Game;

static void die(int wp);
void init(Data *d);
void renew(Data *d, char *buf, Player *p);
int isTouch(Player *p1, Player *p2); // 捕まるのかの判定をする
void rShift(Data *d, Player *mp); // 右移動
void lShift(Data *d, Player *mp); // 左移動
void uShift(Data *d, Player *mp); // 上移動
void dShift(Data *d, Player *mp); // 下移動

int main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int socket_fd; // socket() の返すファイル識別子
  struct sockaddr_in server; // サーバプロセスのソケットアドレス情報
  struct hostent *hp; // ホスト情報
  uint16_t port = atoi(argv[2]); // ポート番号
  struct pollfd fds[2];
  int rec;
  char buf[BUFSIZE]; // メッセージを格納するバッファ
  time_t st;
  
  /* ソケットの作成: INET ドメイン・ストリーム型 */
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1){
    perror("client: socket");
    exit(EXIT_FAILURE);
  }
  
  /* サーバプロセスのソケットアドレス情報の設定 */
  memset((void *) &server, 0, sizeof(server)); // アドレス情報構造体の初期化
  server.sin_family = PF_INET; // プロトコルファミリの設定
  server.sin_port = htons(port); // ポート番号の設定
  
  /* hostのIPアドレスを返す */
  if((hp = gethostbyname(argv[1])) == NULL){
    perror("client: gethostbyname");
    exit(EXIT_FAILURE);
  }
  
  memcpy(&server.sin_addr, hp->h_addr_list[0], hp->h_length); // IPアドレスの設定
  
  /* サーバに接続 */
  if(connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) == -1){
    perror("client: connect");
    exit(EXIT_FAILURE);
  }

  /* ファイルディスクリプタをfdsに設定 */
  fds[0].fd = socket_fd; // サーバと接続したソケット
  fds[1].fd = 0; // 標準入力
  fds[0].events = fds[1].events = POLLIN;
  
  Game game = {
    (Data*)malloc(sizeof(Data)),
    init,
    renew
  }, *g = &game;
  
  g->init(g->d);

  st = time(NULL);
  
  while(time(NULL)-st < LIMITTIME){
    rec = poll(fds,2,0); // fdsに設定されたソケットが読み込み可能になるまで待つ
    if(rec == -1){
      puts("Error poll");
      return (-1);
    }
    
    if(fds[0].revents & POLLIN){ // socket_fdに読み込み可能データがある場合
      /* socket_fdからデータを受信して表示 */
      memset(buf, 0, BUFSIZE);
      recv(socket_fd, buf, BUFSIZE, 0);
      g->renew(g->d, buf, g->d->p[1]);
    }
    
    if(fds[1].revents & POLLIN){ // 標準入力があった場合
      /* 標準入力のデータを送信 */
      memset(buf, 0, sizeof(buf));
      buf[0] = getchar();
      write(socket_fd, buf, BUFSIZE);
      g->renew(g->d, buf, g->d->p[0]);
    }
  }
  
  close(socket_fd);

  die(1);
  
  return 0;
}

static void die(int wp)
{
  endwin();
  if(wp == 0) puts("鬼の勝ち");
  else if(wp == 1) puts("子の勝ち");
  exit(0);
}

void init(Data *d)
{
  signal(SIGINT, die);
  
  initscr(); // 画面の初期化
  
  /* 画面の表示 */
  d->w = newwin(H,W,0,0);
  box(d->w,'|','-');
  wrefresh(d->w);

  curs_set(0); // カーソルを表示しない
  
  d->p[0] = (Player*)malloc(sizeof(Player));
  d->p[1] = (Player*)malloc(sizeof(Player));
  
  d->p[0]->x = d->p[0]->y = 1;
  d->p[0]->m = 'o';
  d->p[1]->x = W-2;
  d->p[1]->y = H-2;
  d->p[1]->m = 'x';
  
  /* 始めのカーソルの表示 */
  wmove(d->w, d->p[0]->y, d->p[0]->x);
  waddch(d->w, d->p[0]->m);
  wrefresh(d->w);
  
  wmove(d->w, d->p[1]->y, d->p[1]->x);
  waddch(d->w, d->p[1]->m);
  wrefresh(d->w);
  
  /* バッファリングの中止 */
  cbreak();
  
  /* エコーの中止 */
  noecho();
}

void renew(Data *d, char *buf, Player *p)
{
  if(strcmp(buf, "a") == 0) lShift(d, p);
  else if(strcmp(buf, "d") == 0) rShift(d, p);
  else if(strcmp(buf, "w") == 0) uShift(d, p);
  else if(strcmp(buf, "s") == 0) dShift(d, p);
}

int isTouch(Player *p1, Player *p2)
{
  return (p1->x == p2->x && p1->y == p2->y);
}

void rShift(Data *d, Player *mp)
{
  int i;
  if(mp->x < W-2){
    wmove(d->w, mp->y, mp->x);
    waddch(d->w,' ');
    mp->x++;
    for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
      if(d->p[i] == mp) continue;
      if(isTouch(d->p[i], mp)) die(0);
    }
    wmove(d->w, mp->y, mp->x);
    waddch(d->w, mp->m);
    wrefresh(d->w);
  }
}

void lShift(Data *d, Player *mp)
{
  int i;
  if(mp->x > 1){
    wmove(d->w, mp->y, mp->x);
    waddch(d->w,' ');
    mp->x--;
    for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
      if(d->p[i] == mp) continue;
      if(isTouch(d->p[i], mp)) die(0);
    }
    wmove(d->w, mp->y, mp->x);
    waddch(d->w, mp->m);
    wrefresh(d->w);
  }
}

void uShift(Data *d, Player *mp)
{
  int i;
  if(mp->y > 1){
    wmove(d->w, mp->y, mp->x);
    waddch(d->w,' ');
    mp->y--;
    for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
      if(d->p[i] == mp) continue;
      if(isTouch(d->p[i], mp)) die(0);
    }
    wmove(d->w, mp->y, mp->x);
    waddch(d->w, mp->m);
    wrefresh(d->w);
  }
}

void dShift(Data *d, Player *mp)
{
  int i;
  if(mp->y < H-2){
    wmove(d->w, mp->y, mp->x);
    waddch(d->w,' ');
    mp->y++;
    for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
      if(d->p[i] == mp) continue;
      if(isTouch(d->p[i], mp)) die(0);
    }
    wmove(d->w, mp->y, mp->x);
    waddch(d->w, mp->m);
    wrefresh(d->w);
  }
}

#include <poll.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 2048
#define LIMITTIME 30 // 制限時間[s]
#define W 50 // 画面サイズ(横)
#define H 20 // 画面サイズ(縦)

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const char dn[] = {'d', 's', 'a', 'w'};

typedef struct{
  int x, y, i;
  char c;
}Player;

typedef struct{
  int x, y;
  char c;
}Item;

typedef struct{
  WINDOW *w;
  Player *p[2];
  Item *i;
}Data;

typedef struct{
  Data *d;
  void(*init)(Data *d);
  void(*renew)(Data *d, char *buf, Player *p);
}Game;

static void die(int wp);
void init(Data *d);
void renew(Data *d, char *buf, Player *p);
int isTouch(Player *p1, Player *p2); // 捕まるかの判定を行う
int isGetItem(Player *p, Item *i); // アイテムを取ったかの判定を行う
void rShift(Data *d, Player *mp); // 右移動
void lShift(Data *d, Player *mp); // 左移動
void uShift(Data *d, Player *mp); // 上移動
void dShift(Data *d, Player *mp); // 下移動
char getChaseDir(Player *p1, Player *p2); // 追いかける方向を取る
char getEscapeDir(Player *p1, Player *p2); // 逃げる方向を取る
int irandom(int lb, int ub); // 範囲内の乱数を生成
void permutation(int a[], int n); // ランダムな順列を生成

int main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int listening_socket; // socket() が返すファイル識別子
  int connected_socket; // accept() が返すファイル識別子
  struct sockaddr_in server; // サーバプロセスのソケットアドレス情報
  struct sockaddr_in client; // クライアントプロセスのソケットアドレス情報
  socklen_t fromlen; // クライアントプロセスのソケットアドレス情報の長さ
  uint16_t port = atoi(argv[1]); // ポート番号
  struct pollfd fds[2];
  int rec;
  char buf[BUFSIZE]; // メッセージを格納するバッファ
  int temp = 1;
  time_t st, nt;
  int at;
  int pn, pi;
  struct timeval tm;

  /* 乱数の準備 */
  gettimeofday(&tm, NULL);
  srandom((unsigned)((tm.tv_sec|tm.tv_usec)*getpid()));
  
  // ソケットの作成: INET ドメイン・ストリーム型
  listening_socket = socket(PF_INET, SOCK_STREAM, 0);
  if(listening_socket == -1){
    perror("server: socket");
    exit(EXIT_FAILURE);
  }
  
  /* ソケットオプションの設定 */
  if(setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, (void *) &temp, sizeof(temp))){
    perror("server: setsockopt");
    exit(EXIT_FAILURE);
  }
  
  /* サーバプロセスのソケットアドレス情報の設定 */
  memset((void *) &server, 0, sizeof(server)); // アドレス情報構造体の初期化
  server.sin_family = PF_INET; // プロトコルファミリの設定
  server.sin_port = htons(port); // ポート番号の設定
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  
  /* ソケットにアドレスをバインド */
  if(bind(listening_socket, (struct sockaddr *) &server, sizeof(server)) == -1){
    perror("server: bind");
    exit(EXIT_FAILURE);
  }
  
  /* 接続要求の受け入れ準備 */
  if(listen(listening_socket, 5) == -1){
    perror("server: listen");
    exit(EXIT_FAILURE);
  }
  
  memset((void *) &client, 0, sizeof(client));
  fromlen = sizeof(client);
  /* クライアントからの接続要求を受け入れ、通信経路を確保する
     クライアントと接続したソケットの識別子が connected_socket に格納される */
  connected_socket = accept(listening_socket, (struct sockaddr *) &client, &fromlen);
  if(connected_socket == -1){
    perror("server: accept");
    exit(1);
  }
  
  close(listening_socket);

  /* ファイルディスクリプタをfdsに設定 */
  fds[0].fd = connected_socket; // クライアントと接続したソケット
  fds[1].fd = 0; // 標準入力
  fds[0].events = fds[1].events = POLLIN;

  /* クライアント側への質問 */
  memset(buf, 0, BUFSIZE);
  strcat(buf, "何人で遊びますか？(1~2人)>");
  write(connected_socket, buf, BUFSIZE);
  do{
    memset(buf, 0, BUFSIZE);
    read(connected_socket, buf, BUFSIZE);
    pn = atoi(buf);
    if(pn != 1 && pn != 2){
      memset(buf, 0, BUFSIZE);
      strcat(buf, "error");
      write(connected_socket, buf, BUFSIZE);
    }
  }while(strcmp(buf, "error") == 0);
  
  memset(buf, 0, BUFSIZE);
  strcat(buf, "鬼と子どちらをやりますか？鬼:0 子:1>");
  write(connected_socket, buf, BUFSIZE);
  do{
    memset(buf, 0, BUFSIZE);
    read(connected_socket, buf, BUFSIZE);
    pi = atoi(buf);
    memset(buf, 0, BUFSIZE);
    strcat(buf, (pi == 0 || pi == 1) ? "end" : "error");
    write(connected_socket, buf, BUFSIZE);
  }while(strcmp(buf, "error") == 0);
  
  Game game = {
    (Data*)malloc(sizeof(Data)),
    init,
    renew
  }, *g = &game;
  
  g->init(g->d);

  st = time(NULL);
  while((nt=time(NULL)-st) < LIMITTIME){
    rec = poll(fds,2,0); // fdsに設定されたソケットが読み込み可能になるまで待つ
    if(rec == -1){
      puts("Error poll");
      return (-1);
    }

    if(fds[0].revents & POLLIN){ // connected_socketに読み込み可能データがある場合
      /* connected_socketからデータを受信 */
      memset(buf, 0, BUFSIZE);
      recv(connected_socket, buf, BUFSIZE, 0);
      g->renew(g->d, buf, g->d->p[pi]);
    }
    
    if(pn == 1){
      at %= 700000;
      if(pi == 1 && at++ == 0){ // 自動で追いかける
        memset(buf, 0, BUFSIZE);
        buf[0] = getChaseDir(g->d->p[0], g->d->p[1]);
        write(connected_socket, buf, 1);
        g->renew(g->d, buf, g->d->p[!pi]);
      }else if(pi == 0 && at++ == 0){ // 自動で逃げる
        memset(buf, 0, BUFSIZE);
        buf[0] = getEscapeDir(g->d->p[1], g->d->p[0]);
        write(connected_socket, buf, 1);
        g->renew(g->d, buf, g->d->p[!pi]);
      }
    }else if(pn == 2){
      if(fds[1].revents & POLLIN){ // 標準入力があった場合
        /* 標準入力のデータを送信 */
        memset(buf, 0, BUFSIZE);
        buf[0] = getchar();
        write(connected_socket, buf, 1);
        g->renew(g->d, buf, g->d->p[!pi]);
      }
    }
    
  }
  
  close(connected_socket);

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
  
  /* p[0]が鬼に対応 */
  d->p[0] = (Player*)malloc(sizeof(Player));
  d->p[0]->x = d->p[0]->y = 1;
  d->p[0]->c = 'o';
  d->p[0]->i = 0;

  /* p[1]が子に対応 */
  d->p[1] = (Player*)malloc(sizeof(Player));
  d->p[1]->x = W-2;
  d->p[1]->y = H-2;
  d->p[1]->c = 'x';
  d->p[1]->i = 0;
  
  /* アイテム */
  d->i = (Item*)malloc(sizeof(Item));
  d->i->c = '@';
  d->i->x = d->i->y = 10;
  
  /* 始めのカーソルの表示 */
  wmove(d->w, d->p[0]->y, d->p[0]->x);
  waddch(d->w, d->p[0]->c);
  wrefresh(d->w);
  
  wmove(d->w, d->p[1]->y, d->p[1]->x);
  waddch(d->w, d->p[1]->c);
  wrefresh(d->w);

  wmove(d->w, d->i->y, d->i->x);
  waddch(d->w, d->i->c);
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

int isGetItem(Player *p, Item *i)
{
  return (p->x == i->x && p->y == i->y);
}

void rShift(Data *d, Player *mp)
{
  int i;
  if(mp->i == 0){
    if(mp->x < W-2){
      wmove(d->w, mp->y, mp->x);
      waddch(d->w,' ');
      mp->x++;
      for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
        if(d->p[i] == mp) continue;
        if(isTouch(d->p[i], mp)) die(0);
      }
      wmove(d->w, mp->y, mp->x);
      waddch(d->w, mp->c);
      wrefresh(d->w);
      if(isGetItem(mp, d->i)){
        mp->i = 5;
        d->i->x = d->i->y = -1;
      }
    }
  }else{
    mp->i--;
  }
}

void lShift(Data *d, Player *mp)
{
  int i;
  if(mp->i == 0){
    if(mp->x > 1){
      wmove(d->w, mp->y, mp->x);
      waddch(d->w,' ');
      mp->x--;
      for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
        if(d->p[i] == mp) continue;
        if(isTouch(d->p[i], mp)) die(0);
      }
      wmove(d->w, mp->y, mp->x);
      waddch(d->w, mp->c);
      wrefresh(d->w);
      if(isGetItem(mp, d->i)){
        mp->i = 5;
        d->i->x = d->i->y = -1;
      }
    }
  }else{
    mp->i--;
  }
}

void uShift(Data *d, Player *mp)
{
  int i;
  if(mp->i == 0){
    if(mp->y > 1){
      wmove(d->w, mp->y, mp->x);
      waddch(d->w,' ');
      mp->y--;
      for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
        if(d->p[i] == mp) continue;
        if(isTouch(d->p[i], mp)) die(0);
      }
      wmove(d->w, mp->y, mp->x);
      waddch(d->w, mp->c);
      wrefresh(d->w);
      if(isGetItem(mp, d->i)){
        mp->i = 5;
        d->i->x = d->i->y = -1;
      }
    }
  }else{
    mp->i--;
  }
}

void dShift(Data *d, Player *mp)
{
  int i;
  if(mp->i == 0){
    if(mp->y < H-2){
      wmove(d->w, mp->y, mp->x);
      waddch(d->w,' ');
      mp->y++;
      for(i = 0; i < sizeof(d->p)/sizeof(d->p[0]); i++){
        if(d->p[i] == mp) continue;
        if(isTouch(d->p[i], mp)) die(0);
      }
      wmove(d->w, mp->y, mp->x);
      waddch(d->w, mp->c);
      wrefresh(d->w);
      if(isGetItem(mp, d->i)){
        mp->i = 5;
        d->i->x = d->i->y = -1;
      }
    }
  }else{
    mp->i--;
  }
}

char getChaseDir(Player *p1, Player *p2)
{
  int i, nx, ny, m, d;
  int dd[] = {0, 1, 2, 3};
  permutation(dd,4);
  for(i = 0, m = INT_MAX; i < 4; i++){
    nx = p1->x + dx[dd[i]];
    ny = p1->y + dy[dd[i]];
    if(nx < 1 || nx > W-2 || ny < 1 || ny > H-2) continue;
    if(m > abs(p2->x-nx)+abs(p2->y-ny)){
      m = abs(p2->x-nx)+abs(p2->y-ny);
      d = dd[i];
    }
  }
  return dn[d];
}

char getEscapeDir(Player *p1, Player *p2)
{
  int i, nx, ny, m, d;
  int dd[] = {0, 1, 2, 3};
  permutation(dd,4);
  for(i = 0, m = -1; i < 4; i++){
    nx = p1->x + dx[dd[i]];
    ny = p1->y + dy[dd[i]];
    if(nx < 1 || nx > W-2 || ny < 1 || ny > H-2) continue;
    if(m < abs(p2->x-nx)+abs(p2->y-ny)){
      m = abs(p2->x-nx)+abs(p2->y-ny);
      d = dd[i];
    }
  }
  return dn[d];
}

int irandom(int lb, int ub)
{
  return lb + (random()%(ub - lb + 1));
}

void permutation(int a[], int n)
{
  int i, r, tmp;
  for(i = 0; i < n; i++) a[i] = i;
  for(i = n-1; i > 0; i--){
    r = irandom(0,i);
    tmp = a[r];
    a[r] = a[i];
    a[i] = tmp;
  }
}

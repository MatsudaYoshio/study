#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFSIZE 2048

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
  
  while(1){
    rec = poll(fds,2,-1); // fdsに設定されたソケットが読み込み可能になるまで待つ
    if(rec == -1){
      puts("Error poll");
      return (-1);
    }
    
    if(fds[0].revents & POLLIN){ // socket_fdに読み込み可能データがある場合
      /* socket_fdからデータを受信して表示 */
      memset(buf, 0, BUFSIZE);
      recv(socket_fd, buf, BUFSIZE, 0);
      if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
      printf("%s", buf);
    }
    
    if(fds[1].revents & POLLIN){ // 標準入力があった場合
      /* 標準入力のデータを送信 */
      memset(buf, 0, sizeof(buf));
      read(0, buf, BUFSIZE);
      write(socket_fd, buf, BUFSIZE);
      if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
    }
  }
  
  close(socket_fd);
  
  return 0;
}

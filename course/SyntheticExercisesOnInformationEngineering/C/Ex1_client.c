#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 2048

void chop(char *str);

int main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int socket_fd; // socket() の返すファイル識別子
  struct sockaddr_in server; // サーバプロセスのソケットアドレス情報
  struct hostent *hp; // ホスト情報
  uint16_t port = atoi(argv[2]);; // ポート番号
  char buf[BUFSIZE]; // メッセージを格納するバッファ
  
  // ソケットの作成: INET ドメイン・ストリーム型
  socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1){
    perror("client: socket");
    exit(EXIT_FAILURE);
  }
  
  /* サーバプロセスのソケットアドレス情報の設定 */
  memset((void *) &server, 0, sizeof(server)); // アドレス情報構造体の初期化
  server.sin_family = PF_INET; // プロトコルファミリの設定
  server.sin_port = htons(port); // ポート番号の設定
  
  /* servername のマシンの IP アドレスを返す */
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
  
  while(1){
    /* 送信データを読み込んで送信 */
    memset(buf, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buf, BUFSIZE, stdin) == NULL) break;
    write(socket_fd, buf, BUFSIZE);
    if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
    
    /* 受信データを読み込んで表示 */
    memset(buf, '\0', BUFSIZE);
    read(socket_fd, buf, BUFSIZE);
    if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
    printf("%s", buf);
  }
  
  close(socket_fd);
  
  return 0;
}

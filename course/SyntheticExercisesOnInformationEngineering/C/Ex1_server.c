#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 2048

void chop(char *str);

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
  char buf[BUFSIZE]; // メッセージを格納するバッファ
  int temp = 1;
  
  /* ソケットの作成: INET ドメイン・ストリーム型 */
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
  
  while(1){
    /* 受信データを読み込んで表示 */
    memset(buf, '\0', BUFSIZE);
    read(connected_socket, buf, BUFSIZE);
    if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
    printf("%s", buf);

    /* 送信データを読み込んで送信 */
    memset(buf, '\0', BUFSIZE);
    printf("> ");
    if(fgets(buf, BUFSIZE, stdin) == NULL) break;
    write(connected_socket, buf, BUFSIZE);
    if(strcmp(buf, "bye\n") == 0 || strcmp(buf, "BYE\n") == 0) break;
  }
  
  close(connected_socket);
  
  return 0;
}

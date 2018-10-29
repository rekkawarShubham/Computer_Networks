#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;

#define PORT 8822
#define SERVERADD "127.0.0.1"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int sockfd;

    //create socket
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        die("Socket Error");
    }

    // define structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVERADD);

    int m = connect(sockfd,(struct sockaddr *)&server,sizeof(server));

  int msg_len;
   char a[10];
   bzero((char *)a,sizeof(a));
   cout<<"Enter num 1 \n";
   cin>> a;
   msg_len = send(sockfd,a,9,0);

   char b[10];
   bzero((char *)b,sizeof(b));
   cout<<"Enter num 2 \n";
   cin>> b;
   msg_len = send(sockfd,b,9,0);
   
   char op[2];
   bzero((char *)op,sizeof(op));
   cout<<"Enter Operataor\n";
   cin>> op;
   msg_len = send(sockfd,op,2,0);
   

   char ans[10];
   bzero((char *)ans,sizeof(ans));
   int r = recv(sockfd,ans,9,0);
   cout<<"ANSWER from SERVER" << ans;
 
 return 0;
}

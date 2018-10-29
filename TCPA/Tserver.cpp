#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;
#define PORT 8003


void die(char *s)
{
   perror(s);
   exit(1);
}
int main()
{
    int sockfd;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        die("Socket Creation error");
    }

    ///server struct;

    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);



    if((bind(sockfd,(struct sockaddr *)&server,sizeof(server)))==-1)
    {
            die("Bind error");
    }

if((listen(sockfd,5))<0)
{
	die("Connection failure");
}
     socklen_t cli = sizeof(client);

     int newsock = accept(sockfd,(struct sockaddr *)&client,&cli);
      int m;
      char a[10];
      bzero((char *)a,sizeof(a));
      m = recv(newsock,a,9,0);
      cout << a;

      char b[10];
      bzero((char *)b,sizeof(b));
       m = recv(newsock,b,9,0);
      cout << b;

      char op[10];
      bzero((char *)op,sizeof(op));
       m = recv(newsock,op,2,0);
      cout << op;

      float n1 ,n2,ans=0;
      n1 = atof(a);
      n2 = atof(b);

     switch(op[0])
     {
         case '+':
                   char res[10];
                   bzero((char *)res,sizeof(res));
                   ans = n1 + n2;
                   cout<<"Server Answer :" <<ans;
                   sprintf(res,"%f",ans);
                   send(newsock,res,strlen(res),0);
                   break;

         case '-':
                   char res1[10];
                   bzero((char *)res1,sizeof(res1));
                   ans = n1 - n2;
                   cout<<"Server Answer :"<< ans;
                   sprintf(res1,"%f",ans);
                   send(newsock,res1,strlen(res1),0);
                   break;


         case '*':
                   char res2[10];
                   bzero((char *)res2,sizeof(res2));
                   ans = n1 * n2;
                   cout<<"Server Answer :"<< ans;
                   sprintf(res2,"%f",ans);
                   send(newsock,res2,strlen(res2),0);
                   break;


         case '/':
                   char res3[10];
                   bzero((char *)res3,sizeof(res3));
                   ans = n1 / n2;
                   cout<<"Server Answer :"<< ans;
                   sprintf(res3,"%f",ans);
                   send(newsock,res3,strlen(res3),0);
                   break;

     }

return 0;
}
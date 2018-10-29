#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;
#define PORT 8003
#define SERVERADD "127.0.0.1"

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
          die("Socket Errror");
      }
      //structure;
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(PORT);
      server.sin_addr.s_addr = inet_addr(SERVERADD);
    int m = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    
    char a[10];
    bzero((char *)a,sizeof(a));
    cout<<"\nEnter Number 1 ";
    cin>>a;
    send(sockfd,a,strlen(a),0);

    char b[10];
    bzero((char *)b,sizeof(b));
    cout<<"\nEnter Number 2 ";
    cin>>b;
    send(sockfd,b,strlen(b),0);

char op[2];
    bzero((char *)op,sizeof(op));
	cout<<"\n\tEnter operator:";
	cin>>op;
	send(sockfd,op,strlen(op),0);

char ans[10];
bzero((char *)ans,sizeof(ans));
int z = recv(sockfd,ans,9,0);
cout<<"\nANSWER FROM SERVER : "<<ans;

return 0;

}


//Server
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#define PORT 9991
#define SERV "127.0.0.1"
using namespace std;
void die(char *s)
{
	perror(s);
	exit(1);
}
int main()
{

	//1.Create a socket
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		die("Connection failure");
	}
	//2.DEfine structure

	struct sockaddr_in server;

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr(SERV);


int m=connect(sockfd,(struct sockaddr *)&server,sizeof(server));

	char a[10];
	bzero((char *)a,sizeof(a));
	cout<<"Enter 1 number";
	cin>>a;
send(sockfd,a,strlen(a),0);

	char b[10];
	bzero((char *)b,sizeof(b));
	cout<<"\n\tEnter 2 number :";
	cin>>b;
	send(sockfd,b,strlen(b),0);

	char op[2];

	bzero((char *)op,sizeof(op));
	
	cout<<"\n\tEnter operator:";
	cin>>op;
	send(sockfd,op,strlen(op),0);

	char ans[10];
	bzero((char *)ans,sizeof(ans));
	int n=recv(sockfd,ans,9,0);
	cout<<"\n\tANSWER :"<<ans;

		


		long long int msg_len;
		 char buffer[256];

			{
			 cout<<"\n\tWating for server to send  filename.";
				char filename[100];
				bzero((char *)filename,sizeof(filename));
				msg_len=recv(sockfd,filename,100,0);
				if(msg_len==-1)
					die("Filename error");
				cout<<"\nFilename:"<<filename;


				char *filebuff=new char[90000*80];


				bzero((char *)filebuff,sizeof(filebuff));
				msg_len=recv(sockfd,filebuff,90000*80,0);
				ofstream fout;
				fout.open(filename,ios::out|ios::binary);
				if(!fout)
					die("CANNOT CREATE FILE");
				else
				{
					fout.write(filebuff,msg_len);
					fout.close();
					cout<<"File received";
				}
			}
	return 0;
}
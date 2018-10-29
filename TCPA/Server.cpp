//Server
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>

#define PORT 9991
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

	struct sockaddr_in server,client;

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

if((bind(sockfd,(struct sockaddr *)&server,sizeof(server)))==-1)
{
	die("Connection failure");

}

if((listen(sockfd,5))<0)
{
	die("Connection failure");
}
	socklen_t cli=sizeof(client);
	int newsock=accept(sockfd,(struct sockaddr*)&client,&cli);

	char a[10];
	bzero((char *)a,sizeof(a));
	int m=recv(newsock,a,9,0);
	cout<<a;

	char b[10];
	bzero((char *)b,sizeof(b));
	int n=recv(newsock,b,9,0);
	cout<<b;

	char op[10];

	bzero((char *)op,sizeof(op));
	int p=recv(newsock,op,2,0);
	cout<<op;

	int n1,n2,res=0;
	n1=atof(a);
	n2=atof(b);

float ans1;
	switch(op[0])
	{
		case '+':
			
			char ans[20];
			ans1=n1+n2;
			cout<<"THe ans1 is "<<ans1<<endl;
			bzero((char *)ans,sizeof(ans));
			sprintf(ans,"%f",ans1);
			send(newsock,ans,strlen(ans),0);
			break;


					
		case '-':
		{


					char ans[10];
					ans1=n1-n2;


					cout<<"\n\tResult :"<<n1-n2;
					bzero((char *)ans,sizeof(ans));
					sprintf(ans,"%f",ans1);
					send(newsock,ans,strlen(ans),0);

					break;
		}
		case '*':
					cout<<"\n\tResult :"<<n1*n2;
					break;
		case '/':
					cout<<"\n\tResult :"<<n1/n2;
					break;
	
						
	}
		long long int msg_len;
	{
		cout<<"\nENter Filename:";
		char filename[100];
		cin>>filename;
		cout<<filename;
		fstream fout;



		msg_len=send(newsock,filename,100,0); //send filename
		if(msg_len==-1)
			die("Filename error");

		fout.open(filename,ios::in|ios::out|ios::binary);
				fout.seekg(0,ios::end);
				long long int filesize=fout.tellg(); //get file size
				char *filebuff=new char[filesize];
				fout.seekg(0,ios::beg);
				fout.read(filebuff,filesize); //reading file content



		msg_len=send(newsock,filebuff,filesize,0); //send file conetents
		if(msg_len==-1)
			die("File transmission error");
		else
			cout<<"Transmission Successful";
		fout.close();
	}
	


	return 0;

}
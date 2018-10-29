#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
#define PORT 8999

void die(char *s)
{
	perror(s);
	exit(1);
}
int main()
{
	cout<<"\n\tHello...This is Server";
	struct sockaddr_in sserver,client;
	//1.CREATE A SOCKET
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
			die("SOCKET CREATE ERROR");
	}
	//2.SERVER STRUCTURE
	sserver.sin_family=AF_INET;
	sserver.sin_port=htons(PORT);
	sserver.sin_addr.s_addr=htonl(INADDR_ANY);

	//3.BIND 

	if(bind(sockfd,(struct sockaddr *)&sserver,sizeof(sserver))==-1)
	{
		die("BIND ERROR");
	}
	else
	{
		cout<<"UDP SERVER startted";
	}

int msg_len;
socklen_t cli=sizeof(client);
int cli_len=sizeof(client);
char buffer[1000];

//RECEIVE FROM client
msg_len=recvfrom(sockfd,buffer,1000,0,(struct sockaddr *)&client,&cli);
if(msg_len>0)
{
	cout<<"\n\tCLIENT :-"<<buffer;
	bzero((char *)buffer,sizeof(buffer));
}
int ch;
cout<<"\n\tCONNECTION PROPERLY ESTABLISHED";
do
{
cout<<"\n\t--------------------------------------------------------------------";
cout<<"\n\t1.SEND FILE\n\t2.RECEIVE FILE\n\t3.EXIT";
cin>>ch;
switch(ch)
{
	case 1:
		{
			char filename[100];
			cout<<"\n\tEnter the file name";
			cin>>filename;
			fstream fout;
			fout.open(filename,ios::in|ios::out|ios::binary);
			fout.seekg(0,ios::end);
			int filesize=fout.tellg();
			char *filebuf=new char[filesize];
			fout.seekg(0,ios::beg);
			fout.read(filebuf,filesize);
			//send filename
			msg_len=sendto(sockfd,filename,strlen(filename),0,(struct sockaddr*)&client,cli_len);
			if(msg_len==-1)
					die("filename error");
			msg_len=sendto(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client,cli_len);
			if(msg_len==-1)
					die("filesize error");

				//send contents
			msg_len=sendto(sockfd,filebuf,filesize,0,(struct sockaddr *)&client,cli_len);
			if(msg_len==-1)
					die("file transmission error");
			else
				cout<<"\n\tTRANSMISSION SUCCESSFULL";


		}
		break;
		case 2:
		{
			char filename[100];
			bzero((char *)filename,sizeof(filename));
			msg_len=recvfrom(sockfd,filename,99,0,(struct sockaddr *)&client,&cli);
			cout<<"\n\tFile name:"<<filename;
			int filesize;

			msg_len=recvfrom(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client,&cli);
			cout<<"\n\tFile Size :"<<filesize;
			char *filebuff=new char[filesize];
			bzero((char *)filebuff,sizeof(filebuff));
			msg_len=recvfrom(sockfd,filebuff,filesize,0,(struct sockaddr *)&client,&cli);

			ofstream fout;
			fout.open(filename,ios::out | ios::binary);
			if(!fout)
					die("FILE NOT TRANSMITTED");
			else
			{
					fout.write(filebuff,filesize);
					fout.close();
					cout<<"\n\tFILE RECEIVED";
			}
		}
		break;
	
}

}while(ch!=3);

	return 0;
}
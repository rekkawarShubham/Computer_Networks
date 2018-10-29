#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
#define PORT 8999
#define SERVERADD "127.0.0.1"
void die(char * s)
{
	perror(s);
	exit(1);
}
int main()
{
	int sockfd;
	struct sockaddr_in saddress;
	//1.CREATE A SOCKET

	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		die("SOCKET ERROR");
	}

	saddress.sin_family=AF_INET;
	saddress.sin_port=htons(PORT);
	saddress.sin_addr.s_addr=inet_addr(SERVERADD);
//----SEND HELLO TO THE SERVER
	int msg_len;
	socklen_t cli=sizeof(saddress);
	int slen=sizeof(saddress);
	char buffer[1000];

	cout<<"\n\tEnter the message for server";
	cin.getline(buffer,sizeof(buffer));


	msg_len=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&saddress,slen);
cout<<"\n\tCONNECTION PROPERLY ESTABLISHED";
int ch;
do
{
cout<<"\n\t--------------------------------------------------------------------";
cout<<"\n\t1.SEND FILE\n\t2.RECEIVE FILE\n\t3.EXIT";
cin>>ch;
switch(ch)
{
	case 1:
			{
				cout<<"\n\t________________SEND FILE TO SERVER______________________________";
				char filename[100];
				cout<<"\n\tEnter the file name :";
				cin>>filename;
				fstream fout;
				fout.open(filename,ios::in |ios::out|ios::binary);
				fout.seekg(0,ios::end);
				int filesize;
				filesize=fout.tellg();
				fout.seekg(0,ios::beg);
				char *filebuff=new char[filesize];

				fout.read(filebuff,filesize);
				//send the file name
				msg_len=sendto(sockfd,filename,strlen(filename),0,(struct sockaddr *)&saddress,slen);
				if(msg_len==-1)
						die("FILENAME ERROR");
				//send file size
				msg_len=sendto(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&saddress,slen);
				if(msg_len==-1)
						die("FILESIZE ERROR");
				
			//send contents
				msg_len=sendto(sockfd,filebuff,filesize,0,(struct sockaddr *)&saddress,slen);
				if(msg_len==-1)
						die("FILE TRANSMITTED ERROR");
				else
						die("FILE TRANSMITTED");

			}
			break;





	case 2:
		{
			char filename[100];
			bzero((char *)filename,sizeof(filename));
			msg_len=recvfrom(sockfd,filename,99,0,(struct sockaddr *)&saddress,&cli);
			cout<<"\n\tFile name:"<<filename;
			int filesize;

			msg_len=recvfrom(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&saddress,&cli);
			cout<<"\n\tFile Size :"<<filesize;
			char *filebuff=new char[filesize];
			bzero((char *)filebuff,sizeof(filebuff));
			msg_len=recvfrom(sockfd,filebuff,filesize,0,(struct sockaddr *)&saddress,&cli);

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
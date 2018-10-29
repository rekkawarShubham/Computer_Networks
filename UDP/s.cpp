#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
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
   struct sockaddr_in server,client;

   //1. create socket
   int sockfd;
   if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
   {
       die("socket error");
   }
   //2. server structure

   server.sin_family=AF_INET;
   server.sin_port=htons(PORT);
   server.sin_addr.s_addr=htonl(INADDR_ANY);
   
   // 3. bind

   if(bind(sockfd,(struct sockaddr *)&server,sizeof(server))==-1)
   {
       die("bind error");
   }
   else{
       cout<<"Server started";
   }
           
   int msg_len;
   socklen_t cli =sizeof(client);
   int cli_len = sizeof(client);
   char buffer[1000];

     msg_len = recvfrom(sockfd,buffer,1000,0,(struct sockaddr*)&client,&cli);
       if(msg_len > 0)
            {
                cout<<"\n Client :"<< buffer;
                bzero((char *)buffer,sizeof(buffer));
            }
    
    int ch;

    do{
        cout<<"\n1. Send \n 2.Receive \n 3. Exit\n";
        cin>>ch;

        switch(ch){
            case 1:
                {
                    char filename[100];
                    int filesize;
                    cout<<"Enter the filename";
                    cin>>filename;
                    fstream fout;
                    fout.open(filename,ios::out|ios::in|ios::binary);
                     fout.seekg(0,ios::end);
                     filesize = fout.tellg();
                     char *filebuf =  new char[filesize];
                     fout.seekg(0,ios::beg);
                     fout.read(filebuf,filesize);
                     msg_len = sendto(sockfd,filename,strlen(filename),0,(struct sockaddr *)&client,cli_len);
                        if(msg_len == -1)
                          cout<<"filename error";
                     msg_len = sendto(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client,cli_len);
                        if(msg_len == -1)
                          cout<<"filesize error";
                     msg_len = sendto(sockfd,filebuf,filesize,0,(struct sockaddr *)&client,cli_len);
                        if(msg_len == -1)
                          cout<<"buffer error";

                    else
                        cout<<"File transmited";
                }
                break;
            case 2:
                                    {
                          char filename[100];
                          bzero((char *)filename,sizeof(filename));
                          msg_len = recvfrom(sockfd,filename,99,0,(struct sockaddr *)&client,&cli);
                            if(msg_len == -1)
                               die("Filename error");
                         cout<<"Filename "<<filename;

                         int filesize;
                          msg_len = recvfrom(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client,&cli);
                          cout<<"File Size "<<filesize;
                          char *filebuffer = new char[filesize];
                          msg_len = recvfrom(sockfd,filebuffer,filesize,0,(struct sockaddr*)&client,&cli);

                            ofstream fout;
                            fout.open(filename,ios::out|ios::binary);

                            if(!fout)
                               die("file open error");
                            else{
                                fout.write(filebuffer,filesize);
                                fout.close();;
                                cout<<"file recieved succesfully";
                            }

                        }
                        break;

        }
    }while(ch!=3);

}


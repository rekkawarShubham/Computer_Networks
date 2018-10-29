#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;
#define PORT 8001

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int sockfd;

    //  1.Create socket
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
        die("Socket Error");
    }

    // 2. server structure
    struct sockaddr_in server,client;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // 3 .Bind

      if((bind(sockfd,(struct sockaddr*)&server,sizeof(server)))==-1)
      {
          die("bind error");
      }

    int msg_len;
    socklen_t cli = sizeof(client);
    int cli_len = sizeof(client);
    char buffer[1000];

    msg_len = recvfrom(sockfd,buffer,1000,0,(struct sockaddr *)&client,&cli);

    if(msg_len == -1)
       die("havnt received");
    else{
       cout<<"Message from client : "<<buffer;
        bzero((char *)buffer,sizeof(buffer));
     }

     int ch;
     do{

         cout << "1. Receive 2. Send 3.ezdxirt \n";
         cin >> ch;
         
         switch (ch)
         {
             case 1:
             {
                 fstream fout;
                 char filename[100];
                 int msg_len;
                 msg_len = recvfrom(sockfd, filename,99, 0 , (struct sockaddr*)&client, &cli);
                 if(msg_len == -1){
                     die("Filename erreoee");
                 }
                 cout << filename;
                 int filesize;
                msg_len = recvfrom(sockfd, (void *)&filesize, sizeof(filesize), 0 , (struct sockaddr*)&client, &cli);
                 if(msg_len == -1){
                     die("Filesize erreoee");
                 }
                 cout << filesize;
                 char* buffer = new char[filesize];
                 msg_len = recvfrom(sockfd, buffer, filesize, 0 , (struct sockaddr*)&client, &cli);
                 if(msg_len == -1){
                     die("Filebuffer erreoee");
                 }
                 
                 fout.open(filename,ios::binary | ios::out);
                 if(!fout){
                     die("File nahi open");
                 }
                 else{

                    fout.write(buffer, filesize);
                    fout.close();
                    
                 }
             }
                 break;
         
             default:
                 break;
         }

     }while(ch!=3);
  return 0;
}

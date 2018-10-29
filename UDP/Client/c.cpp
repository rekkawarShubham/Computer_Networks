#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fstream>

using namespace std;
#define PORT 8001
#define SERVERADD "127.0.0.1"

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
     
     struct sockaddr_in sadd;
     int sockfd;

     // 1. Create socket
     if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
         die("Socket Create error");
     }


     // 2. server structure

     sadd.sin_family = AF_INET;
     sadd.sin_port = htons(PORT);
     sadd.sin_addr.s_addr = inet_addr(SERVERADD);

    // send msg to server
     
     int msg_len;
     socklen_t cli = sizeof(sadd);
     int slen = sizeof(sadd);
     char buffer[1000];
     cout<<"\nEnter Message to server \n";
     cin.getline(buffer,sizeof(buffer));

      msg_len = sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&sadd,slen);
      if(msg_len == -1)
        die("Sending Error");

      int ch;

      do{
          cout<<"\n1.Receive \n2. Send \n3. Exit\n";
          cin>>ch;
          switch(ch)
          {
                case 1:
                        {
                          char filename[100];
                          bzero((char *)filename,sizeof(filename));
                          msg_len = recvfrom(sockfd,filename,99,0,(struct sockaddr *)&sadd,&cli);
                            if(msg_len == -1)
                               die("Filename error");
                         cout<<"Filename "<<filename;

                         int filesize;
                          msg_len = recvfrom(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&sadd,&cli);
                          cout<<"File Size "<<filesize;
                          char *filebuffer = new char[filesize];
                          msg_len = recvfrom(sockfd,filebuffer,filesize,0,(struct sockaddr*)&sadd,&cli);

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
                case 2:
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
                     msg_len = sendto(sockfd,filename,strlen(filename),0,(struct sockaddr *)&sadd,slen);
                        if(msg_len == -1)
                          cout<<"filename error";
                     msg_len = sendto(sockfd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&sadd,slen);
                        if(msg_len == -1)
                          cout<<"filesize error";
                     msg_len = sendto(sockfd,filebuf,filesize,0,(struct sockaddr *)&sadd,slen);
                        if(msg_len == -1)
                          cout<<"buffer error";

                    else
                        cout<<"File transmited";
                }
                break;

          }

      }while(ch!=3);
}
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

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

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {

        die("Socket error");
    }

    //define structure

    sadd.sin_family = AF_INET;
    sadd.sin_port = htons(PORT);
    sadd.sin_addr.s_addr = inet_addr(SERVERADD);

    int msg_len;
    socklen_t cli = sizeof(sadd);
    int slen = sizeof(sadd);
    cout << "Enter msg to send\n";
    char buffer[1000];
    bzero((char *)buffer, sizeof(buffer));
    cin.getline(buffer, sizeof(buffer));
    msg_len = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&sadd, slen);

    if (msg_len == -1)
    {
        die("Error");
    }

    else
    {
        cout << "Succecsfhuvd";
    }

    int ch;
    do
    {

        cout << "1. Send 2. Recve 3.ezdxirt \n";
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            char filename[100];
            cout << "Enter the file name \n";
            cin >> filename;
            fstream fout;
            fout.open(filename, ios::binary | ios::in);
            fout.seekg(0,ios::end); 
            int filesize = fout.tellg();
            char* buff = new char[filesize];
            fout.seekg(0,ios::beg);
            fout.read(buff, filesize);
            int msg_len;
            msg_len = sendto(sockfd, filename, 99, 0, (struct sockaddr*)&sadd, slen);
            if (msg_len == -1)
                die("Filename cha error"); 
          
            msg_len = sendto(sockfd, (void *)&filesize, sizeof(filesize), 0, (struct sockaddr*)&sadd, slen);
            if (msg_len == -1)
                die("Filesize cha error");

            
            msg_len = sendto(sockfd, buff, filesize, 0, (struct sockaddr*)&sadd, slen);
            if (msg_len == -1)
                die("bufff cha error");
            
            else
            {
               cout << "Sexess";
            }
            
        }
        break;

        default:
            break;
        }

    } while (ch != 3);
}

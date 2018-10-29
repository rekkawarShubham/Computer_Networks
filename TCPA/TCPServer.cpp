#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 8822

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        die("Socket Create error");
    }

    // server structure
    struct sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind

    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) == -1)
    {
        die("Bind error");
    }

    if (listen(sockfd, 5) < 0)
    {
        die("Connection Failure");
    }
    socklen_t cli = sizeof(client);

    int newsock = accept(sockfd, (struct sockaddr *)&client, &cli);

    int m;
    char a[10];
    bzero((char *)a, sizeof(a));
    m = recv(newsock, a, 9, 0);
    cout << "Number 1 is " << a;

    char b[10];
    bzero((char *)b, sizeof(b));
    m = recv(newsock, b, 9, 0);
    cout << "Number 2 is " << b;

    char op[10];
    bzero((char *)op, sizeof(op));
    m = recv(newsock, op,9, 0);
    cout << "operator :" << op;

    float ans, n1, n2;
    n1 = atof(a);
    n2 = atof(b);

    switch (op[0])
    {
    case '+':
    {
        char res[10];
        bzero((char *)res, sizeof(res));
        ans = n1 + n2;
        sprintf(res, "%f", ans);
        send(newsock, res, 9, 0);
    }
        break;
    case '-':
    {
        char res[10];
        bzero((char *)&res, sizeof(res));
        ans = n1 - n2;
        sprintf(res, "%f", ans);
        send(newsock, res, 9, 0 );
        break;
    }
    }
    return 0;
}

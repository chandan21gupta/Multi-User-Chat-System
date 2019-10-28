#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void error_print(int error_num)
{
    printf("error_print: %s\n",strerror(error_num));
    exit(1);
}

void main ()
{
    int server_fd; 
    struct sockaddr_in serv_addr;
    char buffer[256];

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) 
        error_print(errno);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <= 0) 
        error_print(errno);
        
    if(connect(server_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error_print(errno);

    scanf("%s",buffer);
    if(strcmp(buffer,"EXIT") == 0)
        exit(1);
    else if(strcmp(buffer,"SEND") == 0) 
    {
        send(server_fd,buffer,1024,0);
        scanf("%s",buffer);
        send(server_fd,buffer,1024,0);
        scanf("%[^\n]s",buffer);
        send(server_fd,buffer,1024,0);
    }
}
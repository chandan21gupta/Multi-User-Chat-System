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

void main()
{
    int server_fd; 
    int client_fd;
    int clilen;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    char buffer[256];
    int data_status;
    int addrlen = sizeof(serv_addr);

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) 
        error_print(errno);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error_print(errno);
    
    listen(server_fd,5);

    clilen = sizeof(cli_addr);

    client_fd = accept(server_fd,(struct sockaddr *)&serv_addr,(socklen_t *)&addrlen);
    if(client_fd < 0)
        error_print(errno);
   
    data_status = read(client_fd,buffer,255);
    if(data_status < 0)
        error_print(errno);
    data_status = write(client_fd,"I got your message",18);
    if(data_status < 0)
        error_print(errno);
}
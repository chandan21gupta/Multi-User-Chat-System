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
    if(server_fd = socket(AF_INET,SOCK_STREAM,0) < 0)
        error_print(errno);
    if(bind(server_fd,(struct sockadd *)&serv_addr,sizeof(serv_addr)) < 0)
        error_print(errno);
}
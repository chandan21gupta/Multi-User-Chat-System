#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define PORT 8080

void error_print(int error_num)
{
    printf("error_print: %s\n",strerror(error_num));
    exit(1);
}

void *receive(void *socket_fd)
{
    int server_fd = *((int *)socket_fd);
    while(1)
    {
        char buffer[256];
        int data_status = recv(server_fd,buffer,256,0);
        if(data_status < 0)
            error_print(errno);
        buffer[data_status] = '\0';
        printf("%s\n",buffer);
        data_status = recv(server_fd,buffer,256,0);
        if(data_status < 0)
            error_print(errno);
        buffer[data_status] = '\0';
        printf("%s\n",buffer);
    }
}

void send_data(int server_fd,char buffer[])
{
    send(server_fd,buffer,256,0);
    scanf("%s",buffer);
    send(server_fd,buffer,256,0);
    scanf("%[^\n]s",buffer);
    send(server_fd,buffer,256,0);
}

void main ()
{
    int server_fd; 
    struct sockaddr_in serv_addr;

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) 
        error_print(errno);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <= 0) 
        error_print(errno);
        
    if(connect(server_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error_print(errno);

    pthread_t thread;
    pthread_create(&thread,NULL,receive,(void *)&server_fd);

    while(1)
    {
        char buffer[256];
        scanf("%s",buffer);

        if(strcmp(buffer,"EXIT") == 0)
        {
            send(server_fd,"EXIT",4,0);
            exit(1);
        }
        else if(strcmp(buffer,"LIST") == 0)
        {
            send(server_fd,"LIST",4,0);
        }
        else
        {   
            send_data(server_fd,buffer);
        }
    }
}
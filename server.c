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
    int server_fd;                      /*server side socket descriptor*/
    int client_fd;                      /*client side socket descriptor*/
    struct sockaddr_in serv_addr;       /*server address structure*/
    char buffer[256];                   /*buffer for containing incoming and outgoing messages*/
    int data_status;                    /*status of reading and writing data*/
    int adddress_len = sizeof(serv_addr); /*storing the size of the server address in bytes*/

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)  /*creating server side socket*/
        error_print(errno);

    serv_addr.sin_family = AF_INET;             
    serv_addr.sin_addr.s_addr = INADDR_ANY;     /*specifying the configuration for the server address*/
    serv_addr.sin_port = htons(PORT);           

    if(bind(server_fd,(struct sockaddr *)&serv_addr,adddress_len) < 0)  /*binding the created socket to the address*/
        error_print(errno);
    
    listen(server_fd,5);   /*telling the server to listen to any incoming collections*/

    client_fd = accept(server_fd,(struct sockaddr *)&serv_addr,(socklen_t *)&adddress_len);  /*storing the client side socket in a socket descriptor*/
    if(client_fd < 0)       
        error_print(errno);
   
    data_status = read(client_fd,buffer,255);   /*reading data from the client side if any*/
    printf("%s\n",buffer);                     /*printing the data received*/
    if(data_status < 0)
        error_print(errno);
    data_status = write(client_fd,"I got your message",18);    /*writing data back to the server*/
    if(data_status < 0)
        error_print(errno);
}
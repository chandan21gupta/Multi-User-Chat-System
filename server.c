#include<stdio.h>
#include<stlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

/*
    Server side
    1) Create socket
    2) Bind the socket
    3) Listen to the socket
    4) Accept connections
*/

void main() {
    int server_fd;
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd <=0) {
        perror("Socket creation failed!!");
        exit(EXIT_STATUS);
    }
    
}
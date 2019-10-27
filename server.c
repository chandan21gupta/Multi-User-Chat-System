#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

void main(int argc, char *argv[]) {
    
    if(argc < 2){ 
        perror("No port provided...Exiting");
        exit(1);
    }
    int server_fd; //server socket descriptor
    int client_fd; //client socket descriptor
    int port_no;    //port number
    int client_address; //size of the client address
    int n;

    char buffer[256];  //reading data from server to this buffer

    struct sockaddr_in server_addr, client_addr; //for containing the addresses of client and server sockets

    server_fd = socket(AF_INET,SOCK_STREAM,0); //initializing the port number
    if(server_fd < 0) {
        perror("Socket initialization failed...Exiting");
        exit(1);
    }

    bzero((char *)&server_addr,sizeof(server_addr));
    
    port_no = atoi(argv[1]); //setting the port number

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_no);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int bindStatus = bind(server_fd,(struct sockaddr *) &server_addr,sizeof(server_addr)); //binding the socket to the server address
    if(bindStatus < 0){
        perror("Binding unsuccessfull....Exiting");
        exit(1);
    }
    
    listen(server_fd,5);  //waiting for incoming connections from the client

    client_address = sizeof(client_addr);

    client_fd = accept(server_fd,(struct sockaddr *) &client_addr,&client_address);
    if(client_fd < 0){
        perror("Connection error....Exiting");
        exit(1);
    }
    bzero(buffer,256);
    n = read(client_fd,buffer,255);
    if(n<0){
        perror("Error in reading data");
        exit(1);
    }
    printf("Received message: %s\n",buffer);

    n = write(client_fd,"I got your message",18);
    if(n<0){
        perror("Error in writing data");
        exit(1);
    }
}
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <netdb.h> 

void main(int argc, char *argv[]) {
    int server_fd;
    int port_no;
    int n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    if(argc < 3) {
        perror("not enough arguments...Exiting");
        exit(0);
    }
    port_no = atoi(argv[2]);
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0) {
        perror("Socket initialization failed...Exiting");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if(server == NULL) {
        perror("No such host...Exiting");
        exit(1);
    }
    bzero((char *)&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,(char *)&server_addr.sin_addr.s_addr,server->h_length);
    server_addr.sin_port = htons(port_no);

    int connectStatus = connect(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(connectStatus < 0) {
        perror("Connection failed.....exiting");
        exit(1);
    }
    printf("Enter a message\n");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(server_fd,buffer,strlen(buffer));
    if(n < 0) {
        perror("Error sending message!!");
        exit(1);
    }
    printf("%s\n",buffer);
}
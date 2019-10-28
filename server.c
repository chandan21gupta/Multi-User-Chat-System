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

int current_client = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client
{
    int id;
    int client_fd;
    struct sockaddr_in client_addr;
    int address_len;
};

void error_print(int error_num)
{
    printf("error_print: %s\n",strerror(error_num));
    exit(1);
}

struct client Client[1024];
pthread_t thread[1024];

void * listening(void *client_detail)
{
    struct client *clientDetail = (struct client *)client_detail;
    printf("New Connection : Client Number %d\n",(clientDetail->id)+1);

    while(1)
    {
        char buffer[256];
        int data_status = recv((clientDetail->client_fd),buffer,256,0);
        buffer[data_status] = '\0';

        if(strcmp(buffer,"SEND") == 0)
        {
            data_status = recv((clientDetail->client_fd),buffer,1024,0);
            buffer[data_status] = '\0';

            int index = atoi(buffer)-1;
            data_status = recv((clientDetail->client_fd),buffer,256,0);
            buffer[data_status] = '\0';

            send(Client[index].client_fd,buffer,256,0);
        }

    }
    return NULL;
}

void main()
{   
    int server_fd;                      /*server side socket descriptor*/
    int client_fd;                      /*client side socket descriptor*/
    struct sockaddr_in serv_addr;       /*server address structure*/
    //char buffer[256];                   /*buffer for containing incoming and outgoing messages*/
    //int data_status;                    /*status of reading and writing data*/
    int adddress_len = sizeof(serv_addr); /*storing the size of the server address in bytes*/
    pid_t pid;

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)  /*creating server side socket*/
        error_print(errno);

    serv_addr.sin_family = AF_INET;             
    serv_addr.sin_addr.s_addr = INADDR_ANY;     /*specifying the configuration for the server address*/
    serv_addr.sin_port = htons(PORT);           

    if(bind(server_fd,(struct sockaddr *)&serv_addr,adddress_len) < 0)  /*binding the created socket to the address*/
        error_print(errno);
    
    listen(server_fd,5);   /*telling the server to listen to any incoming collections*/

    while(1)
    {
        Client[current_client].client_fd = accept(server_fd,(struct sockaddr *)&Client[current_client].client_addr,&Client[current_client].address_len);
        Client[current_client].id = current_client;

        pthread_create(&thread[current_client],NULL,listening,(void *)&Client[current_client]);
        current_client++;
    }

    for(int i=0;i<current_client;i++)
    {
        pthread_join(thread[i],NULL);
    }
}
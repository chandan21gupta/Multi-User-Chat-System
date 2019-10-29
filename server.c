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

void error_print(int error_num)
{
    printf("error_print: %s\n",strerror(error_num));
    exit(1);
}

struct client
{
    int id;
    int client_fd;
    struct sockaddr_in client_addr;
    int address_len;
};

struct client Client[1024];
int existing_clients[1024];
pthread_t thread[1024];

void * listening(void *client_detail)
{
    struct client *clientDetail = (struct client *)client_detail;
    printf("New Connection : Client Number %d\n",(clientDetail->id)+1);

    while(1)
    {
        char buffer[256];
        int data_status = recv((clientDetail->client_fd),buffer,256,0);
        if(data_status < 0)
            error_print(errno);
        buffer[data_status] = '\0';

        if(strcmp(buffer,"EXIT") == 0)
        {
            printf("Client Number %d exited\n",(clientDetail->id)+1);
            existing_clients[(clientDetail->id)] = 0;
        }

        else if(strcmp(buffer,"SEND") == 0)
        {
            data_status = recv((clientDetail->client_fd),buffer,256,0);
            if(data_status < 0)
                error_print(errno);
            buffer[data_status] = '\0';

            if(strcmp(buffer,"ALL") == 0)
            {
                data_status = recv((clientDetail->client_fd),buffer,256,0);
                if(data_status < 0)
                    error_print(errno);
                buffer[data_status] = '\0';
                for(int i=0;i<=current_client;i++)
                {
                    if(existing_clients[i] == 1 && i != ((clientDetail->id)))
                    {   char str[512] = "Client ";
                        char st[5];
                        sprintf(st,"%d ",(clientDetail->id)+1);
                        strcat(str,st);
                        strcat(str,buffer);
                        //printf("%s\n",str);
                        send(Client[i].client_fd,str,512,0);
                    }
                }
            }
            else if(atoi(buffer))
            {
                int index = atoi(buffer)-1;
                if(index >= 0 && existing_clients[index] == 1)
                {
                    data_status = recv((clientDetail->client_fd),buffer,256,0);
                    if(data_status < 0)
                        error_print(errno);
                    buffer[data_status] = '\0';
                    char str[512] = "Client ";
                    char st[5];
                    sprintf(st,"%d ",(clientDetail->id)+1);
                    strcat(str,st);
                    strcat(str,buffer);
                    send(Client[index].client_fd,str,512,0);
                }
                else
                {
                    send(clientDetail->client_fd,"No Client with the given ID",50,0);
                }
            }
        }
        else if(strcmp(buffer,"LIST") == 0)
        {
            for(int i=0;i<current_client;i++)
            {
                if(existing_clients[i] == 1)
                    printf("%d\n",(i+1));
            }
        }
    }
    return NULL;
}

void main()
{   

    for(int i=0;i<1024;i++)
    {
        existing_clients[i] = 0;
    }
    int server_fd;                      /*server side socket descriptor*/
    struct sockaddr_in serv_addr;       /*server address structure*/
    int adddress_len = sizeof(serv_addr); /*storing the size of the server address in bytes*/

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
        if(current_client < 1024)
        {
        Client[current_client].client_fd = accept(server_fd,(struct sockaddr *)&Client[current_client].client_addr,&Client[current_client].address_len);
        Client[current_client].id = current_client;

        pthread_create(&thread[current_client],NULL,listening,(void *)&Client[current_client]);
        existing_clients[current_client] = 1;
        current_client++;
        }
        else
        {
            printf("Maximum 1023 clients are allowed at a time....\n");
        }
    }

    for(int i=0;i<current_client;i++)
    {
        pthread_join(thread[i],NULL);
    }

}
/*********************************   server.c   *******************************
* 
******************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t t_read, t_sleep;

typedef struct Client
{
    int clientnum;
    int val;
    int clientfifo;
} Client;

typedef struct List
{
    Client* clients;
    int size;
} List;

void *readFromClients();
void *waitForClient();

void main (void)
{

    /* Create the fifos and open them  */
    if ((mkfifo("FIFO_TO_SERVER",0666) < 0 && errno != EEXIST))
	{
	    perror("\nCan't create FIFO to server\n");
	    exit(-1);
	}

    if (pthread_create(&t_read, NULL, readFromClients, NULL) != 0)
    {
        printf("\nCouldn't create read thread\n");
        exit(-1);
    }

    if (pthread_create(&t_sleep, NULL, waitForClient, NULL) != 0)
    {
        printf("\nCouldn't create sleep thread\n");
        exit(-1);
    }

    /*
    if ((mkfifo("FIFO_to_client",0666)<0 && errno != EEXIST))
	{
	perror("cant create FIFO_to_client");
	exit(-1);
	}
    
    if((fda=open("FIFO_to_server", O_RDONLY))<0)
        printf("cant open fifo to write");

    if((fdb=open("FIFO_to_client", O_WRONLY))<0)
        printf("cant open fifo to read");
  
    finish=read(fda, charbuff, 1); 	//read the character
  
    printf("Server: just got character: ,%c", charbuff[0]);

    for( i = 0; i<5; i++)
        outchar[i] = '*';
    outchar[5] = charbuff[0];
    outchar[6] = 0;
    printf("\nServer: outchar is,%s", outchar);

    write(fdb, outchar, 7); 
    printf("\nServer: Got the characters sent");
 
    if(finish == 1)
        printf("\nServer: This says I am ready to close ");

    close(fda);
    close(fdb);
    unlink("FIFO_to_server");
    unlink("FIFO_to_client");
    */
  

}

void *readFromClients()
{
    int serverfifo;	// to read from client
    int size = 3, i = 0;
    List* clientlist = (List*) malloc(sizeof(List));
    clientlist->clients = (Client*) malloc(sizeof(Client) * size);
    clientlist->size = 0;
    
    while(1)
    {
        read(serverfifo, &(clientlist->clients[i++]), sizeof(Client));
        
        if (i == clientlist->size)
        {
            clientlist->size++;
            clientlist->clients = (Client*) realloc(clientlist->clients, 
                    sizeof(Client) * clientlist->size);
        }
    }
        
}

void *waitForClient()
{
    sleep(3);
    printf("\nNo clients have sent data for 3 seconds, assuming no more clients\n");
    pthread_cancel(t_read);
}

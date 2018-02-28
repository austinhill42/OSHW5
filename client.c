/***************************   client.c   ****************************
* 
*
**********************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

typedef struct Client
{
    int pid;
    int val;
    char fifo[10];
} Client;

void main (void)
{
    int serverfifo;	// to write to server
    int clientfifo; // to read from server
    Client client = {getpid(), 0}; // initialize the struct
    sprintf(client.fifo, "%d", getpid());

    printf("\nEnter a number: ");
    scanf("%d", &client.val);

    if ((serverfifo = open("FIFO_TO_SERVER", O_WRONLY)) < 0)
        printf("\nCan't open FIFO to server\n");
    
    if (mkfifo(client.fifo, 0666) < 0 && errno != EEXIST)
    {
        perror("\nCan't create private FIFO\n");
        exit(-1);
    }

    if ((clientfifo = open(client.fifo, O_RDONLY)) < 0)
        printf("\nCan't open private FIFO\n");
 
    write(serverfifo, &client, sizeof(Client));
    /*
    if((fda=open("FIFO_to_server", O_WRONLY))<0)
        printf("cant open fifo to write");

    if((fdb=open("FIFO_to_client", O_RDONLY))<0)
        printf("cant open fifo to read");

    printf("Client: Please enter a character: ");
    scanf("%c", &charbuff);


    write(fda, charbuff, 1);
    printf("\nClient: Got the character sent, now waiting for response ");
    read(fdb, outchar, 7);
    printf("\nClient: received from server %s", outchar);

    close(fda);
    close(fdb);

    printf ("\nall done!\n");
   */
}



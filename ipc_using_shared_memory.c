// shm_server.c:
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> 
 
#define SHMSZ 27
 
void main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    char string[100];
 
    //Naming shared memory segment as "5678"
    key = 5678;
 
    //Creating segment
    if((shmid == shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
 
    //Attaching segment to data space
    if((shm = shmat(shmid, NULL, 0)) == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }
 
    //Enter message to shared memory
    s = shm;
 
    printf("Enter data to put into shared memory: ");
    fgets(string, sizeof(string), stdin);
 
    strcpy(s, string);  
 
    /*Wait until other process changes the first character of
    our memory to '*', indicating that it has read from the 
    shared memory.*/
    while(*shm != '*')
        sleep(1);
}

// shm_client.c:
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
 
#define SHMSZ 27
 
void main()
{
    int shmid;
    key_t key;
    char *shm, *s;
 
    //Get the segment named "5678" created by the server
    key = 5678;
 
    //Locate the segment
    if((shmid = shmget(key, SHMSZ, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
 
    //Attach segment to data space
    if((shm = shmat(shmid, NULL, 0)) == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }
 
    //Read from shared memory
    printf("Data read from shared memory: ");
    for(s = shm; *s != '\0'; s++)
        putchar(*s);
 
    /*Change the first character of the segment to '*'
    indicating we have read the segment*/
    *shm = '*'; 
}

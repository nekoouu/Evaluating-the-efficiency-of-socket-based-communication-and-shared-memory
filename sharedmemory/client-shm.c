#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#define SHMSIZE 100
int main(int argc, char *argv[1])
{    
    struct timeval start, end ;
    int shmid_a;
    int shmid_b;
    key_t key_a;
    key_t key_b;
    char *shm_a;
    char *shm_b;
    pthread_mutex_t lock;
    char *s;
    char buffer[1024];
    key_a = 1098;
    key_b = 2076;
 if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    // segment a for recieveing message from clients
    // client write in segment a
    shmid_a = shmget(key_a, SHMSIZE, 0666);
    if(shmid_a < 0)
    {
        perror("shmget a");
        exit(1);
    }
     shm_a = shmat(shmid_a, NULL, 0);
    if (shm_a == (char *) -1)
    {
        perror("shmat a");
        exit(1);
    }
    // segment b for sending message from server to clients
    //client read segment b 
    shmid_b = shmget(key_b, SHMSIZE, 0666);
    if(shmid_b < 0)
    {
        perror("shmget b");
        exit(1);
    }
     shm_b = shmat(shmid_b, NULL, 0);
    if (shm_b == (char *) -1)
    {
        perror("shmat b");
        exit(1);
    }
    while (1)
    {
    printf("client : \t");
    scanf("%s",&buffer[0]);
    gettimeofday(&start, NULL);
    pthread_mutex_lock(&lock);
    memcpy(shm_a ,buffer, strlen(buffer));
    if (strcmp(buffer, "exit")==0)
    {
        printf("disconnected from server\n");
        exit(1);
    }
    pthread_mutex_unlock(&lock);
    printf("server :\t");
    for (s = shm_b; *s != 0; s++)
    {
        printf("%c",*s);
    }
    printf("\n");
    gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
        long milis = micros * pow(10,-3);
        printf("the elapsed time is %ld mili seconds or %ld micro seconds with more precision\n",milis,micros);
    *shm_b = '*';
}
      return 0;
}

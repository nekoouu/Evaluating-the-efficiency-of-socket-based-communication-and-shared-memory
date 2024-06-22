#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 100
int main(int argc, char *argv[1])
{
    int shmid_a;
    int shmid_b;
    key_t key_a;
    key_t key_b;
    char *shm_a;
    char *shm_b;
    char *s;
    char *s_a;
    char *s_b;
    key_a = 1098;
    key_b = 2076;
    shmid_a = shmget(key_a, SHMSIZE, IPC_CREAT | 0666);
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
    shmid_b = shmget(key_b, SHMSIZE, IPC_CREAT | 0666);
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
    //string1 = "HELLOOOOO client"
    //memcpy(shm ,str, strlen(string1));
 //   s = shm;
   // s += strlen(string1);
    //*s = 0;
  //  while (*shm != '*')
    //        sleep(1);
   // return 0;
    
    s_a = shm_a;

 while (1)
    {
    char buffer[1024] ;
    int i  = 0;
    //az avvalin jayi ke nakhoonde  ta akhare sharedmemory mikhone
    for (s = s_a ; *s != 0; s++)
    {
        buffer[i]= *s;
        //printf("%c",*s);
        i++;
    }
    //be andaze tooli le khonde be pointer ezafe mikone
    s_a += i;
    printf("message recieved from client\n");
    printf("client :\t %s",buffer);
    printf("\n");
    printf("answer sent to client\n");
    printf("\n");
    //send(clientsocket, buffer ,strln(buffer),0);
    char answer[100] = " server recieved your message"; 
    memcpy(shm_b ,answer, strlen(answer));
    *shm_b = '*';
    }
    return 0;
}

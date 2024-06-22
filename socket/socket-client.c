#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <math.h>

int main(int argc,char* argv[]){
    struct timeval start, end ;
    int clientsocket , ret , PORT;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    clientsocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientsocket < 0)
    {printf("error in connection\n");
    exit(1);
    }
    printf("client socket is created\n");
    memset(&serverAddr, '\0',sizeof(serverAddr));
    if(argc==1){
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
        //initalize port and serveraddres
        PORT = 4444 ;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
     }
    else{
//   PORT = atoi(argv[2]);
//   serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
        PORT = 4444 ;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port =  htons(PORT);
    ret = connect(clientsocket, (struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if( ret < 0){
    printf("error in connection\n");
    exit(1);
    }
    printf("connected to server\n");
    while (1)
    {
    printf("client : \t");
    scanf("%s",&buffer[0]);
    gettimeofday(&start, NULL);
    send(clientsocket, buffer ,strlen(buffer),0);
    if (strcmp(buffer, "exit")==0)
    {
        close(clientsocket);
        printf("disconnected from server\n");
        exit(1);
    }
    if(recv(clientsocket , buffer , 1024 , 0)<0)
    {
        printf("error in recieving data\n");
    }else
    {
        printf("server :\t%s\n",buffer);
        gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
        long milis = micros * pow(10,-3);
        printf("the elapsed time is %ld mili seconds or %ld micro seconds with more precision\n",milis,micros);
    }
    }
   
return 0; 

}

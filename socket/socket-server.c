#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

//#define PORT 4444
int main(int argc,char* argv[]){ 
    int sockfd , ret , newsocket , number_of_clients , PORT;
    struct sockaddr_in newAddr ;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    pid_t childpid;
    socklen_t addr_size ;
    number_of_clients = 0 ;
    sockfd = socket(AF_INET , SOCK_STREAM, 0);
    if(sockfd < 0)
    {
    printf("error in connection\n");
    exit(1);
    }
    printf("server socket is created\n");
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

    ret = bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0)
    {
    printf("error in binding\n");
    exit(1);
    }
    printf("bind to port\n");
    if(listen(sockfd,10)== 0)
    {
        printf("listening ...\n");
    }else
    {
        printf("error in listening\n");
    }
    while (1)
    {     
	newsocket = accept(sockfd, (struct sockaddr*)&newAddr,&addr_size);
        if(newsocket < 0){exit(1);}
        printf("connection accepted from server\n");
	number_of_clients ++ ;
	printf("%d client(s) are connected to server\n",number_of_clients);
        if((childpid = fork()) == 0){
            close(sockfd);
            while (1)
            {
                recv(newsocket ,buffer, 1024 ,0);
                if(strcmp(buffer,":exit")== 0){
                    //printf()
                    break;
                }else{
                    printf("client: %s\n", buffer);
                    send(newsocket, buffer , strlen(buffer),0);
                    bzero(buffer, sizeof(buffer));
                }
            }
            
        }
    }
    close(newsocket);
    return 0;
    
}

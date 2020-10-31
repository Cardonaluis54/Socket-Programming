#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char const *argv[]) 
{ 
    int mysock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *Deal = "The Deal has started"; 
    char buffer[1024];
    
    if ((mysock = socket(AF_INET, SOCK_STREAM, 0)) == false) 
    { 
        printf("\n Socket creation error \n"); 
        exit(1); 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(argv[1])); 
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        exit(1); 
    } 
   
    if (connect(mysock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Error \n"); 
        exit(1); 
    } 
    send(mysock , Deal , strlen(Deal) , 0 ); 
    printf("Deal message sent\n"); 
    while(1){
        valread = read( mysock , buffer, 1024);
        If (!valread){
            fprintf(stderr, "Error: Receive error\n");
            exit(1);
        }
        else{
             printf("%s\n",buffer ); 
        }
    }
    return 0; 
} 

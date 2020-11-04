#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>

extern int randperm(int *, int);

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int mysock, newsocket, readvalue, card_deck[52];
	int addrlen = sizeof(address);
	char buffer[1024];
	const char *deal = "Deal";
	
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));
	
	if ((mysock = socket (AF_INET, SOCK_STREAM, 0)) == 0)
	{ 
        printf("Socket failed\n");
        exit(1);
    } 
    
	if (bind (mysock, (struct sockaddr*) &address, sizeof(address))!= 0)
	{
		printf("Binding Error\n");
		
		exit(1);
	}
	if (listen (mysock, 10)!=0)
	{
        printf("Listening Error\n"); 
        exit(1); 
    
    fprintf(stdout,"Connecting.\n");
    
    } 
    
    while(1){
		newsocket = accept (mysock, (struct sockaddr*) &address, (socklen_t*) &addrlen);
		if (newsocket<0){
			
			printf("Not Accepted\n");
			exit(1);
			}
	
		readvalue = read(newsocket,buffer,sizeof(buffer));

		int comparingString=strcmp(buffer,deal);

		if(comparingString==0){
			sprintf(buffer,"The Deal has begun\n");
			send(newsocket,buffer,strlen(buffer),0);

			for(int c=0;c<52;c++){
				card_deck[c]=c+1;
				}

			randperm(card_deck,52);

			for(int d=0;d<52;d++){
				sprintf(buffer, "Card %d %d\r\n",d+1, card_deck[d]);
				send(newsocket,buffer, strlen(buffer), 0);
				}
		}

		else{
			sprintf(buffer,"Server is not responding\n");
			send(newsocket,buffer,strlen(buffer),0);
			}
	
		}
	
	return 0;
}

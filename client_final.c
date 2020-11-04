#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h>
#include <stdlib.h>

enum suits { SPADES, HEARTS, DIAMONDS, CLUBS };
enum faces { ACE, TWO,THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, };

typedef struct card{
	char *values;
	char *types;
}

int main(int argc, char const *argv[]) 
{ 
    int mysock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *deal = "Deal"; 
    char buffer[1024];
    char message[2000]
    
    if ((mysock = socket(AF_INET, SOCK_STREAM, 0)) == false) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(atoi(argv[1])); 
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(mysock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Error \n"); 
        return -1; 
    } 
	
	printf("Type 'Deal': \n\n"); 
	
	while(1){
		
		scanf("%s",message);
		
		srand(time(NULL));
		int i, r;
	
		char name[4][9] = {{"diamonds"}, {"clubs"}, {"hearts"}, {"spades"}};
		char number [13][6] = {{"ace"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"jack"}, {"queen"}, {"king"}};
	
		card c[52];
		card temp;
	
		for (i = 0; i < 52; i++) {
			c[i].types = name[i%4];
			c[i].values = number[i%13];
		}
	
		for(i = 0; i < 52; i++) {
			r = rand() % 52;
			temp = c[i];
			c[i] = c[r];
			c[r] = temp;
		}
	
		for (i = 0; i < 52; i++) {
		printf("%s %s\n", c[i].types, c[i].values);
		}
    
	valread = read( mysock, buffer, 1024); 
	}
	
    return 0; 
}

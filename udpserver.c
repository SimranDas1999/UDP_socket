#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT 8080  
    
 
int main() { 
    int sockfd;  
    struct sockaddr_in servaddr, cliaddr; 
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        printf("socket failed"); 
        return -1; 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, ( struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        printf("bind failed"); 
        return -1; 
    } 
        
    int len, n,p; 
    char buffer[1024];
    len=sizeof(cliaddr);
    while(1)
    {
	bzero(buffer,1024); 
        recvfrom(sockfd,buffer, 1024, 0,
	 ( struct sockaddr*) &cliaddr, &len); 
        printf("From Client : %sTo client:", buffer); 
	bzero(buffer,1024);
        p=0;
	while((buffer[p++]=getchar()) != '\n');
        sendto(sockfd, buffer,1024, 0, (struct sockaddr *) &cliaddr, 
            len); 
        
       // return 0;
    }	
}

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
    struct sockaddr_in servaddr; 
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        printf("socket failed"); 
        return -1; 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    int n, len,p;
    char buffer[1024];
    while(1)
    {
        bzero(buffer,1024);
        printf("Enter message:");
        p=0;
        while((buffer[p++]=getchar())!='\n');	
        
        sendto(sockfd, buffer,1024, 0, (struct sockaddr *) &servaddr,  
            sizeof(servaddr));
	bzero(buffer,1024);
            
        recvfrom(sockfd, buffer,1024,0, (struct sockaddr *) &servaddr, 
                &len); 
        printf("From Server : %s\n", buffer); 
    }
    close(sockfd); 
    return 0; 
}

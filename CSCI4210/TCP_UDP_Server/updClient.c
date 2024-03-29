#include <arpa/inet.h> 
#include <fcntl.h>
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#define PORT 8213
#define MAXLINE 1024 

int main() 
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    char* message = "WHO\n"; 
    struct sockaddr_in servaddr; 
  
    int n, len; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        printf("socket creation failed"); 
        exit(0); 
    } 
  
    bzero(buffer, sizeof(buffer));
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // send hello message to server 
    sendto(sockfd, (const char*)message, strlen(message), 
           0, (const struct sockaddr*)&servaddr, 
           sizeof(servaddr)); 
  
    // receive server's response 
    printf("Message from server: "); 
    n = recvfrom(sockfd, (char*)buffer, MAXLINE, 
                 0, (struct sockaddr*)&servaddr, 
                 &len);
    printf("Read %d bytes\n", len);
    puts(buffer); 
    close(sockfd); 
    return 0; 
} 
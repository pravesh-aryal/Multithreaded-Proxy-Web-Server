#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
    if (sockfd == -1) {
        perror("Socket creation failed");
        return 1;
    }
    
    printf("Socket descriptor: %d\n", sockfd); // Print socket descriptor
    
    close(sockfd); // Close the socket
    return 0;
}

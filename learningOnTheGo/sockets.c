#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    struct addrinfo hints, *res;
    int sockfd;

    // Load up address structs with getaddrinfo:
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // Use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM; // TCP stream socket
    hints.ai_flags = AI_PASSIVE;     // Fill in my IP for me (passive)

    // Get address information
    if (getaddrinfo(NULL, "3490", &hints, &res) != 0) {
        perror("getaddrinfo failed");
        return 1;
    }

    // Create a socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("socket failed");
        freeaddrinfo(res);  // Free the linked list
        return 1;
    }

    // Bind the socket to the address
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind failed");
        close(sockfd);
        freeaddrinfo(res);
        return 1;
    }

    printf("Server listening on port 3490\n");

    // Cleanup
    freeaddrinfo(res); // Free the linked list after we are done using it
    close(sockfd);     // Close the socket when done

    return 0;
}
























// #include <stdio.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// int main(){
//     int sockFD = socket(AF_INET, SOCK_STREAM, 0);
//     int sockFD2 = socket(AF_INET, SOCK_STREAM, 0);
//     int sockFD3 = socket(AF_INET, SOCK_STREAM, 0);
//     int sockFD4 = socket(AF_INET, SOCK_STREAM, 0);
//     int sockFD5 = socket(AF_INET, SOCK_STREAM, 0);
//     int sockFD6 = socket(AF_INET, SOCK_STREAM, 0);

//     printf("NEWINT %d \n", sockFD);
//     printf("SOCKFD %d\n", sockFD);
//     printf("SOCKFD2 %d\n", sockFD2);
//     printf("SOCKFD3 %d\n", sockFD3);
//     printf("SOCKFD3 %d\n", sockFD4);
//     printf("SOCKFD3 %d\n", sockFD5);
//     printf("SOCKFD3 %d\n", sockFD6);


//     printf("AF_INET %d \n", AF_INET);
//     printf("SOCK_STREAM %d \n", SOCK_STREAM);

// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    struct addrinfo hints, *res;
    int status;

    // Initialize the hints struct
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;  // Use IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // For binding to any local address

    // Get the address info for the local machine (NULL resolves to local machine)
    status = getaddrinfo(NULL, "0", &hints, &res);  // "0" is a dummy port
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s \n", gai_strerror(status));
        return 1;
    }

    // Cast res->ai_addr to the correct sockaddr_in type for IPv4
    struct sockaddr_in *socket_address = (struct sockaddr_in *)res->ai_addr;

    // Convert the address to a string
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(socket_address->sin_addr), ip_str, sizeof(ip_str));

    printf("The local host address is: %s\n", ip_str);

    // Free the address info after use
    freeaddrinfo(res);

    return 0;
}

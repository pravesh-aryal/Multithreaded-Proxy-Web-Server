// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netdb.h>

// int main() {
//     struct addrinfo info;

//     info.ai_flags = AI_PASSIVE;
//     info.ai_family = AF_INET6;
//     info.ai_socktype = SOCK_DGRAM;
//     info.ai_protocol = 0;
//     info.ai_addrlen = 0;
//     info.ai_addr = NULL;
//     info.ai_canonname = NULL;
//     info.ai_next = NULL;

//     printf("ai_flags: %d\n", info.ai_flags);
//     printf("ai_family: %d\n", info.ai_family);
//     printf("ai_socktype: %d\n", info.ai_socktype);
//     printf("ai_protocol: %d\n", info.ai_protocol);

//     return 0;
// }



/////////////
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <arpa/inet.h>

// int main() {
//     struct sockaddr_in sa;   // Structure for IPv4
//     struct sockaddr_in6 sa6; // Structure for IPv6

//     // IPv4 Address Conversion
//     const char *ipv4 = "10.12.110.57";
//     if (inet_pton(AF_INET, ipv4, &(sa.sin_addr)) != 1) {
//         perror("inet_pton failed for IPv4");
//         return 1;
//     }
//     printf("IPv4 Address: %s successfully converted\n", ipv4);

//     // IPv6 Address Conversion
//     const char *ipv6 = "2001:db8:63b3:1::3490";
//     int x = inet_pton(AF_INET6, ipv6, &(sa6.sin6_addr));

//     if (x != 1) {
//         perror("inet_pton failed for IPv6");
//         return 1;
//     }
//     printf("X IS %d \n", x);
//     printf("IPv6 Address: %s successfully converted\n", ipv6);
//     return 0;
// }


////////////////////
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in sa;  // Structure to hold the IPv4 address
    char ip4[INET_ADDRSTRLEN];  // Buffer to store the IPv4 string

    // Set sa.sin_addr to an example IPv4 address in binary form
    sa.sin_addr.s_addr = inet_addr("192.168.1.1");

    // Convert the binary IPv4 address to a string
    if (inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN) == NULL) {
        perror("inet_ntop failed");
        return 1;
    }

    // Print the IPv4 address as a string
    printf("The IPv4 address is: %s\n", ip4);

    return 0;
}

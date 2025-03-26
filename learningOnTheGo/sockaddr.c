#include <stdio.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET6;  // Set address family to IPv4
    addr.sin_port = htons(8080); // Set port to 8080 (converted to network byte order)
    inet_pton(AF_INET, "192.168.1.1", &addr.sin_addr); // Set IP address

    printf("Address family: %d (AF_INET)\n", addr.sin_family);
    return 0;
}

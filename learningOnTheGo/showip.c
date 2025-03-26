#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){

    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2){
        fprintf(stderr, "Hostname not provided \n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //mayuse ipv4 or ipv6 
    hints.ai_socktype = SOCK_STREAM; //will use TCP socket

    status = getaddrinfo(argv[1], NULL, &hints, &res);

    if (status != 0){
        //failed to get info
        fprintf(stderr, "getaddrinfo: %s \n", gai_strerror(status));
    }

    printf("IP address for %s: \n", argv[1]);

    for (p = res; p != NULL; p = p->ai_next){
        void *addr;
        char *ipver;

        //if ipv4
        if (p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPV4";
        } //if ipv6
        else{
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        //now converting ip to string and printing
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("    %s: %s \n", ipver, ipstr);
    }
    freeaddrinfo(res);

    return 0;
    
}
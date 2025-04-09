#include <stdio.h>
#include <stdlib.h>
//for posix api
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//provides functions structs for networks Berkely sockets
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


#define PORT "3490"


//the number of connections that the OS will allow to queue up before being accepted
#define BACKLOG 10

// struct addrinfo {
// 	int	ai_flags;	/* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
// 	int	ai_family;	/* PF_xxx */
// 	int	ai_socktype;	/* SOCK_xxx */
// 	int	ai_protocol;	/* 0 or IPPROTO_xxx for IPv4 and IPv6 */
// 	socklen_t ai_addrlen;	/* length of ai_addr */
// 	char	*ai_canonname;	/* canonical name for hostname */
// 	struct	sockaddr *ai_addr;	/* binary address */
// 	struct	addrinfo *ai_next;	/* next structure in linked list */
// };


int main(void){
    int sockfd, new_fd; //we listen on sockfd, new connections made on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; //generic socket address struct can hold both ipv4 or ipv6
    socklen_t sin_size; //just a variable
    struct sigaction sa; //??
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    

    //initilize to 0
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; //tcp
    hints.ai_flags = AI_PASSIVE; //wait for incoming connections a server socket

    rv = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (rv != 0){
        fprintf(stderr, "getaddrinfo: %s \n", gai_strerror(rv));
        return 1;
    }
    printf("Hi %s \n", servinfo->ai_canonname);

    for (p = servinfo; p != NULL; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1)
            perror("server: socket");
            continue;
    }    


    return 0;
    


}


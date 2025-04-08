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


int main(void){
    int sockfd, new_fd; //we listen on sockfd, new connections made on new_fd
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM; //tcp
    hints.ai_flags = AI_PASSIVE; //means we will bind to 0.0.0.0

    getaddrinfo(NULL, PORT, &hints, &servinfo);
    


}


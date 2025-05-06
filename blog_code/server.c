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


void sigchld_handler(int s){

    //errno is set when a system call fails could be anything open(), read(), bind() etc.
    int saved_errno = errno;
    //cleaning up zombie processes
    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;

}
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
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

        //create the first valid socket we can and bind to it
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1){
            perror("server: socket");
            continue;
        }
        
        //allowing the reuse of socket, using REUSEADDR and modifying atsocket level using SOL_SOCKET
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
            //if fail
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            //if find fails
            close(sockfd);
            perror("server: bind");
            continue;
        }
        //we break after the first socket
        break;

    }    

    freeaddrinfo(servinfo); // we are done with using servinfo

    // p should not be null if we were successful
    if (p == NULL){
        fprintf(stderr, "server: failed to bind \n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1){
        perror("Listen:");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; //assigning a handler function that will run when SIGCHLD is receieved by parent   
    sigemptyset(&sa.sa_mask); //no other signals are blocked while sigchld handler runs
    sa.sa_flags = SA_RESTART; //makes interuptted calls like accept() automatically restart
    //registering handler when any child process dies
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server is waiting for connections \n");

    while (1){
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1){
            perror("Aceept: ");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
        printf("Server got connection from %s", s);


        if (!fork()){ // the child process
            close(sockfd);
            if (send(new_fd, "Hello world!", 13, 0) == -1){
                perror("send");
            }
            close(new_fd);
            exit(0);
        }
        close(new_fd);

    }


    return 0;
    


}


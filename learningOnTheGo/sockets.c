#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    int sockFD2 = socket(AF_INET, SOCK_STREAM, 0);
    int sockFD3 = socket(AF_INET, SOCK_STREAM, 0);
    int sockFD4 = socket(AF_INET, SOCK_STREAM, 0);
    int sockFD5 = socket(AF_INET, SOCK_STREAM, 0);
    int sockFD6 = socket(AF_INET, SOCK_STREAM, 0);

    printf("NEWINT %d \n", sockFD);
    printf("SOCKFD %d\n", sockFD);
    printf("SOCKFD2 %d\n", sockFD2);
    printf("SOCKFD3 %d\n", sockFD3);
    printf("SOCKFD3 %d\n", sockFD4);
    printf("SOCKFD3 %d\n", sockFD5);
    printf("SOCKFD3 %d\n", sockFD6);


    printf("AF_INET %d \n", AF_INET);
    printf("SOCK_STREAM %d \n", SOCK_STREAM);

}
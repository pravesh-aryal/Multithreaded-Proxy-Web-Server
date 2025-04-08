#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("SOcked created %d", sockfd);
    // close(sockfd);
    return 0;
}





// #include <stdio.h>

// #define PI 3
// #define full_name "Pravesh Aryal"

// const int a = 90;

// int main(){
//     printf("The PI value is %d\n", PI);
//     printf("The full name is %s \n", full_name);
//     printf("The a value is %d\n", a);

//     printf("The address of a is %p\n", (void*)&a);
//     printf("The address of a is %p\n", &a);

//     printf("The address of PI is %p\n", &PI);

// }

// #include <stdio.h>

// int main() {
//     unsigned int x = 1;
//     char *c = (char*)&x;
//     if (*c)
//         printf("Little-endian\n");
//     else
//         printf("Big-endian\n");
//     return 0;
// }



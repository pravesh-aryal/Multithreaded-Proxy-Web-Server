#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t  pid = fork();

    if (pid < 0){
        perror("Fork failed");
        return 1;
    }
    printf("The pid is %d \n", pid);
    printf("PID AGAIN : %d \n", pid);
    if (pid == 0){
        printf("Child: sleeping .... \n");
        sleep(4);
        printf("Child exits \n");
        exit(0);
    }

    printf("Parent process started: \n");
    while (1){

        pid_t result = waitpid(-1, NULL, WNOHANG);
        
        if (result == 0){
            printf("Parent: child still running: \n");
        } else if (result == -1){
            perror("waitpid");
            break;
        }else{
            printf("Parent reaped child with PID %d \n", result);
            break;
        }
        sleep(1);
    }

    printf("Parent: done \n");
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



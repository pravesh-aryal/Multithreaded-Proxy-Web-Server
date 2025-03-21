#include <stdio.h>

#define PI 3
#define full_name "Pravesh Aryal"

const int a = 90;

int main(){
    printf("The PI value is %d\n", PI);
    printf("The full name is %s \n", full_name);
    printf("The a value is %d\n", a);

    printf("The address of a is %p\n", (void*)&a);
    printf("The address of a is %p\n", &a);

    printf("The address of PI is %p\n", &PI);

}
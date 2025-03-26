#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
    data.i = 10;
    printf("i: %d\n", data.i);

    data.f = 3.14;
    printf("f: %f\n", data.f);  // Overwrites i
    printf("%f", data.i);
    return 0;
}

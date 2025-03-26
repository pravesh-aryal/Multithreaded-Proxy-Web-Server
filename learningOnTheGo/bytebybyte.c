char *names[] = {"Pravesh", "rambo", "aambo", "chyangba"};

for (int i = 0; i < 4; i++){
    printf("%p %s\n",names[i], names[i]);
}

// printf("Byte at address %p is %c \n", names[0], *names[0]);

for (int i = 0; i < 20; i++){

    printf("Byte at address %p is %c \n", names[0]+i, *(names[0]+i));
}
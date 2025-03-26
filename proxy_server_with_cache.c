#include "proxy_parse.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define MAX_CLINETS 10
typedef struct cache_element cache_element;

//we will maintain a linkedlist of cache_element
struct cache_element{
    char *data;
    int len;
    char *url;
    time_t lru_time_track;
    cache_element *next;
}

cache_element* find(char* url);
int add_cache_element(char* data, int size, char* url);
void remove_cache_element();

int port_number = 9090;
int proxy_socketId;

pthread_t tid[MAX_CLIENTS];

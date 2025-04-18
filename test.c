#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Get current file flags
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl - get");
        close(fd);
        return 1;
    }

    // Set non-blocking mode
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl - set");
        close(fd);
        return 1;
    }

    char buf[100];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("No data available (non-blocking read).\n");
        } else {
            perror("read");
        }
    } else if (n == 0) {
        printf("End of file.\n");
    } else {
        buf[n] = '\0';
        printf("Read %zd bytes: %s\n", n, buf);
    }

    close(fd);
    return 0;
}

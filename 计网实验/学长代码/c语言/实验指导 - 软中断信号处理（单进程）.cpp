#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void handle_sig(int sign) {
    if (sign == SIGUSR1) {
        printf("[pid](%d): [sig](SIGUSR1)  is captured\n", getpid());
    } else if (sign == SIGUSR2) {
        printf("[pid](%d): [sig](SIGUSR2)  is captured\n", getpid());
    } else if (sign == SIGINT) {
        printf("[pid](%d): [sig](SIGINT)  is captured\n", getpid());
        printf("[pid](%d): exit\n", getpid());
        exit(0);
    }
}
int main(int argc, char *argv[]) {
    printf("[pid](%d): start\n", getpid());
    struct sigaction newsign;
    memset(&newsign, 0, sizeof(newsign));
    sigemptyset(&newsign.sa_mask);
    newsign.sa_handler = handle_sig;
    sigaction(SIGUSR1, &newsign, NULL);
    sigaction(SIGUSR2, &newsign, NULL);
    sigaction(SIGINT, &newsign, NULL);
    while (1) {
        pause();
    }

    return 0;
}

#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int conc_amnt;

void pa_handle_sigint() {
    printf("[pid](%d): SIGINT is handled in pa_handle_sigint()\n", getpid());
    printf("[pid](%d): [func](exit)  with [conc_amnt](%d)\n", getpid(), conc_amnt);
    exit(0);
}

void pa_handle_sigchld() {
    pid_t pid;
    printf("[pid](%d): SIGCHLD is handled in pa_handle_sigchld()\n", getpid());
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
        printf("[pid](%d): [cpid](%d) is waited in pa_handle_sigchld()\n", getpid(), pid);
        conc_amnt--;
    }
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-c") == 0) {
        char buf[6];
        pid_t pid[5] = {0};
        pid_t cpid;
        conc_amnt = argv[2][0] - '0';
        int n = conc_amnt;
        printf("[pid](%d): start\n", getpid());
        struct sigaction newsign;
        memset(&newsign, 0, sizeof(newsign));
        sigemptyset(&newsign.sa_mask);
        newsign.sa_handler = pa_handle_sigint;
        sigaction(SIGINT, &newsign, NULL);  // 安装信号处理器
        struct sigaction newsign1;
        memset(&newsign1, 0, sizeof(newsign1));
        sigemptyset(&newsign1.sa_mask);
        newsign1.sa_handler = pa_handle_sigchld;
        sigaction(SIGCHLD, &newsign1, NULL);  // 安装信号处理器

        // 派生进程
        for (int i = 1; i < n; ++i) {
            pid[i] = fork();
            if (pid[i] == 0) {
                printf("[pid](%d): start\n", getpid());
                cpid = 0;
                break;
            } else {
                cpid = 1;
            }
        }
        if (cpid == 0) {
            pause();
        } else {
            sleep(1);
            for (int i = 1; i < n; ++i) {
                kill(pid[i], SIGINT);
            }
            while (conc_amnt != 1) {
                printf("[pid](%d): [func](pause) with [conc_amnt](%d)\n", getpid(), conc_amnt);
                pause();
            }
            pause();
        }
    }
    return 0;
}

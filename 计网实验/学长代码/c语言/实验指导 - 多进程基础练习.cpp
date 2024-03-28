#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-c") == 0) {
        pid_t pid[8];
        char buf[8][10] = {'\0'};
        int n = argv[2][0] - '0';
        printf("[pid](%d) [ppid](%d): start\n", getpid(), getppid());
        int fd1_td1 = open("./td1.txt", O_RDONLY);
        printf("[pid](%d) [ppid](%d): [fd1_td1](%d) is got\n", getpid(), getppid(), fd1_td1);
        for (int i = 1; i < n; ++i) {
            pid[i] = fork();
            if (pid[i] == 0) {
                printf("[pid](%d) [ppid](%d): start\n", getpid(), getppid());
                // read(int fd, void *buf[i], size_t count);
                read(fd1_td1, buf[i], 5);
                printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td1](%d)\n", getpid(), getppid(), buf[i], fd1_td1);
                int fd2_td1 = open("./td1.txt", O_RDONLY);
                printf("[pid](%d) [ppid](%d): [fd2_td1](%d) is got\n", getpid(), getppid(), fd2_td1);
                memset(buf[i], '\0', sizeof(char) * 6);
                read(fd2_td1, buf[i], 5);
                printf("[pid](%d) [ppid](%d): [read](%s) by [fd2_td1](%d)\n", getpid(), getppid(), buf[i], fd2_td1);
                close(fd2_td1);
                close(fd1_td1);
                printf("[pid](%d) [ppid](%d): exit\n", getpid(), getppid());
                exit(0);
            }
        }
        char buf1[6] = {'\0'};
        memset(buf1, '\0', sizeof(char) * 6);
        read(fd1_td1, buf1, 5);
        printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td1](%d)\n", getpid(), getppid(), buf1, fd1_td1);
        close(fd1_td1);
        int fd1_td2 = open("./td2.txt", O_RDONLY);
        printf("[pid](%d) [ppid](%d): [fd1_td2](%d) is got\n", getpid(), getppid(), fd1_td2);
        memset(buf1, '\0', sizeof(char) * 6);
        read(fd1_td2, buf1, 5);
        printf("[pid](%d) [ppid](%d): [read](%s) by [fd1_td2](%d)\n", getpid(), getppid(), buf1, fd1_td2);
        close(fd1_td2);
        sleep(2);
        printf("[pid](%d) [ppid](%d): exit\n", getpid(), getppid());
        exit(0);
    }

    return 0;
}

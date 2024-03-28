#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define BACKLOG 5

int sigint_flag = 0;

void handle_sigint(int sig) {
    printf("[srv] SIGINT is coming!\n");
    sigint_flag = 1;
}

void handle_sigchld(int sig, siginfo_t *info, void *context) {
    pid_t pid_chld;
    int stat;
    while ((pid_chld = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("[srv](%d)[chd](%d) Child has terminated!\n", getppid(), pid_chld);
    }
}

void srv_biz(int connfd, char *version) {
    char buf[BUFFER_SIZE];
    short cid;
    char res[BUFFER_SIZE + 16];
    short version_pro = (short)atoi(version);
    version_pro = htons(version_pro);  // 将version转换为网络字节序
    while (1) {
        memset(buf, 0, sizeof(buf));
        memset(res, 0, sizeof(res));
        ssize_t read_cid = read(connfd, (char *)&(cid), 2);  // 读取cid
        if (read_cid == 0) {
            break;
        } else if (read_cid < 0) {
            break;
        }
        ssize_t read_content = read(connfd, buf, sizeof(buf));
        if (read_cid == 0 || read_content == 0) {
            break;
        } else if (read_content < 0) {
            break;
        }
        printf("[chd](%d)[cid](%d)[ECH_RQT] %s", getpid(), ntohs(cid), buf);

        memcpy(res, &version_pro, sizeof(short));
        strcpy(&(res[2]), buf);
        ssize_t size_write = write(connfd, res, strlen(res));
        if (size_write < 0) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    struct sigaction sa_int, sa_chld;
    struct sockaddr_in server, client;
    int pid;

    char *ip = argv[1];
    char *port = argv[2];
    char *key = argv[3];

    // 安装SIGINT信号的处理函数
    sa_int.sa_flags = 0;
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction error");
        exit(1);
    }

    // 安装SIGCHLD信号的处理函数
    sa_chld.sa_sigaction = handle_sigchld;
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_SIGINFO;
    if (sigaction(SIGCHLD, &sa_chld, NULL) == -1) {
        perror("sigaction error");
        exit(1);
    }

    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        return 1;
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int bind_result = bind(listen_sock, (struct sockaddr *)&server, sizeof(server));
    if (bind_result < 0) {
        return 1;
    }

    int listen_result = listen(listen_sock, BACKLOG);
    if (listen_result < 0) {
        return 1;
    }

    printf("[srv](%d)[srv_sa](%s:%s)[vcd](%s) Server has initialized!\n", getpid(), ip, port, key);

    while (!sigint_flag) {
        socklen_t len = sizeof(client);
        int connfd = accept(listen_sock, (struct sockaddr *)&client, &len);
        if (connfd < 0) {
            if (errno == EINTR)
                continue;
        }
        printf("[srv](%d)[cli_sa](%s:%d) Client is accepted!\n", getpid(), inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        pid = fork();
        if (pid != 0) {
            printf("[chd](%d)[ppid](%d) Child process is created!\n", pid, getpid());
        }
        if (pid == 0) {
            close(listen_sock);
            srv_biz(connfd, key);
            printf("[chd](%d)[ppid](%d)[cli_sa](%s:%d) Client is closed!\n", getpid(), getppid(), inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            close(connfd);
            printf("[chd](%d)[ppid](%d) connfd is closed!\n", getpid(), getppid());
            printf("[chd](%d)[ppid](%d) Child process is returning!\n", getpid(), getppid());
            return 0;
        }
        close(connfd);
    }
    close(listen_sock);
    return 0;
}

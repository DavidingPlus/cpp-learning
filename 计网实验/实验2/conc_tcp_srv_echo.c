#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 80
#define BACKLOG 5

bool judge_stdin(const char *str, int _argc) {
    if (_argc == 4)
        return true;
    printf("%s  usage:<ip_address>  <port>  <cid>\n", str);
    return false;
}

int sigint_flag = 0;  // 信号
int sig_type = 0;

// 安装sigint信号处理器
void handle_sigint(int sig) {
    sigint_flag = 1;
}

// 安装sig_pipe信号量
void sig_pipe(int signo) {
    sig_type = signo;
    pid_t pid = getpid();
}

// 安装使用SIGCHLD信号处理器
void sig_chld(int signo) {
    pid_t pid_chld;
    int stat;
    while ((pid_chld = waitpid(-1, &stat, WNOHANG)) > 0)
        ;
}

int main(int argc, char *argv[]) {
    if (judge_stdin(argv[0], argc) == false)
        return 1;

    // 存放转换后的ip地址
    char ip_str[20] = {0};
    pid_t pid = getpid();
    const char *veri_code = argv[3];

    // 安装使用sigint信号处理器
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // 使用sigchild
    struct sigaction new, old;
    new.sa_handler = sig_chld;
    sigemptyset(&new.sa_mask);
    new.sa_flags = 0;
    sigaction(SIGCHLD, &new, NULL);

    // 使用sig_pipe信号
    old.sa_handler = sig_pipe;
    sigemptyset(&old.sa_mask);
    old.sa_flags = 0;
    sigaction(SIGPIPE, &old, NULL);

    // 建立套接字，返回监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                 // 地址族协议（IPv4orIPv6）
    serv_addr.sin_port = htons(atoi(argv[2]));      // 端口
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // IP地址

    // 给套接字绑定一个端口和IP
    int bind_ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (bind_ret < 0) {
        perror("bind");
        return 1;
    }
    // 开始监听
    int listen_ret = listen(listenfd, BACKLOG);
    if (listen_ret < 0) {
        perror("listen");
        return 1;
    }

    // 使用inet_ntop函数转换ip
    const char *tes = inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));

    // 打印初始化信息
    printf("[srv](%d)[srv_sa](%s:%d)[vcd](%s) Server has initialized!\n", pid, ip_str, ntohs(serv_addr.sin_port), argv[3]);

    // 开启accpet()主循环，直至sigint_flag指示服务器退出；
    while (!sigint_flag) {
        struct sockaddr_in clie_addr;
        socklen_t clie_addr_len = sizeof(clie_addr);

        // 要一个客户端进程进行处理，返回参数主要是有一个客户端通信描述符cfd，程序就是通过这个cfd和客户端进行交互
        int connectfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
        if (connectfd >= 0) {
            tes = inet_ntop(AF_INET, &clie_addr.sin_addr, ip_str, sizeof(ip_str));
            printf("[srv](%d) [cli_sa][%s:%d] Client is accepted!\n", pid, ip_str, (int)ntohs(clie_addr.sin_port));
        } else {
            if (errno != EINTR)
                perror("accept");
            else
                continue;
            return 1;
        }

        int forkid = fork();
        if (forkid == 0) {
            // ==0 这就是子进程
            int child_pid = getpid();
            printf("[chd](%d)[ppid](%d) Child process is created!\n", child_pid, pid);
            // 第一时间关闭监听
            close(listenfd);

            char buf[BUFFER_SIZE] = {0};
            // 收发业务小循环
            while (true) {
                read(connectfd, buf, 2);
                int value = ((unsigned char)buf[0] << 8) | (unsigned char)buf[1];

                memset(buf, 0, BUFFER_SIZE);

                char subStr[BUFFER_SIZE];
                int n = read(connectfd, subStr, BUFFER_SIZE);

                int if_exit = strncmp(buf, "EXIT", 4);
                if (n <= 0 || if_exit == 0) {
                    printf("[chd](%d)[ppid](%d)[cli_sa](%s:%d) Client is closed!\n", child_pid, pid, ip_str, (int)ntohs(clie_addr.sin_port));
                    break;
                }

                printf("[chd](%d)[cid](%d)[ECH_RQT] %s", getpid(), value, subStr);

                char ret_buf[BUFFER_SIZE];
                memset(ret_buf, 0, BUFFER_SIZE);

                // 将数据拆分成高位和低位
                ret_buf[0] = (atoi(veri_code) >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
                ret_buf[1] = atoi(veri_code) & 0xFF;         // 低位存储在数组的第二个元素中

                for (int i = 0; i < strlen(subStr); i++) {
                    ret_buf[i + 2] = subStr[i];
                }
                ret_buf[strlen(subStr) + 2] = '\0';

                write(connectfd, ret_buf, BUFFER_SIZE);

                memset(buf, 0, BUFFER_SIZE);
            }

            close(connectfd);
            printf("[chd](%d)[ppid](%d) connfd is closed!\n", child_pid, pid);
            printf("[chd](%d)[ppid](%d) Child process is to return!\n", child_pid, pid);
            return 0;
        }
        close(connectfd);
    }
    // 关闭监听
    close(listenfd);

    return 0;
}

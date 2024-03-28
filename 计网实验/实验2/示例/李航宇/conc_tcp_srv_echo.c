// 由于实验指导没有给出异常处理信息，本代码没有设计异常处理
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 80

void usage(const char *str) {
    printf("%s  usage:<IP><PORT><veri_code>\n", str);
}

int sigint_flag = 0;
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

// 主函数
int main(int argc, char *argv[]) {
    int cid = 0;

    // 存放转换后的ip地址
    char ip_str[20] = {0};

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

    struct sockaddr_in serv_addr, clie_addr;
    int listenfd, connectfd;
    int ret;
    socklen_t clie_addr_len;

    // 判断输入的参数
    char *veri_code = argv[3];
    if (argc != 4) {
        usage(argv[0]);
        return 1;
    }

    // 建立套接字，返回监听套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                  // 地址族协议（IPv4orIPv6）
    serv_addr.sin_port = htons(atoi(argv[2]));       // 端口
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // IP地址

    // tes存放返回结果
    const char *tes;

    // 使用inet_ntop函数转换ip
    tes = inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));

    // 获取父进程
    pid_t parrent_pid = getpid();

    // 打印初始化信息
    printf("[srv](%d)[srv_sa](%s:%d)[vcd](%s) Server has initialize!\n", parrent_pid, ip_str, ntohs(serv_addr.sin_port), argv[3]);

    if (listenfd < 0) {
        perror("socket");
        return 1;
    }

    // 给套接字绑定一个端口和IP
    ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("bind");
        return 1;
    }

    // 开始监听
    ret = listen(listenfd, 20);
    if (ret < 0) {
        perror("listen");
        return 1;
    }

    // 大循环
    while (!sigint_flag) {
        clie_addr_len = sizeof(clie_addr);

        // 要一个客户端进程进行处理，返回参数主要是有一个客户端通信描述符cfd，程序就是通过这个cfd和客户端进行交互
        connectfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);

        if (connectfd < 0) {
            if (errno == EINTR)
                continue;
            else
                perror("accept");
            return 1;
        } else {
            tes = inet_ntop(AF_INET, &clie_addr.sin_addr, ip_str, sizeof(ip_str));
            printf("[srv](%d) [cli_sa][%s:%d] Client is accepted!\n", parrent_pid, ip_str, (int)ntohs(clie_addr.sin_port));
        }

        // 创建子进程
        if (!fork()) {
            // 获取子进程pid
            pid_t child_pid = getpid();

            // 打印信息
            printf("[chd](%d)[ppid](%d) Child process is created!\n", child_pid, parrent_pid);

            // 关闭监听
            close(listenfd);

            int n = 0;
            char buf[80] = {0};
            char *to_exit = "EXIT";
            // 获得cid
            char cid[10] = {0};

            while (1) {
                read(connectfd, buf, 2);
                int value = ((unsigned char)buf[0] << 8) | (unsigned char)buf[1];

                memset(buf, 0, 80);

                char subStr[BUFFER_SIZE];
                n = read(connectfd, subStr, BUFFER_SIZE);

                int if_exit = strncmp(buf, to_exit, 4);
                if (n <= 0 || if_exit == 0) {
                    printf("[chd](%d)[ppid](%d)[cli_sa](%s:%d) Client is closed!\n", child_pid, parrent_pid, ip_str, (int)ntohs(clie_addr.sin_port));
                    break;
                }

                printf("[chd](%d)[cid](%d)[ECH_RQT] %s", getpid(), value, subStr);

                // 最多读sizeof(buf)-1,留下一个空间放\0
                // n = read(connectfd, buf, 60);

                char character[BUFFER_SIZE];
                memset(character, 0, BUFFER_SIZE);

                value = atoi(veri_code);
                // 将数据拆分成高位和低位
                character[0] = (value >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
                character[1] = value & 0xFF;         // 低位存储在数组的第二个元素中

                for (int i = 0; i < strlen(subStr); i++) {
                    character[i + 2] = subStr[i];
                }
                character[strlen(subStr) + 2] = '\0';

                write(connectfd, character, BUFFER_SIZE);

                memset(buf, 0, BUFFER_SIZE);
            }
            // 关闭连接
            close(connectfd);
            printf("[chd](%d)[ppid](%d) connfd is closed!\n", child_pid, parrent_pid);
            printf("[chd](%d)[ppid](%d) Child process is to return!\n", child_pid, parrent_pid);
            return getpid();
        }

        // 关闭连接
        close(connectfd);
    }
    close(listenfd);

    return 0;
}

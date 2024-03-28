#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

void usage(const char *str) {
    printf("%s  usage:<IP><PORT><veri_code>\n", str);
}

int sigint_flag = 0;  // 信号

void handle_sigint(int sig) {
    printf("[srv] SIGINT is coming!\n");
    sigint_flag = 1;
}

void srv_biz(int connfd) {}

//./serv 127.0.0.1 8000
int main(int argc, char *argv[]) {
    char *left = "(";
    char *right = ")";

    // 存放转换后的ip地址
    char ip_str[20] = {0};

    // 安装使用sigint信号处理器
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    // 注册信号处理器
    sigaction(SIGINT, &sa, NULL);

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

    // 打印初始化信息
    printf("[srv] server[%s:%d][%s] is initializing!\n", ip_str, ntohs(serv_addr.sin_port), argv[3]);
    printf("[srv] Server has initialized!\n");

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

    // 开启accpet()主循环，直至sigint_flag指示服务器退出；
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
            printf("[srv] client[%s:%d] is accepted!\n", ip_str, (int)ntohs(clie_addr.sin_port));
        }
        int n = 0;
        char buf[140] = {0};
        char *to_exit = "EXIT";

        // 收发业务小循环
        while (1) {
            memset(buf, 0, 140);

            // 最多读sizeof(buf)-1,留下一个空间放\0
            n = read(connectfd, buf, sizeof(buf) - 1);

            int if_exit = strncmp(buf, to_exit, 4);
            if (n <= 0 || if_exit == 0) {
                printf("[srv] client[%s:%d] is closed!\n", ip_str, (int)ntohs(clie_addr.sin_port));
                break;
            }
            buf[n] = 0;
            printf("[ECH_RQT]%s", buf);
            char ret_buf[140];
            memset(ret_buf, 0, 140);
            strcat(ret_buf, left);
            strcat(ret_buf, veri_code);
            strcat(ret_buf, right);
            int length = strlen(ret_buf);
            for (int i = 0; i < strlen(buf); i++) {
                ret_buf[length + i] = buf[i];
                if (buf[i] == '\n')
                    break;
            }
            ret_buf[strlen(ret_buf)] = '\0';
            write(connectfd, ret_buf, strlen(ret_buf) + 2);
            memset(ret_buf, 0, 140);
        }
        // 关闭连接
        close(connectfd);
        printf("[srv] connfd is closed!\n");
    }

    // 关闭监听
    close(listenfd);
    printf("[srv]listenfd is closed!\n");
    printf("[srv]server is to return! \n!");

    return 0;
}

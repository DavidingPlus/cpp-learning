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
#include <unistd.h>

// 存放转换后的ip地址
char ip_str[20] = {0};
// 缓存buf区
char buf[140] = {0};
// 常量
char *left = "(";
char *right = ")";

bool judge_stdin(const char *str, int _argc) {
    if (_argc == 4)
        return true;
    printf("%s  usage:<ip_address>  <port>  <veri_code>\n", str);
    return false;
}

int sigint_flag = 0;  // 信号
void handle_sigint(int sig) {
    printf("[srv] SIGINT is coming!\n");
    sigint_flag = 1;
}

void create_sigint() {
    // 安装使用sigint信号处理器
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    // 注册信号处理器
    sigaction(SIGINT, &sa, NULL);
}

int create_listen() {
    // 建立套接字，返回监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return 1;
    }
    return listenfd;
}

void print_Init(struct sockaddr_in _serv_addr, char *_veri_code) {
    // 打印初始化信息
    printf("[srv] server[%s:%d][%s] is initializing!\n", ip_str, ntohs(_serv_addr.sin_port), _veri_code);
    printf("[srv] Server has initialized!\n");
}

int Bind_Listen(int _listenfd, struct sockaddr_in _serv_addr) {
    // 给套接字绑定一个端口和IP
    int ret = bind(_listenfd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr));
    if (ret < 0) {
        perror("bind");
        return 1;
    }
    // 开始监听
    ret = listen(_listenfd, 20);
    if (ret < 0) {
        perror("listen");
        return 1;
    }
}

void get_retbuf(char *_ret_buf, const char *_left, const char *_right, const char *_veri_code) {
    memset(_ret_buf, 0, 140);
    strcat(_ret_buf, _left);
    strcat(_ret_buf, _veri_code);
    strcat(_ret_buf, _right);
}

void Work_retbuf(char *_ret_buf, int _connectfd) {
    int length = strlen(_ret_buf);
    for (int i = 0; i < strlen(buf); i++) {
        _ret_buf[length + i] = buf[i];
        if (buf[i] == '\n')
            break;
    }
    _ret_buf[strlen(_ret_buf)] = '\0';
    write(_connectfd, _ret_buf, strlen(_ret_buf) + 2);
    memset(_ret_buf, 0, 140);
}

int main(int argc, char *argv[]) {
    // 判断输入的参数
    char *veri_code = argv[3];

    if (judge_stdin(argv[0], argc) == false)
        return 1;

    create_sigint();

    int listenfd = create_listen();

    struct sockaddr_in serv_addr, clie_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                  // 地址族协议（IPv4orIPv6）
    serv_addr.sin_port = htons(atoi(argv[2]));       // 端口
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // IP地址

    // 使用inet_ntop函数转换ip
    // tes存放返回结果
    const char *tes = inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));

    // 打印初始化信息
    print_Init(serv_addr, veri_code);

    // 给套接字绑定一个端口和IP
    Bind_Listen(listenfd, serv_addr);

    // 开启accpet()主循环，直至sigint_flag指示服务器退出；
    while (!sigint_flag) {
        socklen_t clie_addr_len = sizeof(clie_addr);

        // 要一个客户端进程进行处理，返回参数主要是有一个客户端通信描述符cfd，程序就是通过这个cfd和客户端进行交互
        int connectfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);

        if (connectfd >= 0) {
            tes = inet_ntop(AF_INET, &clie_addr.sin_addr, ip_str, sizeof(ip_str));
            printf("[srv] client[%s:%d] is accepted!\n", ip_str, (int)ntohs(clie_addr.sin_port));
        } else {
            if (errno != EINTR)
                perror("accept");
            else
                continue;
            return 1;
        }

        // 收发业务小循环
        while (true) {
            memset(buf, 0, 140);

            // 最多读sizeof(buf)-1,留下一个空间放\0
            int n = read(connectfd, buf, sizeof(buf) - 1);
            int if_exit = strncmp(buf, "EXIT", 4);
            if (n <= 0 || if_exit == 0) {
                printf("[srv] client[%s:%d] is closed!\n", ip_str, (int)ntohs(clie_addr.sin_port));
                break;
            }

            buf[n] = 0;
            printf("[ECH_RQT]%s", buf);

            char ret_buf[140];
            get_retbuf(ret_buf, left, right, veri_code);

            Work_retbuf(ret_buf, connectfd);
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

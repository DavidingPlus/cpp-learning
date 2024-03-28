#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

// 全局存放ip_str
char ip_str[20] = {0};
// 全局存放buf
char buf[140] = {0};

bool judge_stdin(const char *str, int _argc) {
    if (_argc == 3)
        return true;
    printf("%s  usage:<ip_address>  <port>\n", str);
    return false;
}

// 初始化socket
int InitSocket() {
    // 返回客户端的进程描述符
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    return sockfd;
}

int StartConnect(int _sockfd, struct sockaddr_in _addr) {
    int ret = connect(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr));
    if (ret >= 0) {
        // 转换IP地址
        inet_ntop(AF_INET, &_addr.sin_addr, ip_str, sizeof(ip_str));
        printf("[cli] server[%s:%d] is connected!\n", ip_str, ntohs(_addr.sin_port));
    } else {
        perror("connect");
        return 1;
    }
    return ret;
}

void Work(const char *_EXIT, int _sockfd) {
    while (true) {
        memset(buf, 0, 140);
        fgets(buf, 140, stdin);

        int if_exit = strncmp(buf, _EXIT, 4);
        if (if_exit == 0)
            break;

        // 写入并打印写入内容
        write(_sockfd, buf, strlen(buf));
        printf("[ECH_RQT]%s", buf);

        memset(buf, 0, 140);
        read(_sockfd, &buf, sizeof(buf) - 1);

        // 显示服务器发送的内容
        printf("[ECH_REP]%s", buf);
        memset(buf, 0, 140);
    }
}

int main(int argc, char *argv[]) {
    if (judge_stdin(argv[0], argc) == false)
        return 1;

    int sockfd = InitSocket();

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // connect表示客户端与服务端尝试建立连接
    // connect里面的输入参数有要连接服务端的地址
    // connect执行的时候就会被服务端listen检测到
    // 如果accept没有阻塞的话，这时候就会进行三次握手
    // 三次握手完成以后，服务端执行完accept，客户端执行完connect

    // 发起客户端请求连接

    int ret = StartConnect(sockfd, serv_addr);

    Work("EXIT", sockfd);

    close(ret);
    printf("[cli]listenfd is closed!\n");
    printf("[cli]server is to return! \n!");

    return 0;
}

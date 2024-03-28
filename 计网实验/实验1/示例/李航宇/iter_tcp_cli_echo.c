#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

void usage(const char *str) {
    printf("%s  usage:<IP><PORT><veri_code>\n", str);
}

int main(int argc, char *argv[]) {
    // 存放ip_str
    char ip_str[20] = {0};

    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    struct sockaddr_in serv_addr;
    int sockfd;

    // 返回客户端的进程描述符
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // connect表示客户端与服务端尝试建立连接
    // connect里面的输入参数有要连接服务端的地址
    // connect执行的时候就会被服务端listen检测到
    // 如果accept没有阻塞的话，这时候就会进行三次握手
    // 三次握手完成以后，服务端执行完accept，客户端执行完connect

    // 发起客户端请求连接
    int ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("connect");
        return 1;
    } else {
        // 转换IP地址
        inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));
        printf("[cli] server[%s:%d] is connected!\n", ip_str, ntohs(serv_addr.sin_port));
    }

    char buf[140] = {0};
    char *to_exit = "EXIT";
    while (1) {
        memset(buf, 0, 140);
        fgets(buf, 140, stdin);

        int if_exit = strncmp(buf, to_exit, 4);
        if (if_exit == 0)
            break;

        // 写入并打印写入内容
        write(sockfd, buf, strlen(buf));
        printf("[ECH_RQT]%s", buf);

        memset(buf, 0, 140);
        read(sockfd, &buf, sizeof(buf) - 1);

        // 显示服务器发送的内容
        printf("[ECH_REP]%s", buf);
        memset(buf, 0, 140);
    }

    close(ret);
    printf("[cli]listenfd is closed!\n");
    printf("[cli]server is to return! \n!");
    return 0;
}

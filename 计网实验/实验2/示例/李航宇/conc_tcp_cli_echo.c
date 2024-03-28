#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXSIZE 80

void usage(const char *str) {
    printf("%s  usage:<IP><PORT><veri_code>\n", str);
}

int main(int argc, char *argv[]) {
    // 存放ip_str
    char ip_str[20] = {0};

    if (argc != 4) {
        usage(argv[0]);
        return 1;
    }

    char *cid = argv[3];

    // 进程号
    pid_t pid = getpid();

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
        printf("[cli](%d)[srv_sa](%s:%d)Server is connected!\n", pid, ip_str, ntohs(serv_addr.sin_port));
    }

    char buf[80] = {0};
    char *to_exit = "EXIT";

    while (1) {
        memset(buf, 0, 80);
        fgets(buf, 80, stdin);

        printf("[cli](%d)[cid](%d)[ECH_RQT] %s", pid, atoi(cid), buf);

        int if_exit = strncmp(buf, to_exit, 4);
        if (if_exit == 0)
            break;

        char result[82];  // 总长度
        int value = atoi(cid);

        // 将数据拆分成高位和低位
        result[0] = (value >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
        result[1] = value & 0xFF;         // 低位存储在数组的第二个元素中
        int j = 0;
        for (j = 0; j < 80; j++) {
            result[2 + j] = buf[j];
        }

        result[2 + j] = '\0';  // 添加字符串结尾的空字符

        //   写入并打印写入内容
        write(sockfd, result, MAXSIZE + 2);

        memset(buf, 0, 80);
        read(sockfd, &buf, 2);
        int vertycode = ((unsigned char)buf[0] << 8) | (unsigned char)buf[1];
        char subStr[80];
        read(sockfd, subStr, 78);
        printf("[cli](%d)[vcd](%d)[ECH_REP] %s", getpid(), vertycode, subStr);
    }

    close(sockfd);
    printf("[cli](%d) connf is closed!\n", pid);
    printf("[cli](%d) Client is to return! \n", pid);
    return 0;
}

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 80

bool judge_stdin(const char *str, int _argc) {
    if (_argc == 4)
        return true;
    printf("%s  usage:<ip_address>  <port>  <cid>\n", str);
    return false;
}

void cli_biz(int sockfd, const char *_cid) {
    char buf[BUFFER_SIZE] = {0};
    int cid = atoi(_cid);

    while (true) {
        memset(buf, 0, BUFFER_SIZE);
        //-----写
        fgets(buf, BUFFER_SIZE, stdin);  // 自带'\n'
        printf("[cli](%d)[cid](%d)[ECH_RQT] %s", getpid(), cid, buf);

        int if_exit = strncmp(buf, "EXIT", 4);
        if (if_exit != 0)
            goto THEN;
        break;

    THEN:
        char ret_buf[BUFFER_SIZE + 2] = {0};
        // 将数据拆分成高位和低位
        ret_buf[0] = (cid >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
        ret_buf[1] = cid & 0xFF;
        int i = 0;  // 低位存储在数组的第二个元素中
        for (i = 0; i < BUFFER_SIZE; i++) {
            ret_buf[i + 2] = buf[i];
        }
        ret_buf[i + 2] = '\0';  // 添加字符串结尾的空字符

        write(sockfd, ret_buf, BUFFER_SIZE + 2);

        //-----读
        memset(buf, 0, BUFFER_SIZE);
        read(sockfd, &buf, 2);
        int vcd = ((unsigned char)buf[0] << 8) | (unsigned char)buf[1];

        char tmp_buf[BUFFER_SIZE];
        read(sockfd, tmp_buf, BUFFER_SIZE - 2);
        printf("[cli](%d)[vcd](%d)[ECH_REP] %s", getpid(), vcd, tmp_buf);
    }
}

int main(int argc, char *argv[]) {
    if (judge_stdin(argv[0], argc) == false)
        return 1;

    char ip_str[20] = {0};
    pid_t pid = getpid();

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // 返回客户端的进程描述符
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket error");
        return 0;
    }

    // connect表示客户端与服务端尝试建立连接
    // connect里面的输入参数有要连接服务端的地址
    // connect执行的时候就会被服务端listen检测到
    // 如果accept没有阻塞的话，这时候就会进行三次握手
    // 三次握手完成以后，服务端执行完accept，客户端执行完connect

    // 发起客户端请求连接
    int connectfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connectfd >= 0) {
        // 转换IP地址
        inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));
        printf("[cli](%d)[srv_sa](%s:%d)Server is connected!\n", pid, ip_str, ntohs(serv_addr.sin_port));

    } else {
        perror("connect error");
        return 0;
    }

    cli_biz(sockfd, argv[3]);

    close(sockfd);
    printf("[cli](%d) connf is closed!\n", pid);
    printf("[cli](%d) Client is to return! \n", pid);

    return 0;
}

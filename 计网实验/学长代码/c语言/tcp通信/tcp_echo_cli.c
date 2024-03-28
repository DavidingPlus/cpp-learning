/***********************************************************************************************
    > File Name: client.c
    > Author: course team of computer networks,
          School of Information and Software Engineering, UESTC
    > E-mail: networks_cteam@is.uestc.edu.cn


本程序的功能是客户端用TCP连接到服务器，然后服务器给客户端发送一条欢迎消息。服务器的端口为12345，
运行./srv01 即可执行；客户端执行示例为 ./cli01 x.x.x.x 12345，其中x.x.x.x为服务器的IP。

**********************************************************************************************/

#include <arpa/inet.h>   //inet_pton()等函数
#include <netinet/in.h>  //IP地址和端口相关定义，比如struct sockaddr_in等
#include <stdio.h>
#include <stdlib.h>      //exit()函数，atoi()函数
#include <string.h>      //bzero()函数
#include <sys/socket.h>  //套接字基本函数
#include <sys/types.h>   //Unix/Linux系统的基本系统数据类型的头文件,含有size_t,time_t,pid_t等类型
#include <unistd.h>      //C 和 C++ 程序设计语言中提供对 POSIX 操作系统 API 的访问功能的头文件
#define MAX_CMD_STR 100

int clientfd, numbytes;          // clientfd是客户端套接字，numbytes是客户端接收到的字节数
struct sockaddr_in server_addr;  // 存放服务器端地址信息，connect()使用
char buf[MAX_CMD_STR + 1];       // 缓冲区，用于存放从服务器接收到的信息

int echo_rqt() {
    // 从stdin读取1行
    memset(buf, '\0', (MAX_CMD_STR + 1));
    while (fgets(buf, MAX_CMD_STR, stdin)) {
        // TODO 收到exit，退出循环返回
        if (strncmp(buf, "exit", 4) == 0) {
            return 0;
        }
        // TODO 查询所读取1行字符的长度，并将行末'\n'更换为'\0'
        int len_h = strlen(buf);  // 按主机字节序读写的长度变量；
        int len_n = 0;            // 按网络字节序读写的长度变量；
        buf[len_h - 1] = '\0';
        len_n = htonl(len_h);
        // TODO 根据读写边界定义，先发数据长度，再发缓存数据
        write(clientfd, &len_n, sizeof(len_n));
        write(clientfd, buf, len_h);
        // TODO 读取服务器echo回显数据，并打印输出到stdout，依然是先读长度，再根据长度读取数据。
        /* int型长度变量在读写时请特别注意字节序转换！强烈建议做如下定义，以示区分：*/
        int len_nr = 0;
        int len_hr = 0;
        read(clientfd, &len_nr, sizeof(len_nr));
        len_hr = ntohl(len_nr);
        int res = 0;
        /* 在通过read()读取数据时，有可能因为网络传输等问题，使得read()期望读取长度为LEN的数据，但是首次读取仅返回了长度为RES(RES < LEN)的数据（剩余数据尚未接收至系统内核缓存）。因此在read()后必须进行合理判断、循环读取，直至多次read()返回的RES累加和等于LEN，否则读取数据不完整。测试平台刻意制造了必须多次读取的场景，故要求客户端、服务器都必须执行*/
        while (1) {
            /* code */
            res = res + read(clientfd, &buf[res], len_hr);
            if (res == len_hr) {
                printf("[echo_rep] %s\n", buf);
                break;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {  // 如果命令行用法不对，则提醒并退出
        printf("usage: %s  <server IP address>  <server port>\n", argv[0]);
        exit(0);
    }

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Create socket failed.");
        exit(1);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) == 0)  // argv[1] 为服务器IP字符串，需要用inet_pton转换为IP地址
    {
        perror("Server IP Address Error:\n");
        exit(1);
    }

    server_addr.sin_port = htons(atoi(argv[2]));  // argv[2] 为服务器端口，需要用atoi及htons转换

    if (connect(clientfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect failed.");
        exit(1);
    } else {
        printf("[cli] server[%s:%s] is connected! \n", argv[1], argv[2]);
        echo_rqt();
    }

    close(clientfd);
    printf("[cli] connfd is closed!\n");
    printf("[cli] client is going to exit!\n");
}

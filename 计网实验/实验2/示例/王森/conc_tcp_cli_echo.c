#include <arpa/inet.h>
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 70

#define INTER_SIZE 2

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int cid = atoi(argv[3]);
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error in creating socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in connecting to server");
        return 1;
    }
    printf("[cli](%ld)[srv_sa](%s:%ld) Server is connected!\n", getpid(), ip, port);

    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);

        printf("[cli](%ld)[cid](%ld)[ECH_RQT] %s", getpid(), cid, buffer);
        if (strcmp(buffer, "EXIT\n") == 0) {
            break;
        }
        char result[BUFFER_SIZE + 2];  // 总长度为8+151=159
        int j;
        int value = cid;
        // 将数据拆分成高位和低位
        result[0] = (value >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
        result[1] = value & 0xFF;         // 低位存储在数组的第二个元素中
        for (j = 0; j < BUFFER_SIZE; j++) {
            result[2 + j] = buffer[j];
        }

        result[2 + j] = '\0';  // 添加字符串结尾的空字符
        ssize_t bytes_sent, bytes_received;
        bytes_sent = write(client_socket, result, BUFFER_SIZE + 2);
        if (bytes_sent == -1) {
            perror("Error in sending head");
            break;
        }
        bytes_received = read(client_socket, buffer, 2);
        int vertycode = ((unsigned char)buffer[0] << 8) | (unsigned char)buffer[1];
        if (bytes_received == -1) {
            perror("Error in receiving data");
            break;
        }
        char subStr[BUFFER_SIZE];
        bytes_received = read(client_socket, subStr, BUFFER_SIZE - 2);
        printf("[cli](%ld)[vcd](%ld)[ECH_REP] %s", getpid(), vertycode, subStr);
    }

    close(client_socket);
    return 0;
}
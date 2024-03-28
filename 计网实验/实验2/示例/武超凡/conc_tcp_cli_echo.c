#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(1);
}

void cli_biz(int connfd, char *client_id) {
    char buf[BUFFER_SIZE];
    short server_version;
    char res[BUFFER_SIZE + 16];
    short client_id_pro = (short)atoi(client_id);
    client_id_pro = htons(client_id_pro);  // 将client_id转换为网络字节序

    while (1) {
        fgets(buf, BUFFER_SIZE, stdin);
        printf("[cli](%d)[cid](%s)[ECH_RQT] %s", getpid(), client_id, buf);

        if (strcmp(buf, "EXIT\n") == 0) {
            break;
        }

        memcpy(res, &client_id_pro, sizeof(short));
        strcpy(&(res[2]), buf);
        ssize_t size_write = write(connfd, res, strlen(res));
        if (size_write < 0) {
            break;
        }
        memset(buf, 0, sizeof(buf));
        memset(res, 0, sizeof(res));
        ssize_t size_read = read(connfd, (char *)&server_version, 2);
        if (size_read < 0) {
            break;
        }
        size_read = read(connfd, buf, sizeof(buf));
        if (size_read < 0) {
            break;
        }
        printf("[cli](%d)[vcd](%d)[ECH_REP] %s", getpid(), ntohs(server_version), buf);
        memset(buf, 0, sizeof(buf));
        memset(res, 0, sizeof(res));
    }
}

int main(int argc, char *argv[]) {
    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd < 0) {
        handle_error("socket error");
        return 0;
    }

    char *ip = argv[1];
    char *port = argv[2];
    char *key = argv[3];

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));
    server.sin_addr.s_addr = inet_addr(ip);

    int connection = connect(connfd, (struct sockaddr *)&server, sizeof(server));
    if (connection < 0) {
        handle_error("connect error");
        return 0;
    }

    printf("[cli](%d)[srv_sa](%s:%s) Server is connected!\n", getpid(), argv[1], argv[2]);

    cli_biz(connfd, key);
    close(connfd);

    return 0;
}

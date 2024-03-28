#include <arpa/inet.h>
#include <endian.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 70
#define INTER_SIZE 8
int sigint_flag = 0;
void sig_chld(int signo) {
    pid_t pid_chld;
    int stat;
    while ((pid_chld = waitpid(0, &stat, WNOHANG)) > 0) {
        if (WIFEXITED(stat))
            printf("[srv](%ld)[chd](%ld) Child has terminated!\n", getpid(), pid_chld);
        else if (WIFSIGNALED(stat))
            printf("child %ld killed by the %ldth signal\n", pid_chld, WTERMSIG(stat));
    }
}

void handle_sigint(int sig) {
    printf("[srv] SIGINT is coming!\n");
    sigint_flag = 1;
}
void handle_client(int client_socket, int vertycode, char *ip, int port) {
    char buffer[BUFFER_SIZE + 2];
    ssize_t bytes_received, bytes_sent;

    while (1) {
        bytes_received = read(client_socket, buffer, 2);
        int value = ((unsigned char)buffer[0] << 8) | (unsigned char)buffer[1];
        if (bytes_received <= 0) {
            printf("[chd]() [ppid]() client[%s:%ld] is closed.\n", ip, port);
            break;
        }
        char subStr[BUFFER_SIZE];
        bytes_received = read(client_socket, subStr, BUFFER_SIZE);
        printf("[chd](%ld)[cid](%ld)[ECH_RQT] %s", getpid(), value, subStr);
        char character[BUFFER_SIZE];
        memset(character, 0, BUFFER_SIZE);

        // sprintf(character,"(%d)[ECH_REP] ",vertycode);
        // printf("%d\n",vertycode);
        value = vertycode;
        // 将数据拆分成高位和低位
        character[0] = (value >> 8) & 0xFF;  // 高位存储在数组的第一个元素中
        character[1] = value & 0xFF;         // 低位存储在数组的第二个元素中
        for (int i = 0; i < strlen(subStr); i++) {
            character[i + 2] = subStr[i];
        }
        character[strlen(subStr) + 2] = '\0';
        // for(int k=0;k<=strlen(subStr)+2;k++)
        //{
        //     printf("%d\n",character[k]);
        // }
        bytes_sent = write(client_socket, character, BUFFER_SIZE);
        if (bytes_sent <= 0) {
            printf("Error in sending data to client.\n");
            break;
        }
        memset(buffer, 0, BUFFER_SIZE);
    }

    close(client_socket);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    if (argc < 4) {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error in creating socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    // printf("[srv] server[%s:%ld][%s] is initializing!\n", ip, port,argv[3]);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in binding");
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error in listening");
        return 1;
    }
    printf("[srv](%ld)[srv_sa](%s:%ld)[vcd](%s) Server has initialized!\n", getpid(), ip, port, argv[3]);
    // printf("Server listening on %s:%d\n", ip, port);

    while (!sigint_flag) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            if (errno == EINTR)
                continue;
            else {
                perror("Error in accepting connection");
                return 1;
            }
        }
        printf("[srv](%ld)[cli_sa](%s:%ld) Client is accepted!\n", getpid(), inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pid_t fpid = fork();
        if (fpid < 0)
            printf("error in fork!");
        else if (fpid == 0) {
            close(server_socket);
            // printf("[chd](%ld)[ppid](%ld) Child process is created!\n",getpid(),getppid());
            handle_client(client_socket, atoi(argv[3]), ip, port);
            return getpid();
        } else {
            close(client_socket);
            struct sigaction sa;
            sa.sa_flags = 0;
            sa.sa_handler = sig_chld;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGCHLD, &sa, NULL);
        };
    }

    close(server_socket);

    return 0;
}
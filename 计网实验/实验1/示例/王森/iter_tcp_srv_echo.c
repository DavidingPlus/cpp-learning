#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER_SIZE 150
int sigint_flag = 0;

void handle_sigint(int sig) {
    printf("[srv] SIGINT is coming\n");
    sigint_flag = 1;
}
void handle_client(int client_socket, int vertycode, char *ip, int port) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received, bytes_sent;

    while (1) {
        bytes_received = read(client_socket, buffer, BUFFER_SIZE);
        if (bytes_received <= 0) {
            printf("[srv] client[%s:%d] is closed.\n", ip, port);
            break;
        }
        printf("[ECH_RQT]%s", buffer);
        char character[BUFFER_SIZE];
        memset(character, 0, BUFFER_SIZE);
        sprintf(character, "(%d)", vertycode);
        int length = strlen(character);
        for (int i = 0; i < strlen(buffer); i++) {
            character[length + i] = buffer[i];
            if (buffer[i] == '\n') {
                break;
            }
        }
        character[strlen(character)] = '\0';
        bytes_sent = write(client_socket, character, strlen(character) + 2);
        if (bytes_sent <= 0) {
            printf("Error in sending data to client.\n");
            break;
        }
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

    printf("[srv] server[%s:%d][%s] is initializing!\n", ip, port, argv[3]);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in binding");
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error in listening");
        return 1;
    }
    printf("[srv] Server has initialized!\n");
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
        printf("[srv] client [%s:%d] is accepted!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        handle_client(client_socket, atoi(argv[3]), ip, port);
    }

    close(server_socket);
    printf("[srv] connfd is closed\n");
    printf("[srv] client is to return\n");
    return 0;
}

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER_SIZE 150

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

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
    printf("[cli]server[%s:%d] is connected!\n", ip, port);

    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);

        printf("[ECH_RQT]%s", buffer);
        if (strcmp(buffer, "EXIT\n") == 0) {
            break;
        }

        ssize_t bytes_sent, bytes_received;
        bytes_sent = write(client_socket, buffer, strlen(buffer));
        if (bytes_sent == -1) {
            perror("Error in sending data");
            break;
        }
        bytes_received = read(client_socket, buffer, BUFFER_SIZE);
        if (bytes_received == -1) {
            perror("Error in receiving data");
            break;
        }
        printf("[ECH_REP]%s", buffer);
    }

    close(client_socket);
    printf("[cli]connfd is closed\n");
    printf("[cli]client is to return\n");
    return 0;
}

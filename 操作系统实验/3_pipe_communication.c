#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];    // 管道描述符
    pid_t pid1, pid2; // 子进程ID
    char buf[100];    // 缓冲区

    // 创建管道
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 创建子进程1
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0)
    {
        // 关闭管道的读端
        close(pipefd[0]);

        // 向管道中写入消息
        char msg[] = "Child process 1 is sending a message!\n";
        write(pipefd[1], msg, strlen(msg));
        printf("Child process 1 has sent a message.\n");

        // 关闭管道的写端
        close(pipefd[1]);

        // 退出子进程
        exit(EXIT_SUCCESS);
    }

    // 创建子进程2
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0)
    {
        // 关闭管道的读端
        close(pipefd[0]);

        // 向管道中写入消息
        char msg[] = "Child process 2 is sending a message!";
        write(pipefd[1], msg, strlen(msg));
        printf("Child process 2 has sent a message.\n");

        // 关闭管道的写端
        close(pipefd[1]);

        // 退出子进程
        exit(EXIT_SUCCESS);
    }

    // 等待子进程运行完毕
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // 关闭管道的写端
    close(pipefd[1]);

    // 从管道中读取数据
    while (read(pipefd[0], buf, sizeof(buf)) != 0)
        printf("%s\n", buf);

    // 关闭管道的读端
    close(pipefd[0]);

    return 0;
}

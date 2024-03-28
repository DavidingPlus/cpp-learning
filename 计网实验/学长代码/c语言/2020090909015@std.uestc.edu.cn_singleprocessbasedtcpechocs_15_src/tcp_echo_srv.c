#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <signal.h>
#define BACKLOG	5		//listen函数参数
// 全局变量sig_to_exit，用于指示服务器程序是否退出；
int sig_to_exit = 0;
int sig_type = 0;
int 	listenfd, connectfd;			//分别是监听套接字和连接套接字
struct sockaddr_in	server, client;		//存放服务器和客户端的地址信息（前者在bind时指定，后者在accept时得到）
int	sin_size;				// accept时使用，得到客户端地址大小信息

// SIGINT信号处理函数；
void sig_int(int signo) {
    // TODO 记录本次系统信号编号；
    sig_type=signo;
    printf("[srv] SIGINT is coming!\n");
    // TODO 设置全局变量，以提示服务器程序释放资源；
    sig_to_exit=1;
}

// SIGPIPE信号处理函数；
void sig_pipe(int signo) {
    // TODO 记录本次系统信号编号；
    sig_type=signo;
    printf("[srv] SIGPIPE is coming!\n");
}

// 业务逻辑处理函数；
void echo_rep() {
    // TODO 定义数据长度变量len，以及读取结果变量res；
    int len=0;
    int res=0;
    // TODO 定义缓存指针变量buf;
    char*	buf;	
    while(1){
        // (1) TODO 读取数据长度： res = read(x,x,x);
        /* int型长度变量在读写时请特别注意字节序转换！*/
        res=read(connectfd,&len,sizeof(len));
        // 以下代码紧跟read();
        if(res < 0){
            printf("[srv] read len return %d and errno is %d\n", res, errno);
            if(errno == EINTR){
                if(sig_type == SIGINT)
                    return;//但凡收到SIGINT，指示服务器结束
                continue;//若是其他信号中断，则重新执行读取
            }
            return;
        }else if (res == 0)
        {
            /* code */
            return;
        }
        // TODO 若read返回0（并非指定读0字节返回零），return；
        
        // (2) 按长读取数据；
        // TODO 采用malloc，根据数据长度分配buf；
        len=ntohl(len);
        buf=malloc(len);
        res=0;
        int num=0;
        while(1){
            // TODO 按长读取数据： res = read(x,x,x);
            res=read(connectfd,&buf[num],len);
            num=num+res;  
            // 以下代码紧跟read();
            if(res < 0){
                printf("[srv] read data return %d and errno is %d\n", res, errno);
                if(errno == EINTR){
                    if(sig_type == SIGINT)
                        free(buf);
                        return;//但凡收到SIGINT，指示服务器结束
                    continue;//若是其他信号中断，则重新执行读取
                }
                free(buf);
                return;
            }else if(res==0){
                free(buf);
                return;
            }
            // TODO 若read返回0（并非指定读0字节返回零），return；
            if(res==len){
                break;
            }
            len=len-res;
        }

        // 本轮数据长度以及数据本身的读取结束：
        // TODO 按题设要求打印接收到的[echo_rqt]信息；
        printf("[echo_rqt] %s\n",buf);
        // TODO 回写客户端[echo_rep]信息；根据读写边界定义，同样需先发长度，再发数据：res = write(x,x,x);res = write(x,x,x);
        len=strlen(buf)+1;
        len=htonl(len);
        write(connectfd,&len,sizeof(len));
        write(connectfd,buf,ntohl(len));
        // TODO 发送结束，释放buf；
        free(buf);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3){				//如果命令行用法不对，则提醒并退出
    		printf("usage: %s  <server IP address>  <server port>\n",argv[0]);
    		exit(0);
    	}
    // 安装SIGPIPE信号处理器
    struct sigaction sigact_pipe, old_sigact_pipe;
    sigact_pipe.sa_handler = sig_pipe;
    sigemptyset(&sigact_pipe.sa_mask);
    sigact_pipe.sa_flags = 0;
    // 通过SA_RESTART设置受影响的慢调用在中断结束后立刻重启：
    sigact_pipe.sa_flags |= SA_RESTART;
    sigaction(SIGPIPE, &sigact_pipe, &old_sigact_pipe);

    // TODO 安装SIGINT信号处理器
	struct sigaction sigact_int, old_sigact_int;
    sigact_int.sa_handler = sig_int;
    sigemptyset(&sigact_int.sa_mask);
    sigact_int.sa_flags = 0;
	sigaction(SIGINT, &sigact_int, &old_sigact_int);
    // TODO 定义服务器Socket地址srv_addr，以及客户端Socket地址cli_addr；
    // TODO 定义客户端Socket地址长度cli_addr_len（类型为socklen_t）；
    // TODO 定义Socket监听描述符listenfd，以及Socket连接描述符connfd；
    
    // TODO 初始化服务器Socket地址srv_addr，其中会用到argv[1]、argv[2]
        /* IP地址转换推荐使用inet_pton()；端口地址转换推荐使用atoi(); */


    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[1], &server.sin_addr) == 0)	// argv[1] 为服务器IP字符串，需要用inet_pton转换为IP地址
    {
    	perror("Server IP Address Error:\n");
    	exit(1);
    }
    server.sin_port = htons(atoi(argv[2]));	// argv[2] 为服务器端口，需要用atoi及htons转换


    // TODO 按题设要求打印服务器端地址server[ip:port]，推荐使用inet_ntop();
    
    char str[INET_ADDRSTRLEN];
    printf("[srv] server[%s:%s] is initializing!\n",inet_ntop(AF_INET,&server.sin_addr, str, sizeof(str)),argv[2]);


    // TODO 获取Socket监听描述符: listenfd = socket(x,x,x);
    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1)	//建立监听套接字
	{
		perror("Create socket failed.");		//perror是系统函数，参见https://www.cnblogs.com/noxy/p/11188583.html
		exit(-1);	}
	int opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));	//将地址和端口设为可立即重用（后续再解释）
    // TODO 绑定服务器Socket地址: res = bind(x,x,x);
    if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1) {	//把server里的地址信息绑定到监听套接字上
		perror("Bind error.");
		exit(-1);
	}
    // TODO 开启服务监听: res = listen(x,x);
	if (listen(listenfd, BACKLOG) == -1) {						//开始监听
		perror("listen error.");
		exit(-1);
	}

    sin_size = sizeof(struct sockaddr_in);
    // 开启accpet()主循环，直至sig_to_exit指示服务器退出；

    while(!sig_to_exit)
    {
        // TODO 获取cli_addr长度，执行accept()：connfd = accept(x,x,x);
        connectfd = accept(listenfd, (struct sockaddr *)&client, &sin_size);	//接受客户端连接（从监听队列里取出）
        // 以下代码紧跟accept()，用于判断accpet()是否因SIG_INT信号退出（本案例中只关心SIGINT）；也可以不做此判断，直接执行 connfd<0 时continue，因为此时sig_to_exit已经指明需要退出accept()主循环，两种方式二选一即可。
       
       
       
        if((connectfd == -1) && (errno == EINTR )&& (sig_type = SIGINT))
            break;



        // 若上述if判断不成立且connfd<0，则重启accept();
        if (connectfd < 0)
            continue;

        // TODO 按题设要求打印客户端端地址client[ip:port]，推荐使用inet_ntop();
        printf("[srv] client[%s:%d] is accpeted!\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));        

        // TODO 执行业务处理函数echo_rep()，进入业务处理循环;
        echo_rep();
        // TODO 业务函数退出，关闭connfd;
        close(connectfd);
        printf("[srv] connfd is closed!\n");
    }
    // TODO accpet()主循环结束，关闭lstenfd;
    close(listenfd);
    printf("[srv] listenfd is closed!\n");
    printf("[srv] server is going to exit!\n");
    return 0;
}

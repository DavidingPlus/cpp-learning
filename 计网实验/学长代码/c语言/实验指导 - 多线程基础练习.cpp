#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

int conc_amnt;
char str1[7][70]={'\0'};
pthread_t tid[7];
pthread_attr_t first;

void *func1( void  *arg){
	printf("[spid](%ld) [tgid](%d) [ptid](%ld) start\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());
	printf("[spid](%ld) [read](%s)\n",(long int)syscall(SYS_gettid),(char*)arg);
	printf("[spid](%ld) [tgid](%d) [ptid](%ld) [func](pthread_exit)\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());
	pthread_exit(0);
	
}
void *func2( void  *arg){
	pthread_detach(pthread_self());
	printf("[spid](%ld) [tgid](%d) [ptid](%ld) start\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());
	printf("[spid](%ld) [read](%s)\n",(long int)syscall(SYS_gettid),(char*)arg);
	printf("[spid](%ld) [tgid](%d) [ptid](%ld) [func](pthread_exit)\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());	
	pthread_exit(0);
	
}

int main(int argc, char *argv[])
{
	if(strcmp(argv[1],"-c")==0){
		conc_amnt=argv[2][0]-'0';
		int n=conc_amnt;
		
		printf("[spid](%ld) [tgid](%d) [ptid](%ld) start\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());
		FILE * fp=NULL;
		
		fp = fopen ("td.txt", "r");
		int j;
		char str1[7][70]={'\0'};
		for(int i=1;i<n;++i){
		//	memset(str1,'\0',sizeof(str1));
			fgets(str1[i],65, fp);
			for(j=0;str1[i][j]!='\n';j++){			
			}
			str1[i][j]='\0';
			printf("[spid](%ld) [read](%s)\n",(long int)syscall(SYS_gettid),str1[i]);
			if(i==1){
				pthread_attr_init(&first);
				pthread_attr_setdetachstate(&first, PTHREAD_CREATE_DETACHED);
				pthread_create(&tid[i],&first,func1,(void*)str1[i]);

			}else{
				pthread_create(&tid[i],NULL,func2,(void*)str1[i]);
			}
			
		}
		pthread_attr_destroy(&first);
		fclose(fp);
		
		sleep(1);	
		printf("[spid](%ld) [tgid](%d) [ptid](%ld) [func](exit)\n",(long int)syscall(SYS_gettid),getpid(),pthread_self());
		exit(0); 
	}
	return 0;
}


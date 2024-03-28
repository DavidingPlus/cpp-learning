#include <stdio.h>
#include <arpa/inet.h> 
typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;
void myprint1(u_int32_t ipv4_p,u_int16_t port_p){
	u_int8_t *p;
	u_int32_t *temp=&ipv4_p;
	p=((u_int8_t*)temp);
	printf("[ipv4_n_cbc_d]");
	for(int i=0;i<3;++i){
		printf("%u",*p);
		printf(".");
		p++;
	}
	printf("%u\n",*p);//逐字节输出
	p=((u_int8_t*)temp);
	printf("[ipv4_n_cbc_x]");
	for(int i=0;i<3;++i){
		printf("%02X",*p);
		p++;
	}
	printf("%02X\n",*p);//逐字节输出0x
	printf("[ipv4_n_asw_x]%08X\n",ipv4_p);
		
	u_int16_t *temp1=&port_p;
	p=((u_int8_t*)temp1);	
	printf("[port_n_cbc_x]%02X",*p);
	p++;
	printf("%02X\n",*p);//逐字节输出0x
	printf("[port_n_asw_x]%04X\n",port_p);
	printf("[port_n_asw_d]%u\n",port_p);
	
}
void myprint2(u_int32_t ipv4_p,u_int16_t port_p){
	u_int8_t *p;
	u_int32_t *temp=&ipv4_p;
	p=((u_int8_t*)temp);
	printf("[ipv4_h_cbc_d]");
	for(int i=0;i<3;++i){
		printf("%u",*p);
		printf(".");
		p++;
	}
	printf("%u\n",*p);//逐字节输出
	p=((u_int8_t*)temp);
	printf("[ipv4_h_cbc_x]");
	for(int i=0;i<3;++i){
		printf("%02X",*p);
		p++;
	}
	printf("%02X\n",*p);//逐字节输出0x
	printf("[ipv4_h_asw_x]%08X\n",ipv4_p);
		
	u_int16_t *temp1=&port_p;
	p=((u_int8_t*)temp1);	
	printf("[port_h_cbc_x]%02X",*p);
	p++;
	printf("%02X\n",*p);//逐字节输出0x
	printf("[port_h_asw_x]%04X\n",port_p);
	printf("[port_h_asw_d]%u\n",port_p);
	
}
int main(int argc, char *argv[])
{
	u_int32_t ipv4_h,ipv4_n,*t1;
	u_int16_t port_h,port_n; 
	u_int8_t *p;
	int i=0;
	u_int8_t num=0;
	t1=&ipv4_n;
	p=(u_int8_t*)t1;
	while(argv[1][i]!='\0'){
		if(argv[1][i]=='.'){
			*p=num;
			p++;
			num=0;
		}else{
			num=num*10+(u_int8_t)(argv[1][i]-'0');
		}
		i++;	
	}//将ipv4_n中存入值 
	*p=num;
	i=0;
	u_int16_t temp=0;
	while(argv[2][i]!='\0'){
		temp=temp*10+(u_int16_t)(argv[2][i]-'0');
		i++; 
	}
	port_n=htons(temp);//存入端口号网络字节序；
	port_h=ntohs(port_n);
	ipv4_h=ntohl(ipv4_n);
	myprint1(ipv4_n,port_n);
	myprint2(ipv4_h,port_h);
	return 0;
}



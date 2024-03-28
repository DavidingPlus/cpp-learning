#include <stdio.h>
typedef unsigned int u_int32_t;
typedef unsigned short int u_int16_t;
u_int32_t getnum(char m){
	if(m>='a'&&m<='f'){
		return (m-'a')+10;
	}else if(m>='A'&&m<='F'){
		return (m-'A'+10);
	}else if(m>='0'&&m<='9'){
		return m-'0';
	}else{
		return -1;
	}
}
int main(int argc, char *argv[])
{
	int i=0;
	u_int32_t checksum=0,temp=0;
	while(argv[1][i]!='\0'){
		if(i%4==0){
			checksum=checksum+temp;
			if(checksum>0xffff){
				checksum=checksum%0x10000+checksum/0x10000;
			}
			temp=getnum(argv[1][i]);
		}else{
			if(getnum(argv[1][i])>=0){
				temp=temp*16+getnum(argv[1][i]);
			}else{
				printf("Wrong input!Please check your input!\n");
				return 0;
			}
		}
		i++;
	} 
	while(i%4!=0){
		temp=temp*16;
		++i;
	}
	checksum=checksum+temp;
	if(checksum>0x10000){	
	checksum=checksum%0x10000+checksum/0x10000;
	}
	u_int16_t check=(u_int16_t)~checksum;
	printf("%04x\n",check);
	return 0;
}
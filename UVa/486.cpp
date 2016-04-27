#include<stdio.h>
#include<string.h>
using namespace std;
char table[35][20] = {
	"zero","one","two","three","four","five","six","seven","eight","nine","ten",
	"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty",
	"thirty","forty","fifty","sixty","seventy","eighty","ninety",
	"hundred","thousand","million","negative"
};
bool getstr(char*);
int inTable(char*);
int main(){
	char *val = new char[20];
	int total, negative;
	bool haveNext,zero;
	while(1){
		total = 0, negative =1,zero=0;
		int now=0;
		do{
			haveNext = getstr(val);
			int proc = inTable(val);
			if(total==0 && proc==0){
				zero=1;
				break;
			} 
			if(proc<=20) now+=proc;
			else if(proc<28) now+=(proc-18)*10;
			else if(proc==28){
				now*=100;
			} 
			else if(proc==29){
				total+=now*1000;
				now=0;
			}
			else if(proc==30){
				total+=now*1000000;
				now=0;
			}
			else negative =-1;
		}while( haveNext );
		total+=now;
		if(zero){
			printf("0\n");
			continue;
		} 
		if(total==0) break;
		total*= negative;
		printf("%d\n",total);
	}
}

bool getstr(char line[]){
	char cc; int top=-1;
	cc = getchar();
	while( cc==' ' ) cc = getchar();
	while( cc!=' ' && cc!='\n' ){
		line[++top] = cc;
		cc = getchar();
	}
	line[++top] = '\0';
	if( cc=='\n' ){
		return false;
	}
	return true;
}
int inTable(char str[]){
	for(int i=0;i<32;++i){
		if( strcmp(str,table[i])==0 ) return i;
	}
	return -1;
}

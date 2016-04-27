#include<cstdio>
using namespace std;
int main(){
	int mem[100] , p;
	char str[100005];
	int t , nCase = 0;
	scanf(" %d",&t);
	while( ++nCase<=t ){
		scanf(" %s",str);
		printf("Case %d:",nCase);
		for(int i=0;i<100;++i) mem[i] = 0;
		p = 0;
		for(int i=0;str[i]!='\0';++i){
			if( str[i]=='>' ){
				if( ++p==100 ) p=0;
			}
			else if( str[i]=='<' ){
				if( --p==-1 ) p=99;
			}
			else if( str[i]=='+' ){
				if( ++mem[p]==256 ) mem[p]=0;
			}
			else if( str[i]=='-' ){
				if( --mem[p]==-1 ) mem[p]=255;
			}
		}
		for(int i=0;i<100;++i)
			printf(" %02X",mem[i]);
		printf("\n");
	}
} 

#include<cstdio>
using namespace std;
int main(){
	char fir[10000] , op[5];
	char ans[10000];
	long long sec;
	while( scanf(" %s%s%lld",fir,op,&sec)!=EOF ){
		long long r = 0;
		int i;
		for(i=0;fir[i]!='\0';++i){
			r = r*10 + fir[i]-'0';
			ans[i] = r/sec + '0';
			r %= sec;
		}
		if( op[0]=='/' ){
			int pp = 0;
			while( ans[pp]=='0' ) ++pp;
			if( pp>=i ) putchar('0');
			while( pp<i ) putchar( ans[pp++] );
			putchar('\n');
		}
		else{
			printf("%lld\n",r);
		}
	}
}

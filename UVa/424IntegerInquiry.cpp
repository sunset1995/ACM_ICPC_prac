#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char number[500];
	int sum[500];
	memset(sum,0,sizeof(sum));
	while( scanf(" %s",number)!=EOF ){
		if( number[1]=='\0' && number[0]=='0' ) break;
		int len = strlen(number);
		int mul = 1 , id = len-1;
		for(int i=0;i<len;++i,--id){
			if( i%5==0 ) mul = 1;
			else mul *= 10; 
			sum[ i/5 ] += (number[ id ]-'0')*mul;
		}
	}
	int top = 0;
	for(int i=0;i<500;++i){
		if(sum[i]==0) continue;
		top = i;
		if( sum[i]>=100000 ){
			sum[i+1] += sum[i]/100000;
			sum[i] %= 100000;
		}
	}
	printf("%d",sum[top--]);
	while(top>=0){
		printf("%05d",sum[top--]);
	}
	printf("\n");
	return 0;
} 

#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char R[10];
	int N;
	int base[10],sum[200],tmp[200],top;
	while( scanf(" %s%d",R,&N)!=EOF ){
		memset( sum , 0 , sizeof(sum) );
		int len = strlen(R) , point = len;
		top = -1;
		for(int i=len-1;i>=0;--i){
			if( R[i]>='0' && R[i]<='9' )
				base[++top] = R[i]-'0' , sum[top] = base[top];
			else if( R[i]=='.' ) point = i;
		}
		point = len-1-point;
		point*= N;
		len = top;
		for(int t=1;t<N;++t){
			for(int i=0;i<=top;++i) tmp[i] = sum[i] ,sum[i] = 0;
			for(int i=0;i<=top;++i){
				for(int j=0;j<=len;++j){
					sum[i+j] += tmp[i]*base[j];
				}
			}
			top += len;
			int next = 0;
			for(int i=0;i<=top;++i){
				sum[i] += next;
				next = sum[i]/10;
				sum[i] %= 10;
			}
			while( next!=0 ){
				sum[++top] += next%10;
				next/=10;
			}
		}
		int until = 0;
		while( sum[until]==0 ) ++until;
		int from = top;
		while( sum[from]==0 ) --from;
		for( ;from>=point;--from) printf("%d",sum[from]);
		if( point-1>=until ){
			printf(".");
			for(int i=point-1;i>=until;--i) printf("%d",sum[i]);
		}
		printf("\n");
	} 
}

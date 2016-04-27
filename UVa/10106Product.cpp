#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	char X[251],Y[251];
	int ans[501];
	while( scanf(" %s%s",X,Y)!=EOF ){
		int Xl = strlen(X) , Yl = strlen(Y);
		memset( ans , 0 , sizeof(ans) );
		for(int i=0;i<Xl;++i){
			for(int j=0;j<Yl;++j){
				ans[i+j] += (X[Xl-1-i]-'0')*(Y[Yl-1-j]-'0');
			}
		}
		int top = 0;
		for(int i=0;i<500;++i){
			if( ans[i] ){
				top = i;
				ans[i+1] += ans[i]/10;
				ans[i] %= 10;
			}
		}
		if( ans[501] ) top = 501;
		do{
			printf("%d",ans[top]);
			--top;
		}while(top>=0);
		printf("\n");
	}
}

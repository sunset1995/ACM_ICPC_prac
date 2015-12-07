#include <cstdio>
#include <cstring>
using namespace std;

int dp[10004];

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		memset(dp , 0 , sizeof(dp));
		int N,M,K;
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0,a ; i<N ; ++i){
			scanf("%d",&a);
			for(int j=10000 ; j>=0 ; --j)
				if(j+a<=10000 && dp[j]>0 && dp[j+a]<K)
					dp[j+a] += dp[j];
			if( dp[a]<K ) ++dp[a];
		}
		//for(int i=0 ; i<=M ; ++i)
		//	if( dp[i] ) printf("%d %d\n",i,dp[i]);
		if( dp[M]>=K ) puts("ENOUGH");
		else printf("%d\n",dp[M]);
	}
	return 0;
}

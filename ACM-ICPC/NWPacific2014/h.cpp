#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int N , M;
int S[25];
int dp[5004];
int st[5004];

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		scanf("%d%d",&N,&M);
		for(int i=0 ; i<M ; ++i)
			scanf("%d",&S[i]);
		memset(dp , 0 , sizeof(dp));
		memset(st , 0 , sizeof(st));
		for(int i=1 ; i<=N ; ++i)
			for(int j=0 ; j<M ; ++j){
				int bid = i - S[j];
				if( bid<0 || bid>N ) continue;
				if( bid>0 && st[bid]==0 ) continue;
				dp[i] = max(dp[i] , st[bid] + S[j]);
				int nid = i + st[bid] + S[j];
				if( nid>=0 && nid<=N )
					st[nid] = max(st[nid] , st[bid] + S[j]);
			}
		if( dp[N] <= 0 ) printf("-1\n");
		else printf("%d\n",dp[N]);
	}
}
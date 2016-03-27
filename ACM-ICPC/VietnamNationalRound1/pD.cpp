#include <cstdio>
using namespace std;

bool notPrime[1000004];
int dp[1000004];

int main(){
	for(int i=2 ; i<=1000000 ; ++i){
		if( notPrime[i] ) continue;
		for(int j=i+i ; j<=1000000 ; j+=i)
			notPrime[j] = true;
	}
	dp[1] = 1;
	for(int i=2 ; i<=1000000 ; ++i){
		if( !notPrime[i] ) dp[i] = dp[i-1]+1;
		else dp[i] = dp[i-1];
	}
	int NCASE;
	scanf("%d",&NCASE);
	int N;
	for(int NOWCASE = 1 ; NOWCASE<=NCASE ; ++NOWCASE){
		scanf("%d",&N);
		printf("Case #%d: %d\n",NOWCASE,dp[N]);
	}
	return 0;
}

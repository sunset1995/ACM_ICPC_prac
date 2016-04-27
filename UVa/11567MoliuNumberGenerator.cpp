#include<cstdio>
#include<map>
using namespace std;

int min(int a,int b){
	return (a<b)? a:b;
}
map<long long,int> dp;
int DandC(long long from){
	if( dp.find(from)!=dp.end() ){
		return dp[from];
	}
	if( (from&1)==0 ){
		dp[from] = DandC(from>>1) +1;
		return dp[from];
	}
	dp[from] = min( DandC(from-1) , DandC(from+1) ) +1;
	return dp[from];
}

int main(){
	long long S;
	dp[0] = 0, dp[1] = 1, dp[2] = 2;
	while( scanf(" %lld",&S)!=EOF ){
		int operation = DandC(S);
		printf("%d\n",operation);
	}
}

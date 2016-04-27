/* It takes 1.863s to get the AC */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int infinite = 1023456789;

int dp[254][254];
int prefixSum[254];

int P(const int &i, const int &j) {
	if( i>j ) return 0;
	return prefixSum[j] - prefixSum[i-1];
}

int gogogo(const int &i, const int &j) {
	if( i>=j ) return 0;
	if( dp[i][j]!=-1 ) return dp[i][j];
	dp[i][j] = infinite;
	for(int k=i; k<=j; ++k)
		dp[i][j] = min(dp[i][j],
			gogogo(i, k-1)+P(i, k-1)
			+gogogo(k+1, j)+P(k+1, j));
	return dp[i][j];
}

int main() {
	int n;
	while( scanf("%d", &n)!=EOF ) {
		memset(prefixSum, 0, sizeof(prefixSum));
		for(int i=1; i<=n; ++i) {
			scanf("%d", &prefixSum[i]);
			prefixSum[i] += prefixSum[i-1];
		}
		memset(dp, -1, sizeof(dp));
		printf("%d\n", gogogo(1, n));
	}
	return 0;
}

/* It takes 0.979s to get the AC */

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

void gogogo(const int &n) {
	for(int len=2; len<=n; ++len) {
		for(int i=1,j=i+len-1; j<=n; ++i, j=i+len-1) {
			dp[i][j] = infinite;
			for(int k=i; k<=j; ++k)
				dp[i][j] = min(dp[i][j],
					dp[i][k-1]+P(i, k-1)
					+dp[k+1][j]+P(k+1, j));
		}
	}
}

int main() {
	int n;
	while( scanf("%d", &n)!=EOF ) {
		memset(prefixSum, 0, sizeof(prefixSum));
		for(int i=1; i<=n; ++i) {
			scanf("%d", &prefixSum[i]);
			prefixSum[i] += prefixSum[i-1];
		}
		gogogo(n);
		printf("%d\n", dp[1][n]);
	}
	return 0;
}

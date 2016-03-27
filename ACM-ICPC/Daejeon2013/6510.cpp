#include <cstdio>
#include <algorithm>
using namespace std;

int dp[2][100000];

int main() {
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n;
		scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", &dp[0][i]);
		for(int i=0; i<n; ++i) scanf("%d", &dp[1][i]);
		dp[0][1] += dp[1][0];
		dp[1][1] += dp[0][0];
		for(int i=2; i<n; ++i) {
			dp[0][i] += max(dp[1][i-1], dp[1][i-2]);
			dp[1][i] += max(dp[0][i-1], dp[0][i-2]);
		}
		printf("%d\n",max(dp[0][n-1], dp[1][n-1]));
	}
	return 0;
}

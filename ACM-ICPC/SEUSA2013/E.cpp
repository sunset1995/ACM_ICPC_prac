#include <cstdio>
#include <cstring>
using namespace std;

const long long mod = 1000000007LL;
long long fac[5004], facR[5004];
long long dp[5004][5004];

long long modInv(long long val) {
	long long x = mod - 2;
	long long res = 1LL;
	while( x ) {
		if( x&1LL ) res = res * val % mod;
		val = val * val % mod;
		x >>= 1;
	}
	return res;
}
long long C(int n, int r) {
	return fac[n]*facR[r] %mod *facR[n-r] %mod;
}

int main() {
	fac[0] = fac[1] = 1LL;
	for(int i=2; i<5004; ++i)
		fac[i] = fac[i-1] * i % mod;
	for(int i=0; i<5004; ++i)
		facR[i] = modInv(fac[i]);
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int i=1; i<5004; ++i)
		for(int j=1; j<=i; ++j)
			dp[i][j] = (dp[i-1][j-1] + (i-1)*dp[i-1][j]) % mod;

	int n, left, right;
	while( scanf("%d%d%d", &n, &left, &right)!=EOF ) {
		if( !n && !left && !right ) break;
		long long ans = 0LL;
		for(int i=1; i<=n; ++i)
			ans = (ans + C(n-1, i-1)*dp[i-1][left-1]%mod*dp[n-1-(i-1)][right-1]%mod)%mod;
		printf("%lld\n", ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool dp[1000004];

int main() {
	int n, a[104];
	scanf("%d",&n);
	while( n-- ) {
		int m,s,k, bsum=0, csum=0;
		scanf("%d%d%d",&m,&s,&k);
		for(int i=0,b,c ; i<m ; ++i) {
			scanf("%d%d%d",&a[i],&b,&c);
			bsum += b;
			csum += c;
		}
		sort(a, a+m);
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		int asum = 0;
		for(int i=0 ; i<k ; ++i) {
			asum += a[i];
			for(int j=bsum ; j>=a[i] ; --j)
				if( dp[j-a[i]] )
					dp[j] = 1;
		}
		int bwin = bsum;
		while( !dp[bwin] ) --bwin;
		puts( asum-bwin<=csum? "YES" : "NO" );
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <deque>
using namespace std;

long long dp[2][50004];

int main() {
	int a[104];
	int n, k, phi;
	while( scanf("%d",&n)!=EOF && n ) {
		memset(dp, -1, sizeof(dp));
		scanf("%d%d",&k,&phi);
		for(int i=0 ; i<n ; ++i)
			scanf("%d",&a[i]);
		for(int i=k ; i>=0 ; --i)
			dp[0][i] = 1LL*(i-a[n-1])*(i-a[n-1]);
		int now = 0;
		for(int i=n-2 ; i>=0 ; --i) {
			int next = (now+1) % 2;
			memset(dp[next], -1, sizeof(dp[next]));
			deque<long long> asc;
			deque<long long> id;
			for(int j=k ; j>=0 ; --j) {
				while( id.size() && (*(id.begin()))-j > phi ) {
					id.pop_front();
					asc.pop_front();
				}
				if( dp[now][j]!=-1 ) {
					while( asc.size() && (*(asc.rbegin()))>=dp[now][j] ) {
						asc.pop_back();
						id.pop_back();
					}
					asc.push_back(dp[now][j]);
					id.push_back(j);
				}
				if( asc.size() ) {
					long long myCost = 1LL*abs(j-a[i])*abs(j-a[i]);
					dp[next][j] = myCost + (*(asc.begin()));
				}
			}
			now = next;
		}
		long long ans = -1LL;
		for(int i=0 ; i<=k ; ++i)
			if( dp[now][i]!=-1 && (dp[now][i]<ans || ans==-1LL) )
				ans = dp[now][i];
		printf("%lld\n",ans);
	}
	return 0;
}

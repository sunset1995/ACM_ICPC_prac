#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define N 500010
using namespace std;
long long sum[N] , a[N] , X ;
int bit[N] , n ;
int lowbit(int x) {
	return x & (-x) ;
}
void update(int x,int v) {
	for( ; x<=n ; x+=lowbit(x))
		bit[x] = max(bit[x],v) ;
}
int query(int x) {
	int ans = -1e9 ;
	for( ; x ; x-=lowbit(x))
		ans = max(ans,bit[x]) ;
	return ans ;
}
int getindex(long long c) {
	int ind = lower_bound(a,a+n,c)-a ;
	if(ind==n) return n-1 ;
	if(ind==0 && a[ind]>c) return -1 ;
	if(a[ind]>c) return ind-1 ;
	return ind ;
}
int main () {
	int t ;
	scanf("%d",&t) ;
	while(t--) {
		int ans=1e9 ;
		scanf("%d%lld",&n,&X) ;
		for(int i=0 ; i<=n ; i++)
			bit[i] = -1e9 ;
		for(int i=0 ; i<n ; i++) {
			scanf("%lld",&sum[i]) ;
			sum[i] += i>0 ? sum[i-1] : 0 ;
			a[i] = sum[i] ;
		}
		sort(a,a+n) ;
		for(int i=0 ; i<n ; i++) {
			long long c = sum[i]-X ;
			int ind = getindex(c) ;
			if(ind!=-1)
				ans = min(ans , i-query(ind+1));
			update(getindex(sum[i])+1,i) ;
		}
		if(ans!=1e9) printf("%d\n",ans) ;
		else puts("-1");
	}
}

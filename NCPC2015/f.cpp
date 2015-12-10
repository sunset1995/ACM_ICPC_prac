#include <cstdio>
#include <vector>
using namespace std;

int n, p;
long long mtx[104][104];
long long inverse(long long x) {
	int n = p-2;
	long long res = 1LL;
	while( n ) {
		if( n&1LL ) res = res*x % p;
		x = x*x % p;
		n>>=1;
	}
	return res;
}
void reduce(int base,int col) {
	long long inv = inverse(mtx[base][col]);
	for(int i=0 ; i<n ; ++i) {
		if( i==base ) continue;
		long long multi = (p-mtx[i][col])*inv % p;
		for(int j=0 ; j<=n ; ++j)
			mtx[i][j] = (mtx[i][j] + mtx[base][j]*multi%p) % p;
	}
}

int main() {
	scanf("%d",&p);
	while( scanf("%d",&n)!=EOF && n ) {
		for(int i=0 ; i<n ; ++i) {
			long long x,y;
			scanf("%lld%lld",&x,&y);
			x%=p, y%=p;
			long long v = 1LL;
			for(int j=0 ; j<n ; ++j) {
				mtx[i][j] = v;
				v = v*x % p;
			}
			mtx[i][n] = y;
		}
		for(int i=0 ; i<n ; ++i) {
			int id = 0;
			while( id<n ) {
				bool allzero = true;
				for(int j=0 ; j<i ; ++j)
					allzero = allzero && !mtx[id][j];
				if( allzero && mtx[id][i] ) break;
				++id;
			}
			if( id>=n ) continue;
			reduce(id, i);
		}
		printf("%lld\n",mtx[0][n]);
	}
	return 0;
}

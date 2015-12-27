#include <cstdio>
using namespace std;

int mp[104][104];

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int m, n;
		scanf("%d%d", &m, &n);
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				scanf("%d", &mp[i][j]);
		int cnt = 0;
		for(int id=0; id<n; ++id) 
			for(int i=m-1,j=m-1; i>=0; --i)
				if( mp[i][id] ) {
					cnt += j-i;
					--j;
				}
		printf("%d\n",cnt);
	}
	return 0;
}

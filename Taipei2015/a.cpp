#include <cstdio>
using namespace std;

int main() {
	char str[104];
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n;
		scanf("%d%s", &n, str);
		int left=0, ans=0;
		for(int i=0; i<n; ++i)
			if( str[i]=='(' )
				++left;
			else {
				if( left==0 ) ++ans, left=1;
				else --left;
			}
		ans += left>>1;
		printf("%d\n", ans);
	}
	return 0;
}

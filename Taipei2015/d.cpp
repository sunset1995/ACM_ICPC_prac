#include <cstdio>
using namespace std;

int main() {
	int p;
	scanf("%d", &p);
	int a, b;
	while( scanf("%d", &a)!=EOF && a ) {
		scanf("%d", &b);
		int ans = 1;
		int x = a;
		while( x!=b ) {
			x = x*a % p;
			++ans;
			if( x==a ) {
				ans = 0;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

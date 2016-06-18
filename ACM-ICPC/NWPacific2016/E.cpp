#include <cstdio>
#include <algorithm>
using namespace std;

long long s[100004];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
		scanf("%I64d", &s[i]);
	sort(s, s+n);
	long long ans = s[0] + s[n-1];
	for(int i=1,j=n-2; i<j; ++i, --j)
		ans = min(ans, s[i]+s[j]);
	printf("%I64d\n", ans);
	return 0;
}

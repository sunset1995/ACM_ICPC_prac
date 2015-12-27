#include <cstdio>
using namespace std;

int main() {
	long long P[104] = {0,1,1,1,2,2,3,4,5,7,9};
	for(int i=11; i<=100; ++i)
		P[i] = P[i-1] + P[i-5];

	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n;
		scanf("%d", &n);
		printf("%lld\n", P[n]);
	}
	return 0;
}

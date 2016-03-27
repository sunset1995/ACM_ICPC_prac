#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define N 51
#define B 100
using namespace std;

long long GCD(long long a,long long b) {
	return b ? GCD(b, a%b) : a;
}
long long arr[N][N], m[N];

int main () {
	srand(time(NULL));
	int T, kase = 1;
	scanf("%d", &T);
	while(T--) {
		long long n, i, j, small = 0, big = 0;
		scanf("%lld", &n);
		for(i = 0; i < n; i++) {
			scanf("%lld", &m[i]);
			for(j = 0; j < m[i]; j++)
				scanf("%lld", &arr[i][j]);
			sort(arr[i], arr[i]+m[i]);
			small += arr[i][0];
			big += arr[i][m[i]-1]; 
		}
		long long gcd = GCD(small,big), cnt = 0;
		while(cnt++ <= B) {
			long long s = 0;
			for(i = 0; i < n; i++)
				s += arr[i][rand()%m[i]];
			gcd = GCD(gcd,s);
		}
		printf("Case #%d: %lld\n", kase++, gcd);
	}
}

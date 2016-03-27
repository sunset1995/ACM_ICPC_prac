#include <iostream>
#include <cstdio>
#define N 10010
using namespace std;
typedef long long ell;
long long x[N], y[N];
inline bool positive(ell vx,ell x1,ell x0,ell vy,ell y1,ell y0) {
	//printf("%lld %lld %lld %lld %lld %lld-----\n",vx,x1,x0,vy,y1,y0);
	if((vx * (x1 + vx - x0) + vy * (y1 + vy - y0)) > 0) {
		//printf("here1\n");
		return true;
	}
	if((vx * (x1 - x0) + vy * (y1 - y0)) > 0) {
		//printf("here2\n");
		return true;
	}
	return false;
}
inline bool test(int n) {
	for(int j = 1; j < n; j++)
		for(int i = 1; i <= j; i++)
			if(positive(x[i] - x[i-1],x[i-1],x[j],y[i] - y[i-1],y[i-1],y[j])) {
				//printf("%lld %d %d %d %d %d---\n", x[i] - x[i-1],x[i-1],x[n-1],y[i] - y[i-1],y[i-1],y[n-1]);
				return false;
			}
	return true;
}
int main () {
	int n;
	while(scanf("%d", &n)==1 && n) {
		for(int i = 0; i < n; i++)
			scanf("%lld%lld", &x[i], &y[i]);
		if(test(n))
			puts("Fair");
		else
			puts("Unfair");
	}
}

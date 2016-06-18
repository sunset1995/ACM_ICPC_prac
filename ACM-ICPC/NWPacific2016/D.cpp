#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main () {
	int a[4], b[4];
	while(scanf("%d%d%d%d%d%d", &a[0], &a[1], &a[2], &b[0], &b[1], &b[2])==6) {
		sort(a, a+3);
		sort(b, b+3);
		if(a[0] != b[0] || a[1] != b[1] || a[2] != b[2])
			puts("NO");
		else if(a[0]*a[0] + a[1]*a[1] != a[2]*a[2])
			puts("NO");
		else
			puts("YES");
	}
}

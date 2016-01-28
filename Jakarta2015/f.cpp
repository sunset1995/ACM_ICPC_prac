#include <iostream>
#include <cstdio>
#define N 106
using namespace std;

int main () {
	int T, kase = 1;
	scanf("%d", &T);
	while(T--) {
		int n, i, j, m[N][3];
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			for(j = 0; j < 3; j++)
				scanf("%d", &m[i][j]);
		int t = 0, a1 = 0, a2 = 0, a3 = 0, x1 = 105, x2 = 105, x3 = 105;
		while(true) {
			//printf("%d %d %d\n",x1,x2,x3);
			if(a1) a1--;
			if(!a1) m[x1][0] = 0;
			if(a2) a2--;
			if(!a2) m[x2][1] = 0;
			if(a3) a3--;
			if(!a3) m[x3][2] = 0;
			if(a1 == 0) {
				for(i = 0; i < n; i++)
					if(m[i][0])
						break;
				if(i != n) {
					a1 = m[i][0];
					x1 = i;
				}
			}
			if(a2 == 0) {
				for(i = 0; i < n; i++)
					if(m[i][0] == 0 && m[i][1])
						break;
				if(i != n) {
					a2 = m[i][1];
					x2 = i;
				}
			}
			if(a3 == 0) {
				for(i = 0; i < n; i++)
					if(m[i][0] == 0 && m[i][1] == 0 && m[i][2])
						break;
				if(i != n) {
					a3 = m[i][2];
					x3 = i;
				}
			}
			if(!a1 && !a2 && !a3)
				break;
			t++;
		}
		printf("Case #%d: %d\n",kase++,t);
	}
}

#include <iostream>
#include <cstdio>
#include <cmath>
#define N 151
using namespace std;
int G[N][N];
int main () {
	int n, s, t;
	while(scanf("%d%d%d", &n, &s, &t)==3 && n + t + s) {
		int mxf = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				G[i][j] = 1e9;
		for(int i = 0; i < n; i++) {
			int x, f[N];
			scanf("%d", &x);
			for(int j = 0; j < x; j++) {
				scanf("%d", &f[j]);
				mxf = max(mxf, f[j]);
				for(int k = 0; k < j; k++)
					G[f[k]][f[j]] = G[f[j]][f[k]] = abs(f[k]-f[j]);
			}
		}
		for(int k = 0; k <= mxf; k++)
			for(int i = 0; i <= mxf; i++)
				for(int j = 0; j <= mxf; j++)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
		printf("%d\n",G[s][t]);
	}
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 205
using namespace std;

struct pr {
	int i, j, len;
	bool operator < (const pr x) const {
		return len < x.len;
	}
};
vector<pr> vis;
int x[N], y[N], m[N][N], my[N][N];
int dis(int u,int v) {
	return (x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]);
}
int main () {
	int T, kase = 1;
	scanf("%d", &T);
	while(T--) {
		int n, i, j;
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &x[i]);
		for(i = 0; i < n; i++)
			scanf("%d", &y[i]);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &m[i][j]);
		vis.clear();
		for(i = 1; i < n; i++)
			for(j = 0; j < i; j++)
				vis.push_back(pr{i, j, dis(i, j)});
		sort(vis.begin(), vis.end());
		for(i = 0; i < n; i++) {
			memset(my[i], 0, sizeof(my[i]));
			my[i][i] = 1;
		}
		int Y, Z = 0, ansY = 0, ansZ = -1;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				Z += (my[i][j] != m[i][j]);
		ansZ = Z;
		//printf("%dAAAAAAAA\n",Z);
		for(i = 0; i < vis.size(); i++) {
			Y = vis[i].len;
			do {
				pr p = vis[i];
				if(m[p.i][p.j] == my[p.i][p.j])
					Z++;
				else
					Z--;
				if(m[p.j][p.i] == my[p.j][p.i])
					Z++;
				else
					Z--;
				my[p.i][p.j] = my[p.j][p.i] = 1;
			}while(i + 1 < vis.size() && vis[i+1].len == vis[i].len && ++i);
			if(ansZ == -1 || Z < ansZ) {
				ansZ = Z;
				ansY = Y;
			}
		}
		printf("Case #%d: %d %d\n", kase++, ansY, ansZ);
	}
}

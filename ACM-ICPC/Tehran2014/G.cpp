#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 320
using namespace std;
struct dragon {
	int s, nv;
	bool operator < (const dragon g) const {
		return nv > g.nv;
	}
};
vector<dragon> drag[N];
vector<int> G[N];
int pre[N];
void init() {
	for(int i = 0; i < N; i++) {
		pre[i] = -1;
		G[i].clear();
		drag[i].clear();
	}
}
void dfs(int u,vector<dragon> &d) {
	pre[u] = 1;
	for(int i = 0; i < drag[u].size(); i++)
		d.push_back(drag[u][i]);
	for(int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if(pre[v]==-1)
			dfs(v, d);
	}
}
bool enough(int k,vector<dragon> &v) {
	int kbegin = k, i;
	for(i = 0; i < v.size(); i++) {
		if(v[i].nv < kbegin)
			return k >= 0;
		k -= v[i].s;
	}
	return k>=0;
}
int Ans(vector<dragon> &v) {
	int L = 0, R = (v.size() ? v[0].nv+1 : 0);
	while(L < R) {
		int M = (L+R)/2;
		if(enough(M, v))
			R = M;
		else
			L = M+1;
	}
	return R;
}
int main () {
	int n, m, k;
	while(scanf("%d%d%d", &n, &m, &k)==3 && n + m + k) {
		int u, v, s, nv, ans = 0;
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for(int i = 1; i <= k; i++) {
			scanf("%d%d%d", &u, &s, &nv);
			drag[u].push_back(dragon{s, nv});
		}
		for(int i = 1; i <= n; i++)
			if(pre[i]==-1) {
				vector<dragon> comp;
				dfs(i, comp);
				sort(comp.begin(), comp.end());
				ans += Ans(comp);
			}
		printf("%d\n", ans);
	}
}

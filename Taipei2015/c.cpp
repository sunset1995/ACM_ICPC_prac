#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

vector<int> G[104];
char visited[104];

int dfs(int nowAt, int sink) {
	visited[nowAt] = 1;
	int res = nowAt==sink? 0 : 1;
	for(int i=0; i<G[nowAt].size(); ++i) {
		if( visited[G[nowAt][i]] ) continue;
		int req = dfs(G[nowAt][i], sink);
		if( res==0 ) continue;
		if( req==0 ) res=0;
		else res += req;
	}
	return res;
}

void init() {
	for(int i=0; i<104; ++i)
		G[i].clear();
}

int main() {
	int n;
	while( scanf("%d", &n)!=EOF && n ) {
		init();
		int sink, m;
		scanf("%d%d", &sink, &m);
		for(int i=0,u,v; i<m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		int ans = -1, crucial = 0;
		for(int i=1; i<=n; ++i) {
			if( i==sink ) continue;
			memset(visited, 0, sizeof(visited));
			visited[i] = 1;
			int nowCrucial = 0;
			for(int j=0; j<G[i].size(); ++j) {
				if( !visited[G[i][j]] ) {
					int tmp = dfs(G[i][j], sink);
					nowCrucial += tmp;
				}
			}
			if( ans==-1 || nowCrucial>crucial ) {
				crucial = nowCrucial;
				ans = i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

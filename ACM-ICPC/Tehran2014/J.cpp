#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
	int Pa = 0;
	vector<int> t = {};
};

int n, d, p;
Person ps[504];
const int start=0, sink=1003;
vector<int> g[1004];
int G[1004][1004];
bool visited[1004];

int dfs(int nowAt, int nowFlow) {
	if( nowAt==sink )
		return nowFlow;
	visited[nowAt] = 1;
	int res = 0;
	for(auto i : g[nowAt]) {
		if( G[nowAt][i]<=0 || visited[i] )
			continue;
		int req = dfs(i, min(nowFlow-res, G[nowAt][i]));
		G[nowAt][i] -= req;
		G[i][nowAt] += req;
		res += req;
		if( res == nowFlow ) break;
	}
	return res;
}

int maxFlow() {
	int res = 0;
	while( true ) {
		memset(visited, 0, sizeof(visited));
		int req = dfs(start, d);
		res += req;
		if( req==0 || res==d ) break;
	};
	return res;
}

bool ok(int Ea) {
	memset(G, 0, sizeof(G));
	for(int i=1; i<=d; ++i)
		G[start][i] = 1;
	for(int i=1; i<=n; ++i)
		G[i+500][sink] = (ps[i].Pa+Ea) / p;
	for(int i=1; i<=n; ++i)
	for(auto t : ps[i].t)
		G[t][i+500] += 1023456789;
	return maxFlow()>=d;
}

void init() {
	for(int i=0; i<504; ++i)
		ps[i] = Person();
	for(int i=0; i<1004; ++i)
		g[i].clear();
	for(int i=1; i<=d; ++i)
		g[start].emplace_back(i);
	for(int i=1; i<=n; ++i)
		g[i+500].emplace_back(sink);
}

int main() {
	while( scanf("%d%d%d", &n, &d, &p)!=EOF ) {
		if( !n && !d && !p ) break;
		init();
		for(int i=1,num; i<=d; ++i) {
			scanf("%d", &num);
			int todayPa = p / num;
			for(int j=0,id; j<num; ++j) {
				scanf("%d", &id);
				ps[id].t.emplace_back(i);
				ps[id].Pa += todayPa;
				g[i].emplace_back(id+500);
				g[id+500].emplace_back(i);
			}
		}
		int l=0, r=p;
		while( l<r ) {
			int c = (l+r)/2;
			if( ok(c) )
				r = c;
			else l = c+1;
		}
		printf("%d\n", l);
	}
	return 0;
}

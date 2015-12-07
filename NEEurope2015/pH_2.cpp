#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> g[50004];
bool remarkale[50004];
bool visited[50004];

struct route {
	vector<int> a, b;
	route()
	:a(), b(){}
};
vector<route> ans;

vector<int> dfs(int nowAt,int parent) {
	visited[nowAt] = true;
	vector<int> last;
	if( remarkale[nowAt] )
		last.emplace_back(nowAt);
	for(auto &v : g[nowAt]) {
		if( v == parent ) continue;
		if( visited[v] ) continue;
		vector<int> nowR = move(dfs(v, nowAt));
		if( nowR.empty() ) continue;
		nowR.emplace_back(nowAt);
		if( last.size() ) {
			ans.emplace_back(route());
			ans.back().a = move(last);
			ans.back().b = move(nowR);
		}
		else last.swap(nowR);
	}
	return last;
}

int main() {
	int n, m, k;
	scanf("%d%d%d", &n ,&m ,&k);
	for(int i=0,a,b ; i<m ; ++i) {
		scanf("%d%d", &a, &b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	for(int i=0,a ; i<k ; ++i) {
		scanf("%d", &a);
		remarkale[a] = true;
	}
	for(int i=1 ; i<=n ; ++i)
		if( !visited[i] )
			dfs(i,-1);
	printf("%d\n",(int)ans.size());
	for(auto &r: ans) {
		printf("%d",(int)r.a.size()+(int)r.b.size()-2);
		for(int i=0 ; i<r.a.size() ; ++i)
			printf(" %d",r.a[i]);
		for(int i=r.b.size()-2 ; i>=0 ; --i)
			printf(" %d",r.b[i]);
		puts("");
	}
	return 0;
}

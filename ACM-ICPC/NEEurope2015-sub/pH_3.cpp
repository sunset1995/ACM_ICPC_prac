#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

vector<int> g[50004];
bool remarkale[50004];
bool visited[50004];

int routeNum;
int dfsCount(int nowAt,int parent) {
	visited[nowAt] = true;
	bool last = remarkale[nowAt];
	for(auto &v : g[nowAt]) {
		if( v == parent ) continue;
		if( visited[v] ) continue;
		if( !dfsCount(v, nowAt) ) continue;
		if( last ) ++routeNum;
		last = !last;
	}
	return last;
}

vector<int> retval;
void dfsFindRoute(int nowAt,int parent) {
	visited[nowAt] = true;
	vector<int> last;
	if( remarkale[nowAt] )
		last.emplace_back(nowAt);
	for(auto &v : g[nowAt]) {
		if( v == parent ) continue;
		if( visited[v] ) continue;
		dfsFindRoute(v, nowAt);
		if( retval.empty() ) continue;
		retval.emplace_back(nowAt);
		if( last.size() ) {
			printf("%d",last.size()+retval.size()-2);
			for(int i=0 ; i<last.size() ; ++i)
				printf(" %d",last[i]);
			for(int i=retval.size()-2 ; i>=0 ; --i)
				printf(" %d",retval[i]);
			puts("");
			last.clear();
		}
		else last = retval;
	}
	retval = last;
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
			dfsCount(i,-1);
	printf("%d\n",routeNum);
	memset(visited, 0, sizeof(visited));
	for(int i=1 ; i<=n ; ++i)
		if( !visited[i] )
			dfsFindRoute(i,-1);
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
#define N 1010
using namespace std;

int ind[N] , visited[N] ;
vector<int> G[N] , p[N] ;
void init() {
	for(int i=0 ; i<N ; i++) {
		G[i].clear() ;
		p[i].clear() ;
		ind[i] = visited[i] = 0 ;
	}
}
bool goleft(int at) {
	int i , cnt=0 ;
	for(i=at ; i>0 ; i--) {
		cnt += visited[i] ;
		if(p[i].size() && *(p[i].rbegin())>at)
			return false ;
	}
	return cnt!=0 ;
}
void del(int u,int who) {
	int i ;
	ind[u]-- ;
	for(i=0 ; i<p[u].size() ; i++)
		if(p[u][i]==who) {
			p[u].erase(p[u].begin()+i) ;
			return ;
		}
}
int main () {
	int n , m ;
	while(scanf("%d%d",&n,&m)==2) {
		int i , u , v , nowat=0 , cnt=0 ;
		init() ;
		for(i=0 ; i<m ; i++) {
			scanf("%d%d",&u,&v) ;
			G[v].push_back(u) ;
			p[u].push_back(v) ;
			visited[u] = visited[v] = true ;
			ind[u] ++ ;
		}
		for(i=0 ; i<n ; i++)
			sort(p[i].begin(),p[i].end()) ;
		while(nowat <= n) {
			for(i=0 ; i<G[nowat].size() ; i++) {
				v = G[nowat][i] ;
				del(v,nowat) ;
			}
			G[nowat].clear() ;
			visited[nowat] = 0 ;
			if(goleft(nowat)) {
				for(i=nowat ; i>=1 ; i-- , cnt++)
					if(visited[i]) {
						nowat = i ;
						break ;
					}
			} else {
				for(i=nowat ; i<=n ; i++ , cnt++)
					if(visited[i] && p[i].size()==0)
						break ;
				nowat = i ;
			}
		}
		printf("%d\n",cnt) ;
	}
}

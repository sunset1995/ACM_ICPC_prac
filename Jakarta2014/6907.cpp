#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#define M 5000
using namespace std;
struct edge {
	int u , v , id ;
} ;
vector<edge> G[104] , lst ;
bool isbg[M] ;
int pre[104] , low[104] , timestamp ;
void init() {
	for(int i=0 ; i<104 ; i++)
		G[i].clear() ;
	memset(pre,-1,sizeof(pre)) ;
	memset(isbg,false,sizeof(isbg)) ;
	lst.clear() ;
	timestamp = 1 ;
}
void dfs(int u,int f) {
	int i , v ;
	pre[u] = low[u] = timestamp++ ;
	for(i=0 ; i<G[u].size() ; i++) {
		v = G[u][i].v ;
		if(v!=f && pre[v]==-1) {
			dfs(v,u) ;
			low[u] = min(low[u],low[v]) ;
			if(low[v]>pre[u])
				isbg[G[u][i].id] = true ;
		} else if(v!=f)
				low[u] = min(low[u],pre[v]) ;
	}
}
pair<int,int> dfs2(int u,int f,int forbid) {
	int i , v ;
	pre[u] = 1 ;
	pair<int,int> pr(1,0) , son ;
	for(i=0 ; i<G[u].size() ; i++) {
		v = G[u][i].v ;
		if(G[u][i].id!=forbid) pr.second++ ;
		if(v!=f && pre[v]==-1 && G[u][i].id!=forbid) {
			son = dfs2(v,u,forbid) ;
			pr.first += son.first ;
			pr.second += son.second ;
		}
	}
	return pr ;
}
bool completeGraph(pair<int,int> a,pair<int,int> b) {
	return a.first*(a.first-1) == a.second && 
			 b.first*(b.first-1) == b.second ;
}
int main () {
	int t , kase=1 ;
	scanf("%d",&t) ;
	while(t--) {
		int n , m , i , u , v , ans=0 ;
		scanf("%d%d",&n,&m) ;
		init() ;
		for(i=0 ; i<m ; i++) {
			scanf("%d%d",&u,&v) ;
			G[u].push_back(edge{u,v,i}) ;
			G[v].push_back(edge{v,u,i}) ;
			lst.push_back(edge{u,v,i}) ;
		}
		for(i=1 ; i<=n ; i++)
			if(pre[i]==-1)
				dfs(i,-1) ;
		for(i=0 ; i<lst.size() ; i++)
			if(isbg[i]) {
				memset(pre,-1,sizeof(pre)) ;
				pair<int,int> left = dfs2(lst[i].u,-1,i) ;	// parie<node,edge>
				pair<int,int> right= dfs2(lst[i].v,-1,i) ;	// parie<node,edge>
				if(left.first==right.first && completeGraph(left,right))
					ans++ ;
			}
		printf("Case #%d: %d\n",kase++,ans) ;
	}
}

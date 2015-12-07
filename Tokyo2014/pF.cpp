#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 510
using namespace std;
struct edge {
	int u , v , w , use ;
	bool operator < (const edge x) const {
		return w < x.w ;
	}
} ;
vector<edge> E , G[N] ;
int f[N] , d[N] ;
edge fE[N] ;
void init() {
	E.clear() ;
	for(int i=0 ; i<N ; i++) {
		G[i].clear() ;
		f[i] = i ;
		d[i] = -1 ;
	}
}
int find(int u) {
	if(f[u]==u)
		return f[u] ;
	return f[u] = find(f[u]) ;
}
bool Union(int u,int v) {
	int fu = find(u) , fv = find(v) ;
	if(fu!=fv) {
		f[fu] = fv ;
		return true ;
	}
	return false ;
}
int Kruskal(int n) {
	int group = n , sum=0 , i ;
	sort(E.begin(),E.end()) ;
	for(i=0 ; i<E.size() && group!=1 ; i++)
		if(Union(E[i].u,E[i].v)) {
			group-- ;
			G[E[i].u].push_back(E[i]) ;
			swap(E[i].u,E[i].v) ;
			G[E[i].u].push_back(E[i]) ;
			E[i].use = 1 ;
			sum += E[i].w ;
		}
	return sum ;
}
void dfs(int u,int deep) {
	d[u] = deep ;
	for(int i=0 ; i<G[u].size() ; i++)
		if(d[G[u][i].v]==-1) {
			fE[G[u][i].v] = G[u][i] ;
			dfs(G[u][i].v,deep+1) ;
		}
}
void count(int u,int v,int w,int &cost,int &Enum) {
	while(u!=v) {
		int du = d[u] , dv = d[v] ;
		if(du >= dv) {
			if(fE[u].use==0 && fE[u].w==w) {
				cost -= w ;
				Enum-- ;
				fE[u].use = 1 ;
			}
			u = fE[u].u ;
		} else if(du <= dv) {
			if(fE[v].use==0 && fE[v].w==w) {
				cost -= w ;
				Enum-- ;
				fE[v].use = 1 ;
			}
			v = fE[v].u ;
		}
	}
}
int main () {
	int n , m ;
	while(scanf("%d%d",&n,&m)==2) {
		int u , v , w , i , cost=0 , Enum=n-1 ;
		init() ;
		for(i=0 ; i<m ; i++) {
			scanf("%d%d%d",&u,&v,&w) ;
			E.push_back(edge{u,v,w,0}) ;
		}
		cost = Kruskal(n) ;
		dfs(1,1) ;
		for(i=0 ; i<E.size() ; i++)
			if(E[i].use==0)
				count(E[i].u,E[i].v,E[i].w,cost,Enum) ;
		printf("%d %d\n",Enum,cost) ;
	}
}

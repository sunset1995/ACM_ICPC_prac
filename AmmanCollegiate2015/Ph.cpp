#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N,M;
vector<int> g[100004];
int tid[100004] , top;
vector<int> tree[100004];
int inT[100004] , nowT;
int low[100004];

int root[100004];
int findRoot(int from){
	if( from==root[from] ) return from;
	return root[from] = findRoot( root[from] );
}

void init(){
	for(int i=0;i<=N;++i){
		g[i].clear();
		tree[i].clear();
		tid[i] = -1;
		top = -1;
		inT[i] = -1;
		nowT = 0;
		root[i] = i;
	}
}

void findBridge(int nowAt,int parent){
	low[nowAt] = inT[nowAt] = ++nowT;
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( inT[ g[nowAt][i] ] == -1 )
			findBridge( g[nowAt][i] , nowAt );
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( inT[ g[nowAt][i] ] > inT[nowAt] )
			low[nowAt] = min(low[nowAt] , low[ g[nowAt][i] ]);
	for(int i=0 ; i<g[nowAt].size() ; ++i)
		if( inT[ g[nowAt][i] ] > inT[nowAt] && low[ g[nowAt][i] ] <= inT[nowAt] ){
			int rootId = findRoot( g[nowAt][i] );
			root[ rootId ] = findRoot( nowAt );
		}
}

void findTreeFarest(int nowAt,int parent,int nowD,int &farestP,int &maxD){
	if( nowD > maxD ){
		farestP = nowAt;
		maxD = nowD;
	}
	for(int i=0;i<tree[nowAt].size();++i){
		if( tree[nowAt][i]==parent )
			continue;
		findTreeFarest(tree[nowAt][i] , nowAt , nowD+1 , farestP , maxD);
	}
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		init();
		scanf(" %d%d",&N,&M);
		for(int i=0,x,y;i<M;++i){
			scanf(" %d%d",&x,&y);
			g[x].push_back( y );
			g[y].push_back( x );
		}
		findBridge(1 , 0);
		for(int i=1;i<=N;++i)
			if( i == findRoot(i) ){
				++top;
				tid[i] = top;
			}
		for(int i=1;i<=N;++i){
			if( tid[i]==-1 )
				continue;
			for(int j=0;j<g[i].size();++j){
				if( tid[ g[i][j] ]==-1 )
					continue;
				tree[ tid[i] ].push_back( tid[j] );
				tree[ tid[j] ].push_back( tid[i] );
			}
		}
		int t1 , d1 , t2;
		t1 = d1 = t2 = 0;
		findTreeFarest(0 , -1 , 0 , t1 , d1);
		t2 = t1;
		d1 = 0;
		findTreeFarest(d1 , -1 , 0 , t2 , d1);
		printf("%d\n",top-d1);
	}
}
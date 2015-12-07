#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct bridge{
	int u,v,root;
};
vector<bridge> bridges;

bool visited[104];
int inT[104] , low[104] , nowTime;
vector<int> G[104];
int Vnum[104] , Enum[104];

void init(){
	memset(visited , 0 , sizeof(visited));
	nowTime = 0;
	for(int i=0 ; i<104 ; ++i)
		G[i].clear();
	bridges.clear();
}

void dfs(int nowAt,int p,const int &root){
	visited[nowAt] = true;
	inT[nowAt] = low[nowAt] = ++nowTime;
	Vnum[nowAt] = 1;
	Enum[nowAt] = 0;
	for(auto &u : G[nowAt]){
		if( u==p ) continue;
		if( !visited[u] ){
			dfs(u , nowAt , root);
			low[nowAt] = min(low[nowAt] , low[u]);
			if( low[u]>inT[nowAt] )
				bridges.push_back({u , nowAt , root});
			Vnum[nowAt] += Vnum[u];
			Enum[nowAt] += Enum[u] + 1;
		}
		else{
			low[nowAt] = min(low[nowAt] , inT[u]);
			if( inT[u] < inT[nowAt] )
				++Enum[nowAt];
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	for(int NCASE=1 ; NCASE<=T ; ++NCASE){
		init();
		int N,M;
		scanf("%d%d",&N,&M);
		for(int i=0,a,b ; i<M ; ++i){
			scanf("%d%d",&a,&b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		for(int i=1 ; i<=N ; ++i)
			if( !visited[i] )
				dfs(i,-1,i);
		int ans = 0;
		for(auto &bs : bridges){
			int v1 = Vnum[bs.u];
			int e1 = Enum[bs.u];
			int v2 = Vnum[bs.root]-v1;
			int e2 = Enum[bs.root]-e1-1;
			if( v1==v2 && e1==e2 && e1==v1*(v1-1)/2 )
				++ans;
		}
		printf("Case #%d: %d\n",NCASE,ans);
	}
}

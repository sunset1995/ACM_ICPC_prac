#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Record{
	char command;
	int u,v;
};
int parent[20004];
int root[20004];

int find_root(int who){
	if( root[who]==who ) return who;
	return root[who] = find_root(root[who]);
}
void union_root(int a,int b){
	a = find_root(a);
	b = find_root(b);
	root[b] = a;
}

void init(){
	for(int i=0 ; i<20004 ; ++i)
		root[i] = i;
}

int main(){
	int T;
	scanf("%d",&T);
	for(int NCASE=1 ; NCASE<=T ; ++NCASE){
		init();
		int N , K;
		scanf("%d%d",&N,&K);
		for(int i=1 ; i<=N ; ++i)
			scanf("%d",&parent[i]);
		vector<Record> record;
		char command;
		for(int i=0,u,v ; i<K ; ++i){
			scanf(" %c",&command);
			if( command=='C' ){
				scanf("%d",&u);
				if( parent[u]==0 ) continue;
				record.push_back({'C' , u , parent[u]});
				parent[u] = 0;
			}
			else{
				scanf("%d%d",&u,&v);
				record.push_back({'Q' , u , v});
			}
		}
		for(int i=1 ; i<=N ; ++i)
			if( parent[i] )
				union_root(i , parent[i]);
		vector<int> ans;
		for(auto it=record.rbegin() ; it!=record.rend() ; ++it){
			if( it->command=='C' )
				union_root(it->u , it->v);
			else{
				if( find_root(it->u) == find_root(it->v) )
					ans.push_back(1);
				else ans.push_back(0);
			}
		}
		printf("Case #%d:\n",NCASE);
		for(auto it=ans.rbegin() ; it!=ans.rend() ; ++it){
			if( *it ) puts("YES");
			else puts("NO");
		}
	}
}
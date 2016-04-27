#include <cstdio>
using namespace std;

int p[50005];
void findRoot(int);

int main(){
	int n,m , CASECOUNT = 0;
	while( scanf(" %d%d",&n,&m)!=EOF && (n || m) ){
		for(int i=1;i<=n;++i)
			p[i] = i;
		int ans = n;
		for(int i=0,u,v;i<m;++i){
			scanf(" %d%d",&u,&v);
			findRoot(u);
			findRoot(v);
			if( p[u]!=p[v] ){
				p[u] = p[ p[u] ] = v;
				--ans;
			}
		}
		printf("Case %d: %d\n",++CASECOUNT,ans);
	}
}

void findRoot(int who){
	if( p[who]!=who ){
		findRoot( p[who] );
		p[who] = p[ p[who] ];
	}
}
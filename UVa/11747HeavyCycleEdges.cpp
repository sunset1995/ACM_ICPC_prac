#include <cstdio>
#include <algorithm>
using namespace std;

struct P{
	int u , v , w;
} path[25004];
bool myCmp(P a,P b){
	return a.w < b.w;
}

class disjoint{
	public:
		void init(int);
		void combain(int,int);
		bool sameGroup(int,int);
	private:
		int root[25004];
		void findRoot(int);
};
void disjoint::init(int num){
	for(int i=0;i<num;++i)
		root[i] = i;
}
void disjoint::combain(int a,int b){
	if( sameGroup(a,b) ) return;
	root[ root[a] ] = root[b];
}
bool disjoint::sameGroup(int a,int b){
	findRoot(a); findRoot(b);
	return root[a]==root[b];
}
void disjoint::findRoot(int x){
	if( root[x]==x ) return;
	findRoot( root[x] );
	root[x] = root[ root[x] ];
}

int main(){
	int n,m;
	disjoint dSet;
	while( scanf(" %d%d",&n,&m)!=EOF && n && m ){
		for(int i=0;i<m;++i)
			scanf(" %d%d%d",&path[i].u , &path[i].v , &path[i].w);
		sort( &path[0] , &path[m] , myCmp );
		dSet.init(n);
		bool first = true;
		for(int i=0;i<m;++i){
			if( ! dSet.sameGroup( path[i].u , path[i].v ) ){
				dSet.combain( path[i].u , path[i].v );
				continue;
			}
			if( first )
				first = false;
			else
				printf(" ");
			printf("%d",path[i].w);
		}
		if( first )
			printf("forest");
		printf("\n");
	}
}
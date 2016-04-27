#include <cstdio>
#include <algorithm>
using namespace std;

struct POINT{
	int x,y;
} point[800];
struct PATH{
	int u,v,cost;
} path[600000];
int howmuch(const POINT &a,const POINT &b){
	int difX = a.x - b.x,
		 difY = a.y - b.y;
	return difX*difX + difY*difY;
}
bool myCmp(const PATH &a,const PATH &b){
	return a.cost < b.cost;
}

class DISJOINT{
	public:
		enum{
			SIZE = 800
		};
		DISJOINT(){
			init();
		}
		void init();
		void combine(int,int);
		bool sameRoot(int,int);
	private:
		int root[SIZE];
		int findRoot(int);
		//prevent copy constructor and assignment
		//maybe......
		DISJOINT(const DISJOINT&);
		DISJOINT& operator = (DISJOINT &rth);
};

void DISJOINT::init(){
	for(int i=0;i<SIZE;++i)
		root[i] = i;
}
void DISJOINT::combine(int a,int b){
	root[ findRoot(b) ] = findRoot(a);
}
bool DISJOINT::sameRoot(int a,int b){
	return findRoot(a) == findRoot(b);
}
int DISJOINT::findRoot(int whose){
	if( whose==root[whose] )
		return whose;
	return root[whose] = findRoot( root[whose] );
}


int main(){
	DISJOINT disjoint;
	int NCASE;
	scanf(" %d",&NCASE);
	while( NCASE-- ){
		disjoint.init();
		int N,M;
		scanf(" %d",&N);
		for(int i=1;i<=N;++i)
			scanf(" %d%d",&point[i].x , &point[i].y);
		scanf(" %d",&M);
		for(int i=0,u,v;i<M;++i){
			scanf(" %d%d",&u,&v);
			disjoint.combine(u,v);
		}
		int top = -1; // for path's stack
		for(int i=1;i<=N;++i)
			for(int j=i+1;j<=N;++j)
				if( !disjoint.sameRoot(i,j) ){
					++top;
					path[top].u = i,
					path[top].v = j,
					path[top].cost = howmuch(point[i],point[j]);
				}
		sort( &path[0] , &path[top+1] , myCmp );
		bool haveAns = false;
		for(int i=0;i<=top;++i){
			if( disjoint.sameRoot( path[i].u , path[i].v ) )
				continue;
			printf("%d %d\n", path[i].u , path[i].v );
			disjoint.combine( path[i].u  , path[i].v );
			haveAns = true;
		}
		if( !haveAns )
			printf("No new highways need\n");
		if( NCASE )
			printf("\n");
	}
}
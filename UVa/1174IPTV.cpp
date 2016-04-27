#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxSize = 2004;

class CITY{
	public:
		int operator [] (char *str) const{
			for(int i=0;i<=top;++i)
				if( strcmp(stack[i],str)==0 )
					return i;
			return -1;
		}
		void addCity(char *str){
			if( (*this)[str]!=-1 )
				return;
			strcpy( stack[++top] , str );
		}
	private:
		char stack[maxSize][30];
		int top = -1;
};

struct path{
	int a,b,len;
} paths[50004];
struct cmp{
	bool operator() (path x,path y){
		return x.len < y.len;
	}
} myCmp;

class DISJOINT{
	public:
		DISJOINT(){
			for(int i=0;i<maxSize;++i)
				root[i] = -1;
		}
		int findRoot(int);
		void unionSet(int,int);
	private:
		int root[maxSize];
};
int DISJOINT::findRoot(int from){
	if( root[from]<0 )
		return from;
	return ( root[from] = findRoot( root[from] ) );
}
void DISJOINT::unionSet(int a,int b){
	a = findRoot(a);
	b = findRoot(b);
	if( a==b ) return;
	if( root[a] < root[b] )
		a^=b , b^=a , a^=b;
	root[a] += root[b];
	root[b] = a;
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while(NCASE--){
		int N,M;
		scanf(" %d%d",&N,&M);
		
		CITY cityTable;
		for(int i=0;i<M;++i){
			char city1[34] , city2[34];
			int len;
			scanf(" %s%s%d",city1,city2,&len);
			cityTable.addCity( city1 );
			cityTable.addCity( city2 );
			paths[i].a = cityTable[ city1 ];
			paths[i].b = cityTable[ city2 ];
			paths[i].len = len;
		}

		sort( &paths[0] , &paths[M] , myCmp );
		int ans = 0;
		DISJOINT network;
		for(int i=0;i<M;++i){
			if( network.findRoot(paths[i].a) == network.findRoot(paths[i].b) )
				continue;
			ans += paths[i].len;
			network.unionSet(paths[i].a , paths[i].b);
		}
		printf("%d\n",ans);
		if( NCASE )
			printf("\n");
	}
}
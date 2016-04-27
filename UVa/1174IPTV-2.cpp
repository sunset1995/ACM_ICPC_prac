#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

const int maxSize = 2004;

class CITY{
	public:
		int operator [] (char *str){
			return table[str];
		}
		void addCity(char *str){
			if( table.find(str)!=table.end() )
				return;
			strcpy( stack[++top] , str );
			table.insert( pair<const char* const,int>(stack[top] , top) );
		}
	private:
		struct charCmp{
			bool operator () (const char* const a,const char* const b) const{
				return strcmp(a,b)<0;
			}
		};
		map<const char *const , int , charCmp> table;
		char stack[maxSize][10];
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
				root[i] = i;
		}
		int findRoot(int);
		void unionSet(int,int);
	private:
		int root[maxSize];
};
int DISJOINT::findRoot(int from){
	if( root[from]==from )
		return from;
	return ( root[from] = findRoot( root[from] ) );
}
void DISJOINT::unionSet(int a,int b){
	a = findRoot(a);
	b = findRoot(b);
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
		int ans = 0 , cnt = 0;
		DISJOINT network;
		for(int i=0;i<M && cnt<N-1;++i){
			if( network.findRoot(paths[i].a) == network.findRoot(paths[i].b) )
				continue;
			ans += paths[i].len;
			++cnt;
			network.unionSet(paths[i].a , paths[i].b);
		}
		printf("%d\n",ans);
		if( NCASE )
			printf("\n");
	}
}
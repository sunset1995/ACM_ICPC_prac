#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
using namespace std;

const int maxSize = 2004;
const int infinite = 0x3FFFFFFF;

class CITY{
	public:
		int procCity(char *str){
			map<const char *const , int>::iterator it = table.find(str);
			if( it!=table.end() )
				return it->second;
			strcpy( stack[++top] , str );
			table.insert( pair<const char* const,int>(stack[top] , top) );
			return top;
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
	int to , len;
};

int minCost[maxSize];
bool haveElectric[maxSize];

struct NODE{
	int id , cost;
};
struct pqCmp{
	bool operator() (const NODE a,const NODE b) const{
		return a.cost > b.cost;
	}
};

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while(NCASE--){
		int N,M;
		scanf(" %d%d",&N,&M);
		
		CITY cityTable;
		vector<path> g[N+4];
		for(int i=0;i<M;++i){
			char city1[34] , city2[34];
			int len;
			scanf(" %s%s%d",city1,city2,&len);
			int id1 = cityTable.procCity( city1 );
			int id2 = cityTable.procCity( city2 );
			g[id1].push_back( (path){ id2 , len } );
			g[id2].push_back( (path){ id1 , len } );
		}

		for(int i=0;i<=N;++i)
			minCost[i] = infinite , haveElectric[i] = false;
		int ans = 0;
		priority_queue<NODE , vector<NODE> , pqCmp> pq;
		pq.push( (NODE){0,0} );
		while( ! pq.empty() ){
			NODE nowAt = pq.top();
			pq.pop();
			if( haveElectric[nowAt.id] )
				continue;
			haveElectric[nowAt.id] = true;
			ans += nowAt.cost;
			for(vector<path>::iterator it=g[nowAt.id].begin() ; it!=g[nowAt.id].end() ; ++it)
				if( !haveElectric[ it->to ] && it->len < minCost[ it->to ] ){
					minCost[ it->to ] = it->len;
					pq.push( (NODE){it->to , it->len} );
				}
		}
		printf("%d\n",ans);
		if( NCASE )
			printf("\n");
	}
}
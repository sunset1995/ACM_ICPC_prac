#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int infinite = 0x3FFFFFFF;

struct POINT{
	int x,y;
} point[800];
int howmuch(const POINT &a,const POINT &b){
	int difX = a.x - b.x,
		 difY = a.y - b.y;
	return difX*difX + difY*difY;
}
int map[800][800];

struct NODE{
	int id,cost;
};
int cost[800],from[800];
bool lowest[800];
struct myCmp{
	bool operator()(const NODE a,const NODE b) const{
		return a.cost > b.cost;
	}
};
void prim(int N){
	for(int i=1;i<=N;++i)
		cost[i] = infinite,
		lowest[i] = false;
	priority_queue< NODE , vector<NODE> , myCmp > PQ;
	PQ.push( (NODE){ 1 , 0 } );
	cost[1] = 0;
	while( !PQ.empty() ){
		NODE nowAt = PQ.top();
		PQ.pop();
		if( lowest[nowAt.id] )
			continue;
		lowest[nowAt.id] = true;
		for(int i=1;i<=N;++i)
			if( !lowest[i] && map[nowAt.id][i] < cost[i] ){
				cost[i] = map[nowAt.id][i];
				from[i] = nowAt.id;
				PQ.push( (NODE){ i , cost[i] } );
			}
	}
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while( NCASE-- ){
		int N,M;
		scanf(" %d",&N);
		for(int i=1;i<=N;++i){
			scanf(" %d%d",&point[i].x , &point[i].y);
			for(int j=1;j<=i;++j)
				map[i][j] = map[j][i] = howmuch(point[i],point[j]);
		}
		scanf(" %d",&M);
		for(int i=0,u,v;i<M;++i){
			scanf(" %d%d",&u,&v);
			map[u][v] = map[v][u] = 0;
		}
		prim(N);
		bool haveAns = false;
		for(int i=1;i<=N;++i)
			if( cost[i] ){
				printf("%d %d\n",i,from[i]);
				haveAns = true;
			}
		if( !haveAns )
			printf("No new highways need\n");
		if( NCASE )
			printf("\n");
	}
}
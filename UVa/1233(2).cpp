#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int infinite = 0x3FFFFFFF;
int sP[504][504];
int b,p;
struct path{
	int to , cost;
};
vector<path> g[504];

void procInput(){
	scanf(" %d%d",&b,&p);
	for(int i=0;i<=p; g[i].clear() , ++i)
		for(int j=0;j<=p;++j)
			sP[i][j] = infinite;
	int nTo;
	scanf(" %d",&nTo);
	for(int i=1,to;i<=nTo;++i){
		scanf(" %d",&to);
		g[0].push_back( (path){ to , -1 } );
	}
	for(int i=1;i<=p;++i){
		scanf(" %d",&nTo);
		for(int j=0,cost,to;j<nTo;++j){
			scanf(" %d%d",&cost,&to);
			g[i].push_back( (path){ to , cost } );
		}
	}
}
void dijstra(int source){
	bool inQ[504];
	for(int i=0;i<504;++i)
		inQ[i] = false;
	queue<int> myQ;
	myQ.push( source );
	inQ[ source ] = true;
	sP[source][source] = 0;
	while( !myQ.empty() ){
		int now = myQ.front();
		myQ.pop();
		inQ[now] = false;
		for(int i=0;i<g[now].size();++i)
			if( sP[source][ g[now][i].to ] > sP[source][now] + g[now][i].cost ){
				sP[source][ g[now][i].to ] = sP[source][now] + g[now][i].cost;
				if( !inQ[ g[now][i].to ] )
					myQ.push( g[now][i].to );
			}
	}
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while( NCASE-- ){
		procInput();
		for(int i=1;i<=p;++i)
			dijstra(i);

		int minId = g[0][0].to;
		for(int i=1;i<g[0].size();++i)
			if( sP[ g[0][i].to ][0] < sP[ minId ][0] )
				minId = g[0][i].to;
		int ans = (b-2)/sP[minId][0];
		printf("%d\n",ans);
	}
	scanf("%*d");
}
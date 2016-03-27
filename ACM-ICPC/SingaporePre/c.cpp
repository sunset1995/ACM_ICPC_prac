#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define PII pair<int,int>
#define INF 1023456789
using namespace std;

// cost , nextId
vector<PII> g[10004];
int sD[10004];
int way[10004];
bool cnted[10004];

struct myCmp{
	bool operator()(const int&l , const int&r) const{
		return sD[l] > sD[r];
	}
};

int main(){
	int v , e;
	scanf("%d%d",&v,&e);
	for(int i=0,u,v,w ; i<e ; ++i){
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back( {w,v} );
	}
	int s,t;
	scanf("%d%d",&s,&t);

	for(int i=0 ; i<v ; ++i)
		sD[i] = INF;

	priority_queue< int , vector<int> , myCmp > myPQ;
	myPQ.push( s );
	sD[s] = 0;
	way[s] = 1;
	while( !myPQ.empty() && myPQ.top()!=t ){
		int nowId = myPQ.top();
		myPQ.pop();
		if( cnted[nowId] ) continue;
		cnted[nowId] = true;
		for(auto &v : g[nowId]){
			int nextId = v.second;
			int w = v.first;
			if( sD[nextId] > sD[nowId] + w ){
				sD[nextId] = sD[nowId] + w;
				way[nextId] = way[nowId];
				myPQ.push( nextId );
			}
			else if( sD[nextId] == sD[nowId] + w ){
				way[nextId] += way[nowId];
			}
		}
	}
	printf("%d\n",way[t]);
	return 0;
}
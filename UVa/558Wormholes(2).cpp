#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

const int maxLen = 0x1FFFFFFF;
struct edge{
	int to , len;
};
vector<edge> g[1050];
int minLen[1050] , countRelax[1050];
bool inQ[1050];

int main(){
	int c;
	scanf(" %d",&c);
	while( c-- ){
		int n,m;
		scanf(" %d%d",&n,&m);
		for(int i=0;i<n;++i){
			g[i].clear();
			minLen[i] = maxLen;
			countRelax[i] = 0;
			inQ[i] = false;
		}
		for(int i=0,x,y,t;i<m;++i){
			scanf(" %d%d%d",&x,&y,&t);
			g[x].push_back( (edge){ y , t } );
		}
		bool haveNegCyc = false;
		queue<int> myQ;
		minLen[0] = 0;
		myQ.push(0);
		inQ[0] = true;
		while( !haveNegCyc && !myQ.empty() ){
			int nowAt = myQ.front();
			myQ.pop();
			inQ[nowAt] = false;
			for(int i=0;i<g[nowAt].size();++i){
				int des = g[nowAt][i].to , len = g[nowAt][i].len;
				if( minLen[ des ] > minLen[ nowAt ]+len ){
					minLen[ des ] = minLen[ nowAt ]+len;
					if( ++countRelax[ des ] >= n )
						haveNegCyc = true;
					if( !inQ[ des ] ){
						inQ[ des ] = true;
						myQ.push(des);
					}
				}
			}
		}
		if( haveNegCyc )
			printf("possible\n");
		else
			printf("not possible\n");
	}
}

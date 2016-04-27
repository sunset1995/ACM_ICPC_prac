#include <cstdio>
#include <queue>
using namespace std;

const int maxLen = 0x1FFFFFFF;
int minLen[1050];
struct edge{
	int sou , des , val;
} wormhole[2050];

int main(){
	int c;
	scanf(" %d",&c);
	while( c-- ){
		int n,m;
		scanf(" %d%d",&n,&m);
		for(int i=0,x,y,t;i<m;++i){
			scanf(" %d%d%d",&x,&y,&t);
			wormhole[i].sou = x;
			wormhole[i].des = y;
			wormhole[i].val = t;
		}
		for(int i=0;i<n;++i)
			minLen[i] = maxLen;
		minLen[0] = 0;
		for(int i=n-2;i>=0;--i) 
			for(int j=0;j<m;++j)
				if( minLen[ wormhole[j].sou ]!=maxLen && minLen[ wormhole[j].sou ] + wormhole[j].val < minLen[ wormhole[j].des ] )
					minLen[ wormhole[j].des ] = minLen[ wormhole[j].sou ] + wormhole[j].val;
		bool haveNegCyc = false;
		for(int j=0;j<m && !haveNegCyc;++j)
			if( minLen[ wormhole[j].sou ] + wormhole[j].val < minLen[ wormhole[j].des ] )
				haveNegCyc = true;
		if( haveNegCyc )
			printf("possible\n");
		else
			printf("not possible\n");
	}
}

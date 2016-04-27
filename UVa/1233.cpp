#include <cstdio>
#include <cmath>
using namespace std;

const int infinite = 0x3FFFFFFF;
int sP[504][504];
int whom[504];
int b,p;

void procInput(){
	scanf(" %d%d",&b,&p);
	for(int i=0;i<=p;++i)
		for(int j=0;j<=p;++j)
			sP[i][j] = infinite;
	int nTo;
	scanf(" %d",&nTo);
	whom[0] = nTo;
	for(int i=1;i<=nTo;++i)
		scanf(" %d",&whom[i]);
	for(int i=1;i<=p;++i){
		scanf(" %d",&nTo);
		for(int j=0,cost,to;j<nTo;++j){
			scanf(" %d%d",&cost,&to);
			if( cost < sP[i][to] )
				sP[i][to] = cost;
		}
	}
}
void floydWashall(){
	for(int i=1;i<=p;++i)
		for(int u=0;u<=p;++u)
			for(int v=0;v<=p;++v)
				if( sP[u][v] > sP[u][i] + sP[i][v] )
					sP[u][v] = sP[u][i] + sP[i][v];
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while( NCASE-- ){
		procInput();
		floydWashall();
		int minId = whom[1];
		for(int i=whom[0];i>1;--i)
			if( sP[ whom[i] ][0] < sP[ minId ][0] )
				minId = whom[i];
		int ans = ceil( ((double)b-sP[minId][0])/( sP[minId][0]-1 ) );
		printf("%d\n",ans);
	}
	scanf("%*d");
}
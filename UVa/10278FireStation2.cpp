#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define INF 1234567890
using namespace std;

struct NODE{
	int p , d;
	bool operator < (const NODE &r) const {
		if( d > r.d ) return true;
		return false;
	}
};

int f,n;
int d_nearest[505];
vector< NODE > g[505];
int shortesPath[505][505];
int fireStation[105];

void init(){
	scanf(" %d%d",&f,&n);
	for(int i=1;i<=n;++i){
		d_nearest[i] = INF;
		g[i].clear();
		for(int j=1;j<=n;++j)
			shortesPath[i][j] = INF;
	}
	for(int i=0;i<f;++i){
		scanf(" %d",&fireStation[i]);
		d_nearest[ fireStation[i] ] = 0;
	}
	char str[20];
	fgets(str,20,stdin);
	while( fgets(str,20,stdin)!=NULL && str[0]!='\0' && str[0]!='\n' ){
		int from , to , d;
		if( sscanf( str , " %d%d%d" , &from , &to , &d )==EOF )
			break;
		g[from].push_back( (NODE){ to , d } );
		g[to].push_back( (NODE){ from , d } );
	}
}
void dijstra(int);
int coculateD(){
	int maxLen = 0;
	for(int i=0;i<f;++i){
		int from = fireStation[i];
		for(int j=1;j<=n;++j){
			if( shortesPath[ from ][ j ] < d_nearest[ j ] )
				d_nearest[ j ] = shortesPath[ from ][ j ];
			if( d_nearest[j]>maxLen )
				maxLen = d_nearest[j];
		}
	}
	return maxLen;
}
int coculateD(int addToWhere){
	int maxLen = 0;
	int from = addToWhere;
	for(int j=1; j<=n;++j){
		int len = ( shortesPath[ from ][ j ] < d_nearest[j]  )? shortesPath[ from ][ j ] : d_nearest[j];
		if( len > maxLen )
			maxLen = len;
	}
	return maxLen;
}

int main(){
	int CASE;
	scanf(" %d",&CASE);
	while( CASE-- ){
		init();
		for(int i=1;i<=n;++i)
			dijstra(i);
		int d_nearestMax = coculateD();
		int addTo = 1;
		for(int i=1;i<=n;++i){
			if( d_nearest[i]==0 )
				continue;
			int tmpD = coculateD(i);
			if( tmpD < d_nearestMax ){
				d_nearestMax = tmpD;
				addTo = i;
			}
		}
		printf("%d\n",addTo);
		if( CASE )
			printf("\n");
	}
}

void dijstra(int source){
	
	bool visited[501];
	for(int i=1;i<=n;++i)
		visited[i] = false;

	priority_queue< NODE > myQ;
	myQ.push( (NODE){ source , 0 } );

	while( !myQ.empty() ){
		NODE nowAt = myQ.top();
		myQ.pop();
		if( visited[ nowAt.p ] )
			continue;
		shortesPath[source][nowAt.p] = nowAt.d;
		visited[ nowAt.p ] = true;
		for(int i=0;i<g[nowAt.p].size();++i){
			if( visited[ g[nowAt.p][i].p ] )
				continue;
			int newD = shortesPath[source][nowAt.p] + g[nowAt.p][i].d;
			if( newD<shortesPath[source][ g[nowAt.p][i].p ] ){
				shortesPath[source][ g[nowAt.p][i].p ] = newD;
				myQ.push( (NODE){ g[nowAt.p][i].p , newD } );
			}
		}
	}

}
#include <cstdio>
#include <queue>
#include <vector>
#define infinite 100000000
using namespace std;

struct path{
	int to , d;
};
int fireStation[100];
int dp[501][501];
int d[501];
vector<path> g[501];
int f,n;
int minMaxD , ansID;
struct myCmp{
	bool operator() (const int &a,const int &b) const{
		return a>b;
	}
};

void dijkstra(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			dp[i][j] = 0;
		bool visited[501] = {0};
		priority_queue<path,vector<path>,myCmp> pq;
		dp[i][i] = 0;
		pq.push((path){ i , 0 });
		while( !pq.empty() ){
			path tmp = pq.top();
			pq.pop();
			int nowAt = tmp.to;
			visited[nowAt] = true;
			for(int j=0;j<g[nowAt].size();++j)
				if( !visited[ g[nowAt][j].to ] && (dp[i][nowAt]+g[nowAt][j].d) < dp[i][ g[nowAt][j].to ] ){
					pq.push( (path){ g[nowAt][j].to , (dp[i][nowAt]+g[nowAt][j].d) } );
					dp[i][ g[nowAt][j].to ] = (dp[i][nowAt]+g[nowAt][j].d);
				}
			while( !pq.empty() && visited[ pq.top().to ] )
				pq.pop();
		}
	}
}
int caculateD(){
	minMaxD = -1;
	for(int i=1;i<=n;++i){
		for(int j=0 , w=fireStation[j]; j<f; ++j,w=fireStation[j])
			if( dp[i][w] < d[i] )
				d[i] = dp[i][w];	
		if( d[i] > minMaxD )
			minMaxD = d[i];
	}
}
int caculateD(int k){
	int tmpMax = -1;
	for(int i=1;i<=n;++i){
		int tmp = ( dp[i][k]<d[i] )? dp[i][k] : d[i];
		if( tmp > tmpMax )
			tmpMax = tmp;
	}
	if( tmpMax<minMaxD )
		minMaxD = tmpMax , ansID = k;
}

int main(){
	int CASE;
	scanf(" %d",&CASE);
	while( CASE-- ){
		scanf(" %d%d",&f,&n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j)
				dp[i][j] = infinite;
			g[i].clear();
			d[i] = infinite;
		}
		for(int i=0;i<f;++i){
			scanf(" %d",&fireStation[i]);
			d[ fireStation[i] ] = 0;
		}

		char str[20];
		gets(str);
		while( gets(str)!=NULL && str[0]!='\0' && str[0]!='\n' ){
			int a,b,d;
			if( sscanf( str , " %d%d%d" , &a , &b , &d )==EOF )
				break;
			g[a].push_back( (path){b,d} );
			g[b].push_back( (path){a,c} );
		}

		dijkstra();

		ansID = 1;
		caculateD();
		for(int i=1;i<=n;++i){
			caculateD(i);
		}
		printf("%d\n",ansID);
		if( CASE )
			printf("\n");
	}
}
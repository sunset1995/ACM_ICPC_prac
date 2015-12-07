#include <cstdio>
#include <cstring>
using namespace std;

int n;
int c[25][25];
int ok[25];
bool visited[2000000];

void dfs(int state){
	if( visited[state] )
		return;
	visited[state] = true;
	bool nowOk = true;
	for(int i=0 ; i<n ; ++i){
		if( !(state & (1<<i)) ) continue;
		int lastMoney = 0;
		for(int j=0 ; j<n ; ++j)
			if( state & (1<<j) )
				lastMoney -= c[i][j];
		if( lastMoney>=0 ) continue;
		dfs( state & (~(1<<i)) );
		nowOk = false;
	}
	if( !nowOk )
		return;
	int cnt = 0;
	for(int i=0 ; i<n ; ++i)
		if( state & (1<<i) )
			++cnt;
	if( cnt!=1 ) return;
	for(int i=0 ; i<n ; ++i)
		if( state & (1<<i) )
			ok[i] = true;
}

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		memset( ok , 0 , sizeof(ok) );
		memset( visited , 0 , sizeof(visited) );
		scanf("%d",&n);
		for(int i=0 ; i<n ; ++i)
			for(int j=0 ; j<n ; ++j)
				scanf("%d",&c[i][j]);
		dfs( (1<<n)-1 );
		bool have = false;
		for(int i=0 ; i<n ; ++i)
			if( ok[i] ){
				printf("%d ",(i+1));
				have = true;
			}
		if( !have ) printf("0");
		puts("");
	}
}
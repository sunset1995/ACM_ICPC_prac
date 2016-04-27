#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

vector<int> g[50];
int sP[50][50];
char buffer[1000];
bool inSet[50];
vector<int> procSet;

bool judge(int from){
	for(int i=0;i<procSet.size();++i)
		for(int j=i+1;j<procSet.size();++j)
			if( sP[ procSet[i] ][ procSet[j] ]==( sP[ procSet[i] ][from] + sP[ procSet[j] ][from] ) )
				return true;
	return false;
}

int main(){
	int n;
	scanf(" %d",&n);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
			sP[i][j] = -1;
	fgets( buffer , 1000 , stdin );
	for(int i=1;i<=n;++i){
		fgets( buffer , 1000 , stdin );
		char *ptr = strtok( buffer , " " );
		while( ptr!=NULL ){
			g[i].push_back( atoi(ptr) );
			ptr = strtok( NULL , " " );
		}
	}
	for(int s=1;s<=n;++s){
		queue<int> bfsQ;
		sP[s][s] = 0;
		bfsQ.push(s);
		while( !bfsQ.empty() ){
			int now = bfsQ.front();
			bfsQ.pop();
			for(int i=0;i<g[now].size();++i)
				if( sP[s][ g[now][i] ]==-1 ){
					sP[s][ g[now][i] ] = sP[s][now] + 1;
					bfsQ.push( g[now][i] );
				}
		}
	}
	int m;
	scanf(" %d",&m);
	fgets( buffer , 1000 , stdin );
	for(int i=0;i<m;++i){
		for(int i=1;i<=n;++i)
			inSet[i] = false;
		procSet.clear();
		fgets( buffer , 1000 , stdin );
		char *ptr = strtok( buffer , " " );
		while( ptr!=NULL ){
			int tmp = atoi(ptr);
			inSet[ tmp ] = true;
			procSet.push_back( tmp );
			ptr = strtok( NULL , " " );
		}
		bool yes = true;
		for(int i=1;i<=n;++i){
			if( inSet[i] )
				continue;
			if( !judge(i) ){
				yes = false;
				break;
			}
		}
		if( yes )
			printf("yes\n");
		else
			printf("no\n");
	}
}
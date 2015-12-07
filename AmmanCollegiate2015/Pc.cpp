#include <cstdio>
#include <cstring>
using namespace std;

char street[104];
int state[114];

void update(int id){
	state[id] = 1;
	if( id-1>=0 )
		state[id-1] = 1;
	state[id+1] = 1;
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N;
		scanf(" %d%s",&N,street);
		memset(state , 0 , sizeof(state));
		for(int i=0;i<N;++i)
			if( street[i]=='*' )
				update(i);
		int cnt = 0;
		for(int i=0;i<N;++i)
			if( state[i]==0 ){
				update(i+1);
				++cnt;	
			}
		printf("%d\n",cnt);
	}
}
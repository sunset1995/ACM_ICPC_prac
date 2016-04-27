#include <cstdio>
#include <queue>
using namespace std;

int disToState[40000];
int transition[150] , ans;

int main(){
	int T;
	scanf(" %d",&T);
	for(int nowCase = 1;nowCase <= T;++nowCase){
		int N,M;
		scanf(" %d%d",&N,&M);
		for(int i=0;i<M;++i){
			transition[i] = 0;
			for(int j=0,inputC;j<N;++j){
				scanf(" %d",&inputC);
				transition[i] <<= 1;
				transition[i] += inputC;
			}
		}
		
		int initState = 1;
		for(int i=0;i<N;++i)
			initState <<= 1;
		--initState;
		
		for(int i=0;i<=initState;++i)
			disToState[i] = -1;
		
		queue<int> qState , qDis;
		qState.push(initState);
		qDis.push(0);
		while( !qState.empty() && disToState[0]==-1 ){
			int nowState = qState.front();
			int nowDis = qDis.front();
			qState.pop();
			qDis.pop();
			if( disToState[nowState]!=-1 )
				continue;
			disToState[nowState] = nowDis;
			for(int i=0;i<M;++i){
				int nextState = nowState ^ transition[i];
				if( disToState[nextState]==-1 ){
					qState.push(nextState);
					qDis.push(nowDis+1);
				}
			}
		}
		printf("Case %d: ",nowCase);
		if( disToState[0]==-1 )
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n",disToState[0]);
	}
}

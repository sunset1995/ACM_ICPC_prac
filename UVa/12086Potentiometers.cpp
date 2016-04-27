#include <cstdio>
#include <cstring>
using namespace std;

int R[200004] , N;
int query(int id){
	int sum = 0;
	while( id>0 ){
		sum += R[id];
		id -= id & (-id);
	}
	return sum;
}
void update(int id,int val){
	while( id<=N ){
		R[id] += val;
		id += id & (-id);
	}
}

int main(){
	int NCASE = 0;
	while( scanf(" %d",&N)!=EOF && N ){
		if( NCASE )
			printf("\n");
		printf("Case %d:\n",++NCASE);
		for(int i=0;i<=N;++i)
			R[i] = 0;
		for(int i=1,initVal;i<=N;++i){
			scanf(" %d",&initVal);
			update( i , initVal );
		}
		char command[5];
		while( scanf(" %s",command)!=EOF && strcmp(command,"END")!=0 ){
			int x,y;
			scanf(" %d%d",&x,&y);
			if( command[0]=='S' ){
				int oriVal = query(x) - query(x-1);
				update( x , y-oriVal );
			}
			else{
				int val = query(y) - query(x-1);
				printf("%d\n" , val);
			}
		}
	}
}
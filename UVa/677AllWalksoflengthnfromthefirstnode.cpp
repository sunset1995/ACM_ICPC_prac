#include<cstdio>
using namespace std;
void dfs(int);

int m,n;
bool **graph , *visited;
int *stack , top;
bool noPrint;

int main(){
	while(1){
		scanf(" %d%d",&m,&n);
		graph = new bool *[m+1];
		for(int i=1;i<=m;++i){
			graph[i] = new bool[m+1];
			for(int j=1;j<=m;++j)
				scanf(" %d",&graph[i][j]);
		}
		visited = new bool[m+1];
		for(int i=1;i<=m;++i)
			visited[i] = false;
		stack = new int[m+5];
		noPrint = true;
		top=-1;
		stack[++top] = 1;
		
		visited[1] = true;
		dfs(1);
		if( noPrint )
			printf("no walk of length %d\n",n);
		
		for(int i=1;i<=m;++i)
			delete [] graph[i];
		delete [] graph;
		delete [] visited;
		delete [] stack;
		
		int haveNext;
		if( scanf("%d",&haveNext)!=EOF && haveNext==-9999 ){
			printf("\n");
			continue;
		}
		break;
	}
}

void dfs(int at){
	if( top==n ){
		noPrint = false;
		printf( "(%d",stack[0] );
		for(int i=1;i<=n;++i)
			printf(",%d",stack[i]);
		printf(")\n");
		return;
	}
	for(int i=1;i<=m;++i){
		if( graph[at][i] && !visited[i] ){
			visited[i] = true;
			stack[++top] = i;
			dfs(i);
			visited[i] = false;
			--top;
		}
	}
}

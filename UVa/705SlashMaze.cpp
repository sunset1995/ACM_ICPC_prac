#include<cstdio>
#include<queue>
using namespace std;

char maze[300][300];
int cycle , maxL , rBorder , cBorder;

void setMaze(int,int,char);
void bfs_fill(int,int);
void printMaze(){
  for(int i=0;i<=rBorder;++i){
  	for(int j=0;j<=cBorder;++j)
  	  printf("%c",maze[i][j]);
  	printf("\n");
  }
  getchar();
}

int main(){
  bool first = true;
  int CASE = 0;
  int r,c;
  while( scanf(" %d%d",&c,&r)!=EOF && c && r ){
  	rBorder = r*3-1 , cBorder = c*3-1;
  	for(int i=0;i<r;++i)
  	  for(int j=0;j<c;++j){
  	  	char input;
  	  	scanf(" %c",&input);
  	  	setMaze(i,j,input);
  	  }

  	cycle = 0 , maxL = 0;
  	for(int i=0;i<=rBorder;++i)
  	  for(int j=0;j<=cBorder;++j)
  	  	if( maze[i][j]=='.' ){
  	  	  bfs_fill(i,j);
  	  	}
  	
  	printf("Maze #%d:\n",++CASE);
  	if( !cycle )
  	  printf("There are no cycles.\n\n");
  	else
  	  printf("%d Cycles; the longest has length %d.\n\n",cycle,maxL);
  	
  }
}

void setMaze(int r,int c,char type){

  r*=3 , c*=3;
  for(int i=0;i<3;++i)
    for(int j=0;j<3;++j)
      maze[r+i][c+j] = '.';

  int wall = (type=='/')? -1 : 1;
  ++r , ++c;
  maze[r][c] = '#',
  maze[r+1][c+wall] = '#',
  maze[r-1][c-wall] = '#';
}

void bfs_fill(int r,int c){
  
  int length = 1;
  maze[r][c] = '#';
  bool isCycle = true;
  queue<int> rq,cq;
  rq.push(r);
  cq.push(c);
  
  while( !(rq.empty()) ){
  	
  	int nowr = rq.front() , nowc = cq.front();
  	rq.pop();
  	cq.pop();
  	
	if( nowr==0 || nowc==0 || nowr==rBorder || nowc==cBorder )
	  isCycle = false;
	
	int nextr , nextc;
	
	nextr = nowr-1 , nextc = nowc;
	if( nextr>=0 && maze[nextr][nextc]=='.' ){
	  rq.push(nextr);
	  cq.push(nextc);
	  ++length;
  	  maze[nextr][nextc] = '#';
	}
	
	nextr = nowr+1 , nextc = nowc;
	if( nextr<=rBorder && maze[nextr][nextc]=='.' ){
	  rq.push(nextr);
	  cq.push(nextc);
	  ++length;
  	  maze[nextr][nextc] = '#';
	}
	
	nextr = nowr , nextc = nowc-1;
	if( nextc>=0 && maze[nextr][nextc]=='.' ){
	  rq.push(nextr);
	  cq.push(nextc);
	  ++length;
  	  maze[nextr][nextc] = '#';
	}
	
	nextr = nowr , nextc = nowc+1;
	if( nextc<=cBorder && maze[nextr][nextc]=='.' ){
	  rq.push(nextr);
	  cq.push(nextc);
	  ++length;
  	  maze[nextr][nextc] = '#';
	}
  } // complete bfs
  
  length /= 3;
  if( isCycle ){
  	++cycle;
  	maxL = (length>maxL)? length : maxL;
  }
}

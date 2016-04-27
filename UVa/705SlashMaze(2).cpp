#include<cstdio>
using namespace std;

struct G{
  int numChild , fatherR , fatherC;
} maze[200][200]; // a slash would be splited into left part and right part
char wall[200][200]; // record the input maze data 
int cycle , maxL , br , bc; // cycle and maxL for Answer ; br bc are the border of maze

int proc_maze(int,int,char); // make wall[][] (input)  into  maze[][]
void unit(int,int,int,int); // combine two maze's element ; it also detect cycle and update variable cycle and maxL
int find_root(int,int); // find union tree's root ; if two element have the same root , there are 'a' cycle

int main(){
  int CASE = 0;
  int r,c;
  while( scanf(" %d%d",&c,&r)!=EOF ){
  	if( r==0 && c==0 ) break;
  	br=r , bc=c*2;
  	for(int i=0; i<br; ++i)
  	  for(int j=0; j<bc; ++j)
  	    maze[i][j].numChild = 1,
  	    maze[i][j].fatherR = i,
  	    maze[i][j].fatherC = j;
  	cycle = 0 , maxL = 0;
  	
  	for(int i=0;i<r;++i)
  	  for(int j=0;j<c;++j){
  	  	scanf(" %c",&wall[i][j]);
  	  	proc_maze(i,j,wall[i][j]);
  	  }

  	printf("Maze #%d:\n",++CASE);
  	if( cycle )
  	  printf("%d Cycles; the longest has length %d.\n\n",cycle,maxL);
  	else
  	  printf("There are no cycles.\n\n");
  }
}

int proc_maze(int r,int c,char type){
  int leftR = r , rightR = r;
  int leftC = 2*c , rightC = 2*c+1;
  if( leftC>0 )
    unit(leftR,leftC-1,leftR,leftC);
  if( rightR>=1 ){
  	int upR , upC , nowR , nowC;
  	if( wall[r-1][c]=='/' )
  	  upR = rightR-1 , upC = rightC;
  	else
  	  upR = leftR-1 , upC = leftC;
  	if( type=='/' )
  	  nowR = leftR , nowC = leftC;
  	else
  	  nowR = rightR , nowC = rightC;
  	unit( upR , upC , nowR , nowC );
  }
}
void unit(int r1,int c1,int r2,int c2){
  int tmp1 = find_root( r1 , c1 );
  int tmp2 = find_root( r2 , c2 );
  r1 = tmp1 / bc,
  c1 = tmp1 % bc,
  r2 = tmp2 / bc,
  c2 = tmp2 % bc;
  if(tmp1==tmp2){
  	++cycle;
  	if( maze[r1][c1].numChild>maxL )
	  maxL = maze[r1][c1].numChild;
	return; // detected cycle
  }
  if( maze[r2][c2].numChild>maze[r1][c1].numChild )
    r1^=r2 , r2^=r1 , r1^=r2,
    c1^=c2 , c2^=c1 , c1^=c2;
  
  maze[r1][c1].numChild += maze[r2][c2].numChild;
  maze[r2][c2].numChild = 0;
  maze[r2][c2].fatherR = r1;
  maze[r2][c2].fatherC = c1;
  return;
}
int find_root(int r,int c){
  if( maze[r][c].fatherR!=r || maze[r][c].fatherC!=c ){
  	int tmp = find_root(maze[r][c].fatherR , maze[r][c].fatherC);
  	maze[r][c].fatherR = (tmp/bc);
  	maze[r][c].fatherC = (tmp%bc);
  }
  
  return maze[r][c].fatherR * bc + maze[r][c].fatherC;
}

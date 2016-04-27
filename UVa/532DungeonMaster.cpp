#include<cstdio>
#include<queue>
using namespace std;

char maze[35][35][35]; //z,y,x
int L,R,C,ans;
bool reach;
struct position{
  int x,y,z;
  int depth;
};
queue<position> myQueue;
void judge(int x,int y,int z,int nowDepth){
  if( x<0 || x>=C ) return;
  if( y<0 || y>=R ) return;
  if( z<0 || z>=L ) return;
  if( maze[z][y][x]=='#' ) return;
  
  if( maze[z][y][x]=='E' )
  	reach = true , ans = nowDepth;
  myQueue.push( (position){ x , y , z , nowDepth+1 } );
  maze[z][y][x] = '#';
}
void clearMyQueue(){
  while( !myQueue.empty() )
    myQueue.pop();
}

int main(){
  while( scanf(" %d%d%d",&L,&R,&C)!=EOF && L ){
  	clearMyQueue();
  	reach = false;
  	for(int i=0;i<L;++i) for(int j=0;j<R;++j) for(int k=0;k<C;++k){
  	  scanf(" %c",&maze[i][j][k]);
  	  if( maze[i][j][k]=='S' ){
  	    myQueue.push( (position){ k , j , i , 1 } );
  	    maze[i][j][k] = '#';
  	  }
  	}
  	while( !reach && !myQueue.empty() ){
  	  position now = myQueue.front();
  	  judge( now.x-1 , now.y , now.z , now.depth );
  	  judge( now.x+1 , now.y , now.z , now.depth );
  	  judge( now.x , now.y-1 , now.z , now.depth );
  	  judge( now.x , now.y+1 , now.z , now.depth );
  	  judge( now.x , now.y , now.z-1 , now.depth );
  	  judge( now.x , now.y , now.z+1 , now.depth );
  	  myQueue.pop();
  	}
  	if( reach )
  	  printf("Escaped in %d minute(s).\n",ans);
  	else
  	  printf("Trapped!\n");
  }
} 

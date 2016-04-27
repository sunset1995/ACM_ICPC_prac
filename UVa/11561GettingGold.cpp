#include<stdio.h>

char map[100][100];
int score;
void dfs(int x,int y){
  if( map[y][x]=='G' ) ++score;
  map[y][x] = '#';
  
  if( map[y-1][x]=='T' || map[y+1][x]=='T' || map[y][x-1]=='T' || map[y][x+1]=='T' )
    return;

  if( map[y-1][x]!='#' )
    dfs( x , y-1 );
  if( map[y+1][x]!='#' )
    dfs( x , y+1 );
  if( map[y][x-1]!='#' )
    dfs( x-1 , y );
  if( map[y][x+1]!='#' )
    dfs( x+1 , y );
}

int main(){
  int W,L;
  while( scanf(" %d%d",&W,&L)!=EOF ){
  	int sx,sy;
  	for(int i=0;i<L;++i)
  	  for(int j=0;j<W;++j){
  	  	scanf(" %c",&map[i][j]);
  	  	if( map[i][j]=='P' ) sx = j , sy = i;
  	  }
  	score = 0;
  	dfs(sx,sy);
  	printf("%d\n",score);
  }
} 

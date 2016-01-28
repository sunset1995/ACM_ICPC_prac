#include <cstdio>
using namespace std;

char grid[14][14];
int tryOutCnt[14][14];

int main(){
	int w,h;
	scanf("%d%d",&h,&w);
	for(int i=0 ; i<h ; ++i)
		scanf("%s",grid[i]);

	int r=-1 , c=-1;
	for(int i=0 ; i<h && r==-1 ; ++i)
		for(int j=0 ; j<w ; ++j)
			if( grid[i][j]!='.' && grid[i][j]!='*' ){
				r = i , c = j;
				break;
			}
	bool forward = false;
	while( tryOutCnt[r][c]<=4 ){
		++tryOutCnt[r][c];
		int nr , nc;
		char rotate;
		switch( grid[r][c] ){
			case 'U':
				nr = r-1 , nc = c;
				rotate = 'R';
				break;
			case 'R':
				nr = r , nc = c+1;
				rotate = 'D';
				break;
			case 'D':
				nr = r+1 , nc = c;
				rotate = 'L';
				break;
			default:
				nr = r , nc = c-1;
				rotate = 'U';
		}
		if( nr>=h || nr<0 || nc>=w || nc<0 || grid[nr][nc]=='*' )
			grid[r][c] = rotate;
		else{
			grid[nr][nc] = grid[r][c];
			grid[r][c] = 'y';
			r = nr , c = nc;
		}
	}

	int ans = 0;
	for(int i=0 ; i<h ; ++i)
		for(int j=0 ; j<w ; ++j)
			if( grid[i][j] != '*' && grid[i][j]!= '.' )
				++ans;
	printf("%d\n",ans);
	return 0;
}

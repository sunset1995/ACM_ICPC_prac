#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n , maxLast;
bool e[104][51000];
int dp[104][51000];
int s[104][51000];
int tmp[504];
void init(){
	memset( dp , 0 , sizeof(dp) );
	memset( s , 0 , sizeof(s) );
	memset( e , 0 , sizeof(e) );
	e[0][0] = 1;
}

inline void pk(int r,int c,int atk,int oriC,int m){
	e[r][c] = 1;
	if( dp[r][c] > atk ) return;
	if( dp[r][c]==atk && s[r][c]!=0 && s[r][c] < oriC+m ) return;
	dp[r][c] = atk , s[r][c] = oriC+m;
}

int main(){
	while( scanf(" %d",&n)!=EOF && n ){
		init();

		for(int i=1,cost;i<=n;++i){
			scanf(" %d",&cost);
			memcpy( dp[i] , dp[i-1] , sizeof(dp[i]) );
			memcpy( s[i] , s[i-1] , sizeof(s[i]) );
			memcpy( e[i] , e[i-1] , sizeof(e[i]) );

			if( cost%1000 == 0 ){
				for(int j=500;j<50000;++j)
					if( e[i-1][j] )
						pk(i,j-500,dp[i-1][j]+1 , s[i-1][j] , cost);
				continue;
			}
			int last = 500 - cost%1000;
			for(int j=0;j<-last;++j)
				if( e[i-1][j] )
					pk(i,j+500+last , dp[i-1][j] , s[i-1][j] , cost);
			for(int j=(-last<0)?0:-last ; j<50000 ; ++j)
				if( e[i-1][j] )
					pk(i,j+last , dp[i-1][j]+1 , s[i-1][j] , cost);
		}

		int c = 0 , spend = dp[n][0];
		for(int j=0;j<50000;++j)
			if(dp[n][j] > c || (dp[n][j]==c && s[n][j] < spend) ){
				c = dp[n][j];
				spend = s[n][j];
			}
		if( c==0 )
			printf("0 0\n");
		else
			printf("%d %d\n",c,spend);
	}
}
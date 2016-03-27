#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n , maxLast;
bool e[51000];
int dp[51000];
int s[51000];

void init(){
	memset( dp , 0 , sizeof(dp) );
	memset( s , 0 , sizeof(s) );
	memset( e , 0 , sizeof(e) );
	e[0] = 1;
}

inline void pk(int c,int atk,int oriC,int m){
	e[c] = 1;
	if( dp[c] > atk ) return;
	if( dp[c]==atk && s[c]!=0 && s[c] < oriC+m ) return;
	dp[c] = atk , s[c] = oriC+m;
}

int main(){
	while( scanf(" %d",&n)!=EOF && n ){
		init();

		for(int i=1,cost;i<=n;++i){
			scanf(" %d",&cost);

			int tmp1[504] , tmp2[504];
			memcpy( tmp1 , dp , sizeof(tmp1) );
			memcpy( tmp2 , s , sizeof(tmp2) );

			if( cost%1000 == 0 ){
				for(int j=500;j<50000;++j)
					if( e[j] )
						pk(j-500,dp[j]+1 , s[j] , cost);
				continue;
			}
			int last = 500 - cost%1000;
			for(int j=(-last<0)?0:-last ; j<50000 ; ++j)
				if( e[j] )
					pk(j+last , dp[j]+1 , s[j] , cost);
			for(int j=0;j<-last;++j)
				if( e[j] )
					pk(j+500+last , tmp1[j] , tmp2[j] , cost);
		}

		int c = 0 , spend = dp[0];
		for(int j=0;j<50000;++j)
			if(dp[j] > c || (dp[j]==c && s[j] < spend) ){
				c = dp[j];
				spend = s[j];
			}
		if( c==0 )
			printf("0 0\n");
		else
			printf("%d %d\n",c,spend);
	}
}
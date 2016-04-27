#include<cstdio>
using namespace std;
int main(){
  int l,n;
  int c[55];
  int dp[55][55];
  while( scanf(" %d%d",&l,&n)!=EOF && l ){
  	c[0] = 0;
  	for(int i=1;i<=n;++i)
  	  scanf(" %d",&c[i]);
  	c[++n] = l;
  	for(int i=1;i<=n;++i){
  	  dp[i-1][i] = 0;
  	  for(int j=i-2;j>=0;--j){
  	  	dp[j][i] = c[i] - c[j];
  	  	int min = 100 * l;
  	  	for(int k=j+1;k<i;++k)
  	  	  if( dp[j][k]+dp[k][i] < min ) min = dp[j][k] + dp[k][i];
  	  	dp[j][i] += min;
  	  }
  	}
  	printf("The minimum cutting is %d.\n",dp[0][n]);
  }
} 

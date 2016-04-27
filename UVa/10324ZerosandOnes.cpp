#include<stdio.h>
#define MAX 1000005

int main(){
  char tmp;
  int *dp;
  dp = new int[MAX];
  int CASE = 0;
  while( scanf(" %c",&tmp)!=EOF && tmp!='z' ){
  	printf("Case %d:\n",++CASE);
  	dp[0] = tmp - '0';
  	char last = tmp;
  	int index = 1;
  	do{
  	  
  	  tmp = getchar();
  	  if( tmp!=last )
  	    dp[index] = dp[index-1] + 1;
  	  else
  	    dp[index] = dp[index-1];
  	  ++index;
  	  last = tmp;
  	}while( tmp!='\n' );
  	int N;
  	scanf(" %d",&N);
  	while(N--){
  	  int l,r;
  	  scanf(" %d%d",&l,&r);
  	  if( l>r ) l^=r , r^=l , l^=r;
  	  if( dp[l]==dp[r] ) printf("Yes\n");
  	  else printf("No\n");
  	}
  }
  delete [] dp;
}

#include<stdio.h>

int n;
int A[20];
int dp[20][20];
int record[20][20];
void printAns(int from,int to){
  if( to-from==2 ){
  	printf("(A%d x A%d)",from+1,to);
  	return;
  }
  
  printf("(");
  if( record[from][to]==from+1 ){
  	printf("A%d x ",from+1);
  	printAns( from+1 , to );
  }
  else if( record[from][to]==to-1 ){
  	printAns( from , to-1 );
  	printf(" x A%d",to);
  }
  else{
  	printAns( from , record[from][to] );
  	printf(" x ");
  	printAns( record[from][to] , to );
  }
  printf(")");
}

int main(){
  int CASE = 0;
  while( scanf(" %d",&n)!=EOF && n ){
  	for(int i=0;i<n;++i){
  	  int l,r;
  	  scanf(" %d%d",&l,&r);
  	  A[i] = l;
  	  A[i+1] = r;
  	}
  	for(int i=2;i<=n;++i){
  	  dp[i-1][i] = 0;
  	  for(int j=i-2; j>=0; --j){
  	  	int minId = j+1;
  	  	int minVal = dp[j][minId] + dp[minId][i] + A[j]*A[minId]*A[i];
  	  	for(int k=j+2;k<i;++k){
  	  	  int nowVal = dp[j][k] + dp[k][i] + A[j]*A[k]*A[i];
  	  	  if( nowVal<minVal )
  	  	    minVal = nowVal , minId = k;
  	  	}
  	  	dp[j][i] = minVal;
  	  	record[j][i] = minId;
  	  }
  	}
  	printf("Case %d: ",++CASE);
  	printAns( 0 , n );
  	printf("\n");
  }
}

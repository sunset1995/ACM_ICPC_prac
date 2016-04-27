#include<cstdio>
#include<cstring>
using namespace std;

int main(){
  char martix[30][30];
  int n;
  scanf(" %d",&n);
  for(int CASE=0;CASE<n;++CASE){
  	scanf(" %s",martix[0]);
  	int len = strlen( martix[0] );
  	for(int i=1;i<len;++i)
  	  scanf(" %s",martix[i]);
  	
  	int maxA = 0;
  	for(int i=0;i<len;++i )
  	  for(int j=0;j<len;++j){
  	  	int minW = 100;
  	  	for(int r=1;i-r+1>=0 && martix[i-r+1][j]=='1';++r){
  	  	  int w=1;
  	  	  while( j-w>=0 && martix[i-r+1][j-w]=='1' && w<=minW ) ++w;
  	  	  if( w<minW ) minW = w;
  	  	  maxA = ( minW*r>maxA )? minW*r : maxA;
  	  	}
  	  }
  	if( CASE!=0 ) printf("\n");
  	printf("%d\n",maxA);
  }
}

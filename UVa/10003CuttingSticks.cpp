#include<cstdio>
using namespace std;

int main(){
  int wood[100][100];
  int l,n;
  int stick[100];
  while( scanf(" %d%d",&l,&n)!=EOF && l ){
  	stick[0] = 0;
  	for(int i=1;i<=n;++i)
  	  scanf(" %d",&stick[i]);
  	stick[n+1] = l;
  	n+=2;
  	for(int i=1;i<n;++i){
  	  wood[ i ][ i-1 ] = 0;
  	  for(int j=i-2;j>=0;--j){
  	  	wood[ i ][ j ] = stick[i] - stick[j];
  	  	int min = wood[j+1][j] - wood[j][j];
  	  	for(int k=j+1;k<i;++k)
  	  	  if( wood[j][k]+wood[k][i]<min ) min = wood[j][k]+wood[k][i];
  	  	wood[ i ][ j ] += min;
  	  }
  	}
  	for(int i=0;i<n;++i)
  	  printf("%d ",wood[i][0]);
  	printf("The minimum cutting is %d.\n",wood[n-1][0]);
  }
} 

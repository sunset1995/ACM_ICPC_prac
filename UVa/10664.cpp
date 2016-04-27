#include<stdio.h>
#include<string.h>

bool dp[250];
int a[25] , top , sum , target;
char str[1000];

void getData(){
  fgets( str , 1000 , stdin );
  char *ptr = strtok( str , " \n" );
  top = -1 , sum = 0;
  do{
    int getval;
    sscanf( ptr , "%d" , &getval ); 
	a[++top] = getval;
	sum += getval;
	ptr = strtok( NULL , " \n" );
  }while( ptr!=NULL );
}

int main(){
  int m;
  scanf(" %d",&m);
  fgets( str , 10 , stdin );
  while( m-- ){
  	getData();
  	if( (sum&1)==1 ){
  	  printf("NO\n");
  	  continue;
  	}
  	target = sum/2;
  	for(int i=0;i<=target;++i)
  	  dp[i] = false;
  	dp[0] = true;
  	for(int i=0;i<=top && !dp[target];++i){
  	  for(int j=target;j>0;--j)
  	    if( j-a[i]>=0 && dp[ j-a[i] ] )
		  dp[j] = true;
  	}
  	if( dp[target] ) printf("YES\n");
  	else printf("NO\n");
  	
  }
}

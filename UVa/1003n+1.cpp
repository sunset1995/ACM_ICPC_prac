#include<cstdio>
#define MAX 10000 
using namespace std;
int main(){
  int known[MAX];
  for(int i=1;i<MAX;++i){
  	int tmp = i , length = 1;
  	while( tmp!=1 ){
	  if( tmp&1 ){
	    tmp=3*tmp+1;
	    ++length;
	  }
	  tmp>>=1;
	  ++length;
  	}
  	known[i] = length;
  }
  
  int a,b;
  while( scanf(" %d%d",&a,&b)!=EOF ){
    int max=0;
    int tmpa = a,tmpb = b;
    if( a>b ) tmpa = b,tmpb = a; // some people say that a will bigger than b
    for(int i=tmpa;i<=tmpb;++i){
	  int length = 1, N=i;
	  while( N!=1 ){
	  	if( N<MAX ){
	  		length += known[N] -1;
	  		break;
	  	}
	  	while( (N&1)==0 ){
			N >>= 1 , ++length;
	  	}
	    if( N==1 )
			break;
		N = (3*N+1)>>1;
	    length+=2;
	  }
	  if( length>max ) max = length;
	}
	printf("%d %d %d\n",a,b,max);
  }
  return 0;
}

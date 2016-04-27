#include<cstdio>
using namespace std;

struct G{
  int father;
  int numChild;
} citizen[30005];

int findFather(int a){
  if( citizen[a].father!=a )
    citizen[a].father = findFather( citizen[a].father );

  return citizen[a].father;
}
int beFriend(int a,int b){
  b = findFather(b);
  a = findFather(a);
  if( a == b )
    return citizen[a].numChild;
    
  citizen[a].numChild += citizen[b].numChild;
  citizen[b].numChild = 0;
  citizen[b].father = a;
  return citizen[a].numChild;
}

int main(){
  int N,M;
  int CASE;
  scanf(" %d",&CASE);
  while( CASE-- ){
  	scanf(" %d%d",&N,&M);
  	for(int i=1;i<=N;++i)
  	  citizen[i].father = i,
  	  citizen[i].numChild = 1;
  	
  	int manA , manB , maxL = 1, tmpL;
  	for(int i=0;i<M;++i){
  	  scanf(" %d%d",&manA,&manB);
  	  tmpL = beFriend( manA , manB );
  	  if( tmpL>maxL ) maxL = tmpL;
  	}
  	printf("%d\n",maxL);
  }
}

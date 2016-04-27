#include<cstdio>
using namespace std;

bool canSetPart( int *set , int len , long long tolerance , int maxPart ){
  long long nowPartHave = 0LL;
  int partNum = 1;
  while( (--len)>=0 && partNum <= maxPart ){
  	nowPartHave += (long long)set[len];
  	if( nowPartHave > tolerance )
  	  ++partNum , nowPartHave = (long long)set[len];
  }
  if( partNum > maxPart )
    return false;
  return true;
}

int main(){
  int N;
  int book[550] , stack[550] , index;
  scanf(" %d",&N);
  while( N-- ){
  	int k,m;
  	scanf(" %d%d",&m,&k);
  	long long totalPage = 0 , maxBookPage = 0;
  	for(int i=0;i<m;++i){
  	  scanf(" %d",&book[i]);
  	  totalPage += book[i];
  	  if( book[i]>maxBookPage ) maxBookPage = (long long)book[i];
  	}
  	long long l=maxBookPage , r=totalPage;
  	while( l<r ){
  	  long long c = (l+r)/2LL;
  	  if( canSetPart( book , m , c , k ) )
  	    r = c;
  	  else
  	    l = c+1LL;
  	}
  	while( !canSetPart( book , m , l , k ) ) ++l;
  	index = -1;
  	long long nowPageNum = 0LL;
  	int partNum = 0 , id = m;
  	while( (--id)>=0 ){
  	  nowPageNum += (long long)book[id];
  	  if( nowPageNum>l )
  	  	stack[++index] = id,
  	  	nowPageNum = (long long)book[id],
  	  	++partNum;
  	  if( (id+1) == (k-partNum) )
  	    break;
  	}
  	while( (--id)>=0 ){
  	  stack[++index] = id;
  	}
  	for(int i=0;i<m-1;++i){
  	  printf("%d ",book[i]);
  	  if( index>=0 && stack[index]==i ){
  	  	printf("/ ");
  	  	--index;
  	  }
  	}
  	printf("%d\n",book[m-1]);
  }
}

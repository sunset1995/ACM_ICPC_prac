#include<cstdio>
#include<algorithm>
using namespace std;

struct animal{
  int ith;
  int weight;
  int IQ;
  int derive;
} elephant[1005];
bool myCmp( animal a,animal b ){
  return a.IQ>b.IQ;
}
int stack1[1005] , id1[1005] , size = 0;
int stack2[1005] , id2[1005];

int bSearch( int nowWeight ){
  int l=-1 , r=size-1;
  while( l<r ){
  	int c = (l+r+1)/2;
  	if( nowWeight > stack1[c]  )
  	  l = c;
  	else
  	  r = c-1;
  }
  return l;
}
void update( int id , int W , int D ){
  if( id==size ){
  	stack1[ size ] = W,
  	id1[ size ] = D,
  	size++;
  	return;
  }
  
  if( elephant[ id1[id] ].IQ==elephant[ D ].IQ ){
  	stack1[ id ] = W,
  	id1[ id ] = D;
  	return;
  }
  
  stack2[id] = stack1[id],
  id2[id] = id1[id],
  stack1[id] = W,
  id1[id] = D;
}

int main(){
  int N = 0;
  while( scanf(" %d%d",&elephant[N].weight ,&elephant[N].IQ)!=EOF && elephant[N].weight>0 ){
  	elephant[N].ith = N+1;
  	elephant[N].derive = -1;
    ++N;
  }
  stable_sort( elephant , elephant+N , myCmp );
  
  // init
  for(int i=0;i<N;++i) stack2[i] = -1 , id2[i] = -1;
  
  // start dp
  elephant[0].derive = -1;
  stack1[size] = elephant[0].weight,
  id1[size] = 0,
  ++size;
  for(int i=1;i<N;++i){
  	int find = bSearch( elephant[i].weight );
  	if( find==-1 ){
  	  elephant[i].derive = -1;
  	  update( 0 , elephant[i].weight , i );
  	  continue;
  	}
  	elephant[i].derive = id1[find];
  	if( find!=-1 && elephant[i].IQ==elephant[ id1[find] ].IQ ){
  	  if( id2[find]!=-1 && elephant[i].weight>elephant[ id2[find] ].weight )
  	    elephant[i].derive = id2[find];
  	  else
  	    --find , elephant[i].derive = id1[find];
  	}
  	update( find+1 , elephant[i].weight , i );
  }
  printf("%d\n",size);
  int trace = id1[size-1] , traceStack[1005] , top = -1;
  while( trace!=-1 ){
    traceStack[++top] = trace;
    trace = elephant[trace].derive;
  }
  while( top>=0 ){
  	printf("%d\n",elephant[ traceStack[top--] ].ith);
  }
}

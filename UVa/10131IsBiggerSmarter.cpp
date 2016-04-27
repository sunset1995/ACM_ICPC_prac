/* AC 0.022 */
#include<cstdio>
#include<algorithm>
using namespace std;

struct animal{
  int ith;
  int weight;
  int IQ;
} elephant[1005];
bool myCmp(animal a,animal b){
  return a.IQ>b.IQ;
}


int main(){
  int N = 0;
  while( scanf(" %d%d",&elephant[N].weight ,&elephant[N].IQ)!=EOF && elephant[N].weight>0 ){
  	elephant[N].ith = N+1;
  	++N;
  }
  stable_sort( elephant , elephant+N , myCmp );
  int derive[1005] , L[1005];
  derive[0] = -1;
  L[0] = 1;
  
  for(int i=1;i<N;++i){
  	L[i] = 1;
  	derive[i] = -1;
  	for(int j=i-1;j>=0;--j)
  	  if( elephant[j].weight<elephant[i].weight && L[j]+1>L[i] && elephant[j].IQ!=elephant[i].IQ ){
  	  	L[i] = L[j]+1;
  	  	derive[i] = j;
  	  }
  }
  int maxId = 0;
  for(int i=1;i<N;++i)
  	if( L[i]>L[maxId] )
  	  maxId = i;
  printf("%d\n",L[maxId]);
  int stack[1005] , top = -1;
  while( maxId!=-1 ){
  	stack[++top] = maxId;
  	maxId = derive[maxId];
  }
  while( top>=0 ){
  	printf("%d\n",elephant[ stack[top--] ].ith );
  }
} 

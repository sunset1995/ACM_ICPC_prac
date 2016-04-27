/* WA 0.025 */
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;

struct animal{
  int ith;
  int weight;
  int IQ;
} elephant[1005];
int derive[1005];
bool myCmp(animal a,animal b){
  return a.IQ>b.IQ;
}

void binarySearch(int *array,int &len,int from,int to){ // elephant from~to are the same smart
  map<int,int> tmp; //  whereToBeChang -- problablyNewVal
  for(int i=from;i<to;++i){
  	int l=0 ,r=len-1;
  	while(l<r){
  	  int c = (l+r+1)/2;
  	  int cWeight = elephant[ array[c] ].weight;
  	  if( cWeight < elephant[i].weight )
  	    l = c;
  	  else
  	    r = c-1;
  	}
  	if( l==0 && elephant[i].weight <= elephant[ array[0] ].weight )
  	  l = -1;
  	if( tmp.find(l+1)==tmp.end() || elephant[ tmp[l+1] ].weight > elephant[i].weight )
  	  tmp[l+1] = i;
  	  
  	derive[i] = (l==-1)? -1 : array[l];
  }
  for(map<int,int>::iterator it=tmp.begin() ;it!=tmp.end(); ++it ){
  	if( it->first == len ){
  	  array[ len ] = it->second;
  	  len++;
  	  continue;
  	}
  	int oriWeight = elephant[ array[it->first] ].weight;
  	int newWeight = elephant[ it->second ].weight;
  	if( newWeight < oriWeight )
  	  array[ it->first ] = it->second;
  }
}


int main(){
  int N = 0;
  while( scanf(" %d%d",&elephant[N].weight ,&elephant[N].IQ)!=EOF ){
  	elephant[N].ith = N+1;
  	++N;
  }
  stable_sort( elephant , elephant+N , myCmp );
  for(int i=0;i<N;++i)
    printf("%d %d %d\n",elephant[i].ith,elephant[i].IQ,elephant[i].weight);
  derive[0] = -1;
  int B[1005] , size = 1;
  B[0] = 0;
  for(int i=1;i<N;++i){
  	int from = i , to = i+1;
  	while( to<N && elephant[to].IQ==elephant[from].IQ )
	  ++to;
  	i = to-1;
  	binarySearch(B,size,from,to);
  }
  
  printf("%d\n",size);
  int stack[1005] , top = -1 , trace = B[size-1];
  while( trace!=-1 ){
  	stack[++top] = trace;
  	trace = derive[trace];
  }
  while( top>=0 ){
  	printf("%d\n",elephant[ stack[top--] ].ith );
  }
} 

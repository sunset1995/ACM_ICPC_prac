/* 52ms */

#include<cstdio>
#include<list>
using namespace std;

int belong[30005];
list<int> group[30005];  // the first element indicate num

int group_merge(int a,int b){
  list<int>::iterator it = group[b].begin();
  while( it!=group[b].end() ){
  	belong[ (*it) ] = a;
	++it; 
  }
  group[a].splice( group[a].begin() , group[b] );
  return group[a].size();
}

int main(){
  int N,M;
  int CASE;
  scanf(" %d",&CASE);
  while( CASE-- ){
  	scanf(" %d%d",&N,&M);
  	for(int i=1;i<=N;++i){
  	  belong[i] = i;
  	  group[i].clear();
  	  group[i].push_back(i);
  	}
  	
  	int manA,manB,maxSize = 1,tmpSize;
  	for(int i=0;i<M;++i){
  	  scanf(" %d%d",&manA,&manB);
  	  if( belong[manA]==belong[manB] )
  	    continue;
  	  tmpSize = group_merge( belong[manA],belong[manB] );
  	  maxSize = (tmpSize>maxSize)? tmpSize : maxSize;
  	}
  	printf("%d\n",maxSize);
  }
}

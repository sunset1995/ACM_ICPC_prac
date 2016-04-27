#include<cstdio>
#include<map>
#include<queue>
using namespace std;


int main(){
  int N , num;
  int track[20];
  map< int , int > tape;
  map< int , int >::iterator it , find;
  queue<int> qq;
  while( scanf(" %d%d",&N,&num)!=EOF ){
  	tape.clear();
  	tape[0] = -1;
    for(int i=0;i<num;++i)
      scanf(" %d",&track[i]);
    for(int i=0;i<num;++i){
      for(it = tape.begin();it!=tape.end() && (it->first+track[i])<=N;++it)
        if( tape.find( it->first + track[i] )==tape.end() )
          qq.push( it->first );
      while( !(qq.empty()) ){
      	tape[ qq.front()+track[i] ] = qq.front();
      	qq.pop();
      }
    }
    it = tape.end(); --it;
    int id = it->first;
    int stack[20] , top = -1;
    while( id>0 ){
	  stack[ ++top ] = id-tape[id];
	  id = tape[id];
	}
	while( top>=0 ){
	  printf("%d ",stack[top]);
	  --top;
	}
	printf("sum:%d\n",it->first);
  }
}

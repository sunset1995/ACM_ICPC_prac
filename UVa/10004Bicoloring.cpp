#include<cstdio>
#include<list>
using namespace std;

int n,l;
list<int> node[210];
int color[210];
bool ok;
void dfs(int at,int c){
  if( color[at] ){
  	if( color[at]!=c )
  	  ok = false;
  	return;
  }
  color[at] = c;
  
  list<int>::iterator it = node[at].begin();
  while( it!=node[at].end() && ok ){
  	dfs( (*it) , -1*color[at] );
  	++it;
  }
}

int main(){
  while( scanf(" %d%d",&n,&l)!=EOF && n ){
  	ok = true;
  	for(int i=0;i<l;++i){
  	  node[i].clear();
  	  color[i] = 0;
  	}
    for(int i=0;i<l;++i){
      int a , b;
      scanf(" %d%d",&a,&b);
      node[a].push_back( b );
      node[b].push_back( a );
    }
    dfs( 0 , 1 );
    if( ok )
      printf("BICOLORABLE.\n");
    else
      printf("NOT BICOLORABLE.\n");
  }
} 

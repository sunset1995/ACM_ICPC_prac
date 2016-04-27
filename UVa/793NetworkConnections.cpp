#include<cstdio>
using namespace std;

int success , unsuccess , g[1000000];

int root(int a){
  if( a!=g[a] )
    g[a] = root(g[a]);
  return g[a];
}
void find(int a,int b){
  if( root(a)==root(b) )
    ++success;
  else
    ++unsuccess;
}
void unit(int a,int b){
  a = root(a);
  b = root(b);
  g[b] = a;
}

int main(){
  int n , CASE;
  scanf(" %d",&CASE);
  bool first = true;
  while( CASE-- ){
  	scanf(" %d",&n);
    for(int i=0;i<=n+5;++i)
      g[i] = i;
    success = 0 , unsuccess = 0;
    char command[20];
    char operation;
    int fir , sec;
    gets(command);
    while( gets(command) ){
      if( command[0]=='\0' || command[0]=='\n' ) break;
      sscanf(command," %c%d%d",&operation,&fir,&sec);
  	  if( operation=='c' )
  	    unit(fir,sec);
  	  else
  	    find(fir,sec);
    }
    if( first ) first = false;
    else printf("\n");
    printf("%d,%d\n",success,unsuccess);
  }
} 

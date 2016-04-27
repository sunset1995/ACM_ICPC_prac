#include<cstdio>
using namespace std;
bool close(int);
int n;
int main(){
  while( scanf(" %d",&n)!=EOF && n ){
  	int ans = 1;
  	while( !close(++ans) )
	  ;
  	printf("%d\n",ans);
  }
}
bool close(int m){
	int mod , d = 0;
	for(mod=1;mod<n;++mod){
	  d = (d+m) % mod;
      if( d==0 ) d = mod;
	}
	if( d==1 ) return true;
	return false;
}

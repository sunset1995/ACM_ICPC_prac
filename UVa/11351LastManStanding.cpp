#include<cstdio>
using namespace std;
int main(){
  int k;
  scanf(" %d",&k);
  for(int __time=1;__time<=k;++__time){
    int n,m;
    scanf(" %d%d",&n,&m);
    int mod , d = 0;
    for(mod=1;mod<n;++mod){
      d = (d+m) % mod;
      if( d==0 ) d = mod;
	}
	int ans = (d+m) % mod;
	if( ans==0 ) ans = mod;
	printf("Case %d: %d\n",__time,ans);
  }
}

#include<cstdio>
using namespace std;
int main(){
	int n,people[3501];
	int prime[3501],top=-1;
	prime[++top] = 2;
	for(int i=0;i<3501;++i){
		int temp = prime[top];
		bool found = false;
		while( !found ){
			found = true;
			++temp;
			for(int j=0;j<=top;++j)
			  if( temp%prime[j]==0 ){
			  	found = false;
			  	break;
			  }
		}
		prime[++top] = temp;
	}
	while( scanf(" %d",&n)!=EOF && n ){
		int mod,d;
		for(mod=1,d=0;mod<n;++mod){
			d = (d+prime[ n-mod ]) % mod;
			if(d==0) d = mod;
		}
		d = (d+2) % mod;
		if( d==0 ) d = mod;
		printf("%d\n",d);
	}
}

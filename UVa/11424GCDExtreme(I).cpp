#include<cstdio>
#include<cstring>
#define MAX 200001
using namespace std;
int main(){
	bool *isPrime;
	isPrime = new bool[MAX];
	memset( isPrime , true , sizeof(bool[MAX]) );
	for(int i=2;i<MAX;++i){
		if( isPrime[i] ){
			for(int j=2;i*j<MAX;++j){
				isPrime[i*j] = false;
			}
		}
	}
	int *childAns;
	childAns = new int[MAX/2+5];
	int n;
	while( scanf(" %d",&n)!=EOF && n ){
		long long ans = 0;
		for(int i=1;i<n;++i){
			if( isPrime[i] )
				ans += (long long)n-i ,
				ans += (long long)(i-1) * (n/i-1);
			else{
				int sum = 0;
				for(int j=i+1;j<=n && j<=2*i;++j){
					if( isPrime[j] )
						sum += 1 , childAns[j-i] = 1;
					else{
						int a=i,b=j;
						while(1){
							if( !(b%a) || a==1 ) break;
							int tmp = b;
							b = a,
							a = (tmp%a);
						}
						sum+=a , childAns[j-i] = a;
					}
				}
				ans += (long long)(n/i-1)*sum;
				int last = n%i;
				for(int j=1;j<=last;++j)
					ans += (long long)childAns[j];
			}
		}
		printf("%ld\n",ans);
	}
	delete [] isPrime;
	delete [] childAns;
}

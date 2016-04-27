#include<cstdio>
using namespace std;
int main(){
	int fib[100],top;
	fib[0] = 1,
	fib[1] = 2;
	top = 1;
	while( fib[top]<=100000000 )
		fib[ ++top ] = fib[top-1] + fib[top-2];
	
	int n;
	scanf(" %d",&n);
	while( n-- ){
		int input;
		scanf(" %d",&input);
		printf("%d = ",input);
		int p;
		for(p=0;fib[p+1]<=input;++p)
			;
		while( p>=0 ){
			if( input>=fib[p] ){
				putchar('1');
				input -= fib[p];
			}
			else{
				putchar('0');
			}
			--p;
		}
		printf(" (fib)\n");
	}
}

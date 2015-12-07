#include <cstdio>
using namespace std;

int main(){
	int n2 = 0;
	for(int i=1 ; i<=100 ; ++i){
		int tmp = i;
		while( tmp%2 == 0 )
			++n2 , tmp/=2;
	}
	int n2_2 = 0;
	for(int i=1 ; (1<<i)<100 ; ++i)
		n2_2 += 100 / (i<<i);
	printf("%d %d\n",n2,n2_2);

}

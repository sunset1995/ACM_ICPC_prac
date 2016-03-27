#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
	srand(time(NULL));
	int n = rand()%100 + 1;
	printf("%d 2\n",n);
	for(int i=0 ; i<n ; ++i) {
		int x = rand()%100, y = rand()%100;
		if( x==y ) y = x+1;
		printf("%d %d\n",min(x,y),max(x,y));
	}
	return 0;
}

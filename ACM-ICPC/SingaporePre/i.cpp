#include <cstdio>
#include <climits>
using namespace std;

int a[100004];
bool possible[100004];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0 ; i<n ; ++i)
		scanf("%d",&a[i]);
	int biggest = -INT_MAX-1;
	for(int i=0 ; i<n ; ++i)
		if( a[i] >= biggest )
			possible[i] = true , biggest = a[i];
	int smallest = INT_MAX;
	for(int i=n-1 ; i>=0 ; --i){
		if( a[i] > smallest )
			possible[i] = false;
		else
			smallest = a[i];
	}
	int ans = 0;
	for(int i=0 ; i<n ; ++i)
		if( possible[i] ) ++ans;
	printf("%d",ans);
	return 0;
}
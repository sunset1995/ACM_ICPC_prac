#include <cstdio>
#include <vector>
using namespace std;

int label[100004];
int arr[100004];

int ans;
void mergeSort(int *a,int n) {
	if( n==1 ) return;
	int mid = n>>1;
	mergeSort(a, mid);
	mergeSort(a+mid, n-mid);
	vector<int> tmp(n);
	int top = -1, i = 0, j = mid;
	while( i<mid && j<n ) {
		if( a[i] < a[j] )
			tmp[++top] = a[i++];
		else {
			tmp[++top] = a[j++];
			ans += mid - i;
		}
	}
	while( i<mid ) tmp[++top] = a[i++];
	while( j<n ) tmp[++top] = a[j++];
	for(int i=0; i<tmp.size(); ++i)
		a[i] = tmp[i];
}

int main() {
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int n;
		scanf("%d", &n);
		for(int i=1,ori; i<=n; ++i) {
			scanf("%d", &ori);
			label[ori] = i;
		}
		for(int i=1,ori; i<=n; ++i) {
			scanf("%d", &ori);
			arr[i] = label[ori];
		}
		ans = 0;
		mergeSort(arr+1, n);
		printf("%d\n", ans);
	}
	return 0;
}

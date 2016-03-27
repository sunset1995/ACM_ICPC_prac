#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int top = -1;
int n, a[50000][8];
vector<int> G[50000];

void insert(int *a,int id,int v) {
	for(int i=6 ; i>=id ; --i)
		a[i+1] = a[i];
	a[id] = v;
}
bool rev;
void itdepen(int nowAt,int depth,int len) {
	if( depth<len-1 ) {
		for(int i=0 ; i<G[nowAt].size() ; ++i)
			itdepen(G[nowAt][i], depth+1, len);
		return;
	}
	int from = 0, to = len, step = 1;
	if( rev ) from = len-1, to = -1, step = -1;
	rev = !rev;
	for(int i=from ; i!=to ; i+=step) {
		G[nowAt].push_back(++top);
		memcpy(a[top], a[nowAt], sizeof(a[top]));
		insert(a[top], i, len);
	}
}
void show(int nowAt,int depth) {
	if( depth==n ) {
		for(int i=0 ; i<n ; ++i)
			printf("%d ",a[nowAt][i]);
		puts("");
		return;
	}
	for(int i=0 ; i<G[nowAt].size() ; ++i)
		show(G[nowAt][i], depth+1);
}

int main() {
	scanf("%d",&n);
	a[++top][0] = 1;
	for(int i=2 ; i<=n ; ++i) {
		rev = true;
		itdepen(0, 1, i);
	}
	show(0,1);
	return 0;
}

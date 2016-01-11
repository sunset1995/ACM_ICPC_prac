#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int label[100004];
int fenwick[100004];

int query(int id) {
	int res = 0;
	while( id ) {
		res += fenwick[id];
		id -= -id & id;
	}
	return res;
}
void addOne(int id) {
	while( id<100004 ) {
		++fenwick[id];
		id += -id & id;
	}
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

		int ans = 0;
		memset(fenwick, 0, sizeof(fenwick));
		for(int i=1,val; i<=n; ++i) {
			scanf("%d", &val);
			val = label[val];
			ans += i - 1 - query(val);
			addOne(val);
		}
		printf("%d\n", ans);
	}
	return 0;
}

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, d, p;
struct Person {
	int Pa = 0;
	vector<int> t;
};

bool ok(int Ea) {
	
}

int main() {
	while( scanf("%d%d%d", &n, &d, &p)!=EOF ) {
		if( !n && !d && !p ) break;
		Person ps[504];
		for(int i=0,num; i<d; ++i) {
			scanf("%d", &num);
			int todayPa = p / num;
			for(int j=0,id; j<num; ++j) {
				scanf("%d", &id);
				employee[id].emplace_back(i);
				employee[id] += todayPa;
			}
		}
		int l=0, r=1023456789;
		while( l<r ) {
			int c = (l+r)/2;
			if( ok(c) )
				r = c;
			else l = c+1;
		}
		printf("%d\n", l);
	}
	return 0;
}

#include <cstdio>
#include <list>
using namespace std;

typedef list<int>::iterator setit;

list<int> lts[100];
void update(int val) {
	int id = 0;
	while( lts[id].size()>=100 && val > lts[id].back() )
		++id;
	setit it = lts[id].begin();
	while( it!=lts[id].end() && (*it) < val )
		++it;
	lts[id].insert(it, val); 
	while( lts[id].size() > 100 ) {
		lts[id+1].push_front( lts[id].back() );
		lts[id].pop_back();
		++id;
	}
}
int findMedian(int sz) {
	int targetID = (sz-1)>>1;
	setit it = lts[targetID/100].begin();
	int num = targetID%100;
	for(int i=0; i<num; ++i)
		++it;
	if( sz&1 ) return *it;
	long long res = *it;
	if( ++it == lts[targetID/100].end() )
		res += lts[targetID/100 + 1].front();
	else
		res += *it;
	return res>>1;
}

int main() {
	int X, sz=0;
	while( scanf("%d", &X)!=EOF ) {
		update(X);
		printf("%d\n", findMedian(++sz));
	}
	return 0;
}

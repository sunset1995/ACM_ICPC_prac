#include <cstdio>
#include <algorithm>
using namespace std;

char str[300004];

int fenwickR[300004], fenwickL[300004];
void add(int *a,int id,int val) {
	while( id<=300000 ) {
		a[id] += val;
		id += -id & id;
	}
}
int query(int *a,int id) {
	int sum = 0;
	while( id>0 ) {
		sum += a[id];
		id -= -id & id;
	}
	return sum;
}

void turnRight(int id) {
	str[id] = '(';
	add(fenwickR, id, -1);
	add(fenwickL, id, 1);
}
void turnLeft(int id) {
	str[id] = ')';
	add(fenwickR, id, 1);
	add(fenwickL, id, -1);
}

int main() {
	int N, Q;
	scanf("%d%d%s", &N, &Q, str+1);
	for(int i=1 ; i<=N ; ++i)
		if( str[i]==')' )
			add(fenwickR, i, 1);
		else
			add(fenwickL, i, 1);

	int id;
	while( Q-- ) {
		scanf("%d", &id);
		if( str[id]==')' ) {
			turnRight(id);
			int l = query2(mempool);
			printf("%d\n", l);
			turnLeft(l);
		}
		else {
			turnLeft(id);
			int l=1 , r=N;
			while( l<r ) {
				int c = (l+r)>>1;
				if( query(c)==0 ) l = c+1;
				else r = c;
			}
			printf("%d\n", l);
			turnRight(l);
		}
	}
	return 0;
}

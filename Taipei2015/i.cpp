#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

char buffer[1000000];
int getNum(int &i) {
	int val = 0;
	while( buffer[i]>='0' && buffer[i]<='9' ) {
		val *= 10;
		val += buffer[i]-'0';
		++i;
	}
	--i;
	return val;
}

vector<int> num, op;
int root[10004], sz[10004], r[10004];
int findRoot(int id) {
	if( root[id]==id ) return id;
	return root[id] = findRoot(root[id]);
}
void init() {
	num.clear();
	op.clear();
	for(int i=0; i<10004; ++i) {
		root[i] = i;
		sz[i] = r[i] = 1;
	}
}

void R1() {
	int a = findRoot(num.back());
	num.pop_back();
	int b = findRoot(num.back());
	num.pop_back();
	if( r[a]+sz[b] < r[b]+sz[a] ) {
		sz[a] += sz[b];
		r[a] += sz[b];
		root[b] = a;
		num.emplace_back(a);
	}
	else {
		sz[b] += sz[a];
		r[b] += sz[a];
		root[a] = b;
		num.emplace_back(b);
	}
}
void R2() {
	int a = findRoot(num.back());
	num.pop_back();
	int b = findRoot(num.back());
	num.pop_back();
	sz[a] += sz[b];
	r[a] = max(r[a], r[b]);
	root[b] = a;
	num.emplace_back(a);
}
void cocuStack() {
	while( op.size() ) {
		int operation = op.back();
		op.pop_back();
		if( operation=='J' )
			R1();
		else if( operation=='U' )
			R2();
		else break;
	}
}

int main() {
	int K;
	scanf("%d", &K);
	while( K-- ) {
		init();
		int n;
		scanf("%d%s", &n, buffer);
		for(int i=0; buffer[i]!='\0'; ++i) {
			if( buffer[i]>='0' && buffer[i]<='9' )
				num.emplace_back(getNum(i));
			else if( buffer[i]==')' )
				cocuStack();
			else
				op.emplace_back(buffer[i]);
		}
		cocuStack();
		printf("%d\n", r[findRoot(1)]);
	}
	return 0;
}

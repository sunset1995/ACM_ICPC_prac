#include <cstdio>
#include <vector>
using namespace std;

int n[4];
char canuse[3] = {'+', '-', '='};
char op[3];

bool valid() {
	vector<int> val = {n[0]};
	for(int i=0; i<3; ++i) {
		if( op[i]=='+' ) val.back() += n[i+1];
		else if( op[i]=='-' ) val.back() -= n[i+1];
		else val.push_back(n[i+1]);
	}
	if( val.size()==1 ) return false;
	for(int i=1; i<val.size(); ++i)
		if( val[i]!=val[i-1] ) return false;
	return true;
}
bool recur(int id) {
	if( id==4 )
		return valid();
	for(int i=0; i<3; ++i) {
		op[id] = canuse[i];
		if( recur(id+1) ) return true;
	}
	return false;
}

int main () {
	int T;
	scanf("%d", &T);
	for(int NOWCASE=1; NOWCASE<=T; ++NOWCASE) {
		scanf("%d%d%d%d", &n[0], &n[1], &n[2], &n[3]);
		recur(0);
		printf("Case #%d: %d %c %d %c %d %c %d\n", NOWCASE, n[0], op[0], n[1], op[1], n[2], op[2], n[3]);
	}
	return 0;
}

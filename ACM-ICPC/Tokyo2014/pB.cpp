#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int main() {
	char str[50];
	int res, len;
	scanf("%s%d",str,&res);
	len = strlen(str);
	int l2r = str[0]-'0';
	for(int i=2 ; i<len ; i+=2) {
		if( str[i-1]=='+' )
			l2r += str[i]-'0';
		else l2r *= str[i]-'0';
	}
	vector<int> st;
	vector<char> op;
	for(int i=0 ; i<len ; ++i) {
		if( i%2 == 0 ) {
			st.emplace_back(str[i]-'0');
		}
		else if( str[i]=='+' ) {
			while( op.size() && op.back()=='*' ) {
				op.pop_back();
				int tmp = st.back();
				st.pop_back();
				st.back() *= tmp;
			}
			op.emplace_back('+');
		}
		else op.emplace_back('*');
	}
	while( op.size() ) {
		int tmp = st.back();
		st.pop_back();
		if( op.back() == '+' )
			st.back() += tmp;
		else st.back() *= tmp;
		op.pop_back();
	}
	int normal = st[0];
	//printf("%d %d\n",l2r,normal);
	if( res==l2r && res==normal ) puts("U");
	else if( res==l2r ) puts("L");
	else if( res==normal ) puts("M");
	else puts("I");
	return 0;
}

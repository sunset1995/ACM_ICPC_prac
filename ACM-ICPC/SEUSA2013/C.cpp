#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<int> ans;
int dp[1004];
void fill(int val) {
	ans.push_back(val);
	for(int i=val; i<1004; i+=val)
		++dp[i];
}

int main() {
	char str[1004];
	while( scanf("%s", str)!=EOF ) {
		if(  str[0]=='0' && str[1]=='\0' ) break;
		memset(dp, 0, sizeof(dp));
		ans.clear();
		int len = strlen(str)-1;
		int id = 1;
		while( str[id]=='0' )
			++id;
		fill(id);
		while( str[++id]!='\0' ) {
			if( str[id]=='0' ) {
				if( dp[id]&1 ) fill(id);
			}
			else {
				if( !(dp[id]&1) ) fill(id);
			}
		}
		printf("%d", ans[0]);
		for(int i=1; i<ans.size(); ++i)
			printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}

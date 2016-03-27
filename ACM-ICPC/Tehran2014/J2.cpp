#include <cstdio>
#include <cstring>
using namespace std;

int n, d, p;
int day[504][504];
long long dp[504][504];

int main() {
	while( scanf("%d%d%d", &n, &d, &p)!=EOF ) {
		if( !n && !d && !p ) break;
		memset(day, 0, sizeof(day));
		memset(dp,  0, sizeof(dp) );
		for(int i=1,num; i<=d; ++i) {
			scanf("%d", &num);
			int todayPa = p / num;
			for(int j=0,id; j<num; ++j) {
				scanf("%d", &id);
				day[i][id] = 1;
				dp [0][id] -= todayPa;
			}
		}
		for(int i=1; i<=d; ++i)
		for(int j=1; j<=n; ++j) {}
	}
	return 0;
}

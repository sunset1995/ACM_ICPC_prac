#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define N 18
using namespace std;

int dp[1<<N][N];
char str[N+2];

int main () {
	while(scanf("%s", str)!=EOF && str[0]!='0') {
		int len = strlen(str);
		memset(dp, -1, sizeof(dp));
		int fullstate = (1<<len)-1;
		for(int i = 0; i < len; i++)
			dp[0][i] = 0;
		for(int k = 1; k <= fullstate; k++)
			for(int pos = 0; pos < len; pos++)
				if((k & (1<<pos)) == 0 || (k==fullstate && pos==0)) {
					int mn = 2e9;
					char now = (k == fullstate && pos == 0 ? 'A' : str[pos]);
					for(int i = 0; i < len; i++)
						if(k & (1<<i)) {
							int cost = 0;
							for(int j = pos + (i>pos); j != i; j += (i < j ? -1 : 1))
								cost += ((k & (1<<j)) == 0);
							cost += min(abs(str[i]-now), 26 - abs(str[i]-now));
							mn = min (mn, dp[k ^ (1<<i)][i] + cost);
						}
						dp[k][pos] = mn;
				}
		printf("%d\n",dp[(1<<len)-1][0] + len);
	}
}

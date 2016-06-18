#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

char mp[30][30];
int  in[30][30];
bool visited[30][30];
int n, w;
int stR[4] = {-1, 1,-1,1};
int stC[4] = {-1,-1, 1,1};
bool judge(int r, int c, int k) {
	int nr  = r + stR[k];
	int nr2 = r + stR[k]*2;
	int nc  = c + stC[k];
	int nc2 = c + stC[k]*2;
	return nr>=0 && nr<n && nr2>=0 && nr2<n
		&& nc>=0 && nc<n && nc2>=0 && nc2<n
		&& !visited[nr][nc]
		&& mp[nr][nc]=='W' && mp[nr2][nc2]=='_';
};
int dfsBuildEdge(int r, int c) {
	int ret = 0;
	for(int k=0; k<4; ++k)
		if( judge(r, c, k) ) {
			++in[r][c];
			++in[r+stR[k]*2][c+stC[k]*2];
			visited[r+stR[k]][c+stC[k]] = 1;
			ret += 1 + dfsBuildEdge(r+stR[k]*2, c+stC[k]*2);
		}
	return ret;
}
bool ok(int r, int c) {
	memset(in, 0, sizeof(in));
	memset(visited, 0, sizeof(visited));
	if( dfsBuildEdge(r, c)!=w )
		return false;
	int odd = 0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if( (i!=r || j!=c) && (in[i][j]&1) )
				++odd;
	return odd < 2;
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
		scanf("%s", mp[i]);
	w = 0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if( mp[i][j]=='W' )
				++w;
	
	int multiple = 0;
	int ans=-1;
	for(int i=0; i<n && !multiple; ++i)
		for(int j=0; j<n && !multiple; ++j)
			if( mp[i][j]=='B' && ok(i, j) ) {
				if( ans!=-1 ) multiple = 1;
				ans = 100*(n-i) + j;
			}
	if( multiple ) puts("Multiple");
	else if( ans==-1 ) puts("None");
	else printf("%c%d\n", ans%100 + 'a', ans/100);
	return 0;
}
	

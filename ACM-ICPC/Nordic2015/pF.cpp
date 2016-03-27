#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ti, ni;
int t[104][2];
int dpR[10004];
int dpL[10004];

int main() {
	int f;
	scanf("%d",&f);
	bool possible = 1;
	while( f-- ) {
		scanf("%d%d",&ti,&ni);
		for(int i=0 ; i<ni ; ++i) {
			scanf("%d%d",&t[i][0],&t[i][1]);
			if( t[i][1]-t[i][0] > ti ) possible = false;
		}
		if( !possible ) continue;
		memset(dpR, 0, sizeof(dpR));
		memset(dpL, 0, sizeof(dpL));
		for(int i=0,playT=t[0][1]-t[0][0] ; i<=ti ; ++i) {
			if( i+playT<=ti ) dpR[i+playT] = 1;
			if( i-playT>=0 ) dpL[i-playT] = 1;
		}
		int now = 0;
		for(int k=1 ; k<ni ; ++k) {
			int next = (now+1)%2;
			for(int i=0 ; i<=ti ; ++i) {
				if( dpR[i] || dpL[i] )
					dpR[i] = dpL[i] = 1;
			}
			now = next;
			int playT = t[k][1] - t[k][0];
			for(int i=ti ; i>=0 ; --i) {
				if( dpR[i] ) {
					dpR[i] = 0;
					if( i+playT <= ti )
						dpR[i+playT] = 1;
				}
			}
			for(int i=0 ; i<=ti ; ++i) {
				if( dpL[i] ) {
					dpL[i] = 0;
					if( i-playT >= 0 )
						dpL[i-playT] = 1;
				}
			}
			bool ok = false;
			for(int i=0 ; i<=ti ; ++i)
				if( dpL[i] || dpR[i] ) {
					ok = true;
					break;
				}
			if( !ok ) possible = false;
		}
	}
	if( possible ) puts("possible");
	else puts("impossible");
	return 0;
}

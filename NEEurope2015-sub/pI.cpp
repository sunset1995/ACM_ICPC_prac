#include <cstdio>
using namespace std;

int cnt[104];

int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int avg = n/k , ans = 0;
	for(int i=0,c ; i<n ; ++i){
		scanf("%d",&c);
		if( ++cnt[c] > avg )
			++ans;
	}
	printf("%d\n",ans);
	return 0;
}

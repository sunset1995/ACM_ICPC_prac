#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int top;
pair<int,int> event[24];
bool used[14];

int ans , now;
void recur(int nowid){
	if( nowid==top ){
		ans = max(ans , now);
		return;
	}
	recur(nowid+1);
	for(int i=event[nowid].first+1 ; i<=event[nowid].second ; ++i)
		if( used[i] ) return;
	for(int i=event[nowid].first+1 ; i<=event[nowid].second ; ++i)
		used[i] = true;
	++now;
	recur(nowid+1);
	for(int i=event[nowid].first+1 ; i<=event[nowid].second ; ++i)
		used[i] = false;
	--now;
}

int main(){
	int n;
	scanf("%d",&n);
	while( n-- ){
		top = 0;
		int s,f;
		while(true){
			scanf("%d%d",&s,&f);
			if( s==0 && f==0 ) break;
			event[top].first = s;
			event[top].second = f;
			++top;
		}
		memset(used , 0 , sizeof(used));
		ans = now = 0;
		recur(0);
		printf("%d\n",ans);
	}
}

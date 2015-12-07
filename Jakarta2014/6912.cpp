#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int N , K;
int ans , now;
bool light[1004];
vector<int> brute , simple;

void turn(int p){
	for(int i=p ; i<=N ; i+=p){
		light[i] = !light[i];
		if( light[i] ) ++now;
		else --now;
	}
}

void simpleTry(){
	vector<int> record;
	for(auto &p : simple){
		int tmp = now;
		turn(p);
		if( now < tmp ) turn(p);
		else record.emplace_back( p );
	}
	ans = max(ans , now);

	for(auto &p : record)
		turn(p);
}

void recur(int nowid){
	if( nowid == brute.size() ){
		simpleTry();
		return;
	}
	recur(nowid+1);
	turn(brute[nowid]);
	recur(nowid+1);
}

void init(){
	ans = now = 0;
	memset(light , 0 , sizeof(light));
	brute.clear();
	simple.clear();
}

int main(){
	int T;
	scanf("%d",&T);
	for(int NCASE = 1 ; NCASE<=T ; ++NCASE){
		init();
		scanf("%d%d",&N,&K);
		int to = sqrt(N);
		for(int i=0,p ; i<K ; ++i){
			scanf("%d",&p);
			if( p<to ) brute.emplace_back( p );
			else simple.emplace_back( p );
		}
		recur(0);
		printf("Case #%d: %d\n",NCASE,ans);
	}
}
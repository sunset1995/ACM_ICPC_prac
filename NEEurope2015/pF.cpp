#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct event{
	int from,to;
	event(const int &from,const int &to)
	:from(from), to(to){}
};
vector<event> es;
bool occupy[10004];

bool min_each(int ts){
	memset(occupy , 0 , sizeof(occupy));
	for(auto &e : es){
		int cnt = ts;
		for(int i=e.from ; i<=e.to && cnt ; ++i)
			if( !occupy[i] ){
				occupy[i] = true;
				--cnt;
			}
		if( cnt ) return false;
	}
	return true;
}

int main(){
	int n;
	scanf("%d",&n);
	int lb = 0 , rb = 0;
	for(int i=0,a,b ; i<n ; ++i){
		scanf("%d%d",&a,&b);
		rb = max(rb , b-a);
		es.emplace_back( event(a , b-1) );
	}
	sort(es.begin() , es.end() , [](const event &l,const event &r){
		return l.to < r.to;
	});

	while( lb<rb ){
		int c = (lb+rb+1)>>1;
		if( min_each(c) ) lb = c;
		else rb = c-1;
	}
	printf("%d\n",lb*n);
}

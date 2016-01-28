#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct work{
	int t,day;
	work(const int &t,const int &day)
	:t(t), day(day){}
};
struct person{
	int d,r,id;
	person(const int &d,const int &r,const int &id)
	:d(d), r(r), id(id){}
};

int ans[200004];

long long fenWorktime[200004];
long long fenWorkdays[200004];
void add(long long *a,int id,long long val){
	while( id<200004 ){
		a[id] += val;
		id += -id & id;
	}
}
long long query(long long *a,int id){
	long long sum = 0LL;
	while( id>0 ){
		sum += a[id];
		id -= -id & id;
	}
	return sum;
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	vector<work> wk;
	vector<person> cd;
	for(int i=1,t ; i<=m ; ++i){
		scanf("%d",&t);
		wk.emplace_back(work(t,i));
	}
	for(int i=0,d,r ; i<n ; ++i){
		scanf("%d%d",&d,&r);
		cd.emplace_back(person(d,r,i));
	}

	sort(wk.begin() , wk.end() , [](const work &l,const work &r){
		return l.t > r.t;
	});
	sort(cd.begin() , cd.end() , [](const person &l,const person &r){
		return l.d > r.d;
	});

	int id = 0;
	for(auto &nowPerson : cd){
		while( id < wk.size() && wk[id].t > nowPerson.d ){
			add(fenWorktime, wk[id].day, wk[id].t);
			add(fenWorkdays, wk[id].day, 1);
			++id;
		}

		int lb = 1 , rb = m+1;
		while( lb<rb ){
			int c = (lb+rb)>>1;
			long long myT = query(fenWorktime,c) -
								 query(fenWorkdays,c) * nowPerson.d;
			if( myT >= nowPerson.r ) rb = c;
			else lb = c+1;
		}
		ans[nowPerson.id] = (lb==m+1)? 0 : lb;
	}
	for(int i=0 ; i<n ; ++i)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}

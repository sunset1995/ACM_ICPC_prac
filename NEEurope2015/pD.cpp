#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

struct Person{
	int t , e , s , f;
	int way;
};
Person person[1004];
int ans[1004];

bool meet(const Person &i,const Person &j){
	if( i.e < j.t ) return false;
	if( j.e < i.t ) return false;
	int t = max(i.t , j.t);
	int e = min(i.e , j.e);
	int s1 = i.s + i.way*(t-i.t);
	int f1 = i.s + i.way*(e-i.t);
	int s2 = j.s + j.way*(t-j.t);
	int f2 = j.s + j.way*(e-j.t);
	if( i.way * j.way > 0 )
		return s1==s2;
	if( s1 > f1 ) swap(s1,f1);
	if( s2 > f2 ) swap(s2,f2);
	if( f1 < s2 ) return false;
	if( f2 < s1 ) return false;
	return true;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0,t,s,f ; i<n ; ++i){
		scanf("%d%d%d",&person[i].t , &person[i].s , &person[i].f);
		person[i].e = person[i].t + abs(person[i].s - person[i].f);
		person[i].way = (person[i].f > person[i].s)? 1 : -1;
	}
	for(int i=0 ; i<n ; ++i)
		for(int j=i+1 ; j<n ; ++j)
			if( meet(person[i] , person[j]) )
				++ans[i] , ++ans[j];
	for(int i=0 ; i<n ; ++i)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}

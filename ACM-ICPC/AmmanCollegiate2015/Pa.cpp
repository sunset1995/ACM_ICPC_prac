#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

struct team{
	string name;
	int solve;
	int penalty;
};

team Team[104];
bool myCmp(const team &l,const team &r){
	return l.solve > r.solve || (l.solve==r.solve && l.penalty < r.penalty);
}

int main(){
	int T;
	scanf(" %d",&T);
	while( T-- ){
		int N;
		scanf(" %d",&N);
		for(int i=0;i<N;++i)
			cin >> Team[i].name >> Team[i].solve >> Team[i].penalty;
		sort( &Team[0] , &Team[N] , myCmp );
		cout << Team[0].name << endl;
	}
}
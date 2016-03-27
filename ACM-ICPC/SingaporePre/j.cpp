#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct data{
	long long sum , pro , sz;
	data& operator += (const data &rth){
		sum += rth.sum;
		pro = (pro*rth.pro) % 1000000007;
		sz += rth.sz;
	}
	bool operator < (const data &rth) const{
		if( sum<rth.sum ) return true;
		if( sum>rth.sum ) return false;
		if( pro<rth.pro ) return true;
		if( pro>rth.pro ) return false;
		if( sz<rth.sz ) return true;
		if( sz>rth.sz ) return false;
		return false;
	}
	bool operator == (const data &rth) const{
		return sum==rth.sum && pro==rth.pro && sz==rth.sz;
	}
};

inline bool isNum(const char &c){
	return c<='9' && c>='0';
}

void getLine(vector< data > &st){
	vector< data > myStack;
	int tmp = 0;
	int inCh = getchar();
	while( inCh!='\n' ){
		if( isNum(inCh) ){
			tmp *= 10;
			tmp += inCh-'0';
		}
		else if( tmp ){
			myStack.push_back( {tmp,tmp,1} );
			tmp = 0;
		}
		if( inCh==')' ){
			data added = myStack.back();
			myStack.pop_back();
			myStack.back() += added;
			st.push_back( myStack.back() );
		}
		inCh = getchar();
	}
}

int main(){
	int N;
	scanf("%d",&N);
	vector< data > setAlice , setBob;

	getchar();
	getLine( setAlice );
	getLine( setBob );
	sort(setAlice.begin() , setAlice.end());
	sort(setBob.begin() , setBob.end());

	auto itA = setAlice.begin();
	auto itB = setBob.begin();
	int ans = N;
	while( itA!=setAlice.end() && itB!=setBob.end() ){
		if( *itA == *itB ){
			++ans , ++itA , ++itB;
		}
		else if( *itA < *itB )
			++itA;
		else
			++itB;
	}
	printf("%d\n",ans);

	return 0;
}
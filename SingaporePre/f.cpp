#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct BigNum{
	vector<int> val;
	int sz() const{
		return val.size();
	}
	int get(int id) const{
		return id<sz() ? val[id] : 0;
	}
	void add(int id,int v){
		while( id>=sz() ) val.push_back(0);
		val[id] += v;
	}

	BigNum(){ val.push_back(0); }
	BigNum(long long n){
		while( n ){
			val.push_back( n%10000LL );
			n /= 10000LL;
		}
		if( !sz() ) val.push_back(0);
	}
	void fix(){
		int c = 0;
		for(int i=0 ; i<sz() ; ++i){
			val[i] += c;
			c = val[i] / 10000;
			val[i] %= 10000;
		}
		if( c ) val.push_back( c );
	}
	BigNum operator + (const BigNum &rth) const{
		BigNum tmp;
		int to = max(sz() , rth.sz());
		tmp.val.resize( to );
		for(int i=0 ; i<to ; ++i)
			tmp.val[i] = get(i) + rth.get(i);
		tmp.fix();
		return tmp;
	}
	BigNum operator * (const BigNum &rth) const{
		BigNum tmp;
		tmp.val.resize( sz()+rth.sz() );
		for(int i=0 ; i<sz() ; ++i){
			for(int j=0 ; j<rth.sz() ; ++j)
				tmp.val[i+j] += get(i)*rth.get(j);
			tmp.fix();
		}
		return tmp;
	}
	BigNum operator + (const long long &rth) const{
		BigNum tmp = rth;
		tmp = tmp + *this;
		return tmp;
	}
	BigNum operator * (const long long &rth) const{
		BigNum tmp = rth;
		tmp = tmp * (*this);
		return tmp;	
	}
	BigNum operator - (const BigNum &rth) const{
		BigNum tmp = *this;
		for(int i=0 ; i<tmp.sz() ; ++i){
			if( tmp.get(i)<0 || tmp.get(i)<rth.get(i) ){
				tmp.add(i+1 , -1);
				tmp.add(i , 10000);
			}
			tmp.add(i , -rth.get(i));
		}
		tmp.fix();
		return tmp;
	}
};

int main(){
	int N;
	scanf("%d",&N);

	long long x , y;
	long long sigX=0LL , sigY=0LL , sigXX=0LL , sigYY=0LL , sigXY = 0LL;
	for(int i=0 ; i<N ; ++i){
		scanf("%lld%lld",&x,&y);
		sigX += x , sigY += y;
		sigXX += x*x , sigYY += y*y;
		sigXY += x*y;
	}

	BigNum A=sigX , B=sigY , AA=sigXX , BB=sigYY , AB=sigXY;
	BigNum tmp1 = AA*BB*N + AB*A*B*2LL;
	BigNum tmp2 = AB*AB*N + BB*A*A + AA*B*B;
	BigNum ans = tmp1 - tmp2;
	
	while( ans.sz()>1 && ans.val.back()==0 )
		ans.val.pop_back();

	if( ans.val.back()/4 || ans.sz()==1 )
		printf("%d",ans.val.back()/4);
	int last = ans.val.back()%4;
	for(int i=ans.sz()-2 ; i>=0 ; --i){
		printf("%04d",(last*10000 + ans.get(i)) / 4);
		last = (last*10000 + ans.get(i)) % 4;
	}
	putchar('.');
	printf("%04d\n",last*2500);
	return 0;
}
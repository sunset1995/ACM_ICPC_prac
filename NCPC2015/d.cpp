#include <cstdio>
#include <vector>
using namespace std;

bool isPrime(int v) {
	for(int i=2 ; i<v ; ++i)
		if( v%i == 0 ) return false;
	return true;
}

int main() {
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int n;
		scanf("%d",&n);
		vector<int> last;
		if( n==2 ) {
			puts("2");
			continue;
		}
		for(int i=3 ; i<=n ; ++i)
			last.push_back(i);
		int id = 0, step = -1;
		int f1 = 1, f2 = 1;
		while( last.size() > 1 ) {
			int cnt = f1+f2;
			f1 = f2, f2 = cnt;
			cnt %= last.size();
			id = (id+step*cnt+last.size()) % last.size();
			if( isPrime(last[id]) )
				step = -step;
			last.erase(last.begin()+id);
			if( step==1 )
				id = (id-1+last.size()) % last.size();
		}
		printf("%d\n",last[0]);
	}
	return 0;
}

#include <cstdio>
using namespace std;

char buffer[100];

int main(){
	long long la , lb , ra , rb , nowa , nowb;
	int N;
	scanf(" %d",&N);
	fgets( buffer , 100 , stdin );
	while( N-- ){
		la = rb = 0;
		lb = ra = nowa = nowb = 1;
		bool end = false;
		while( !end ){
			switch( getchar() ){
				case 'R':
					la = nowa , lb = nowb;
					nowa += ra , nowb += rb;
					break;
				case 'L':
					ra = nowa , rb = nowb;
					nowa += la , nowb += lb;
					break;
				case '\n':
					end = true;
					break;
			}
		}
		printf("%lld/%lld\n",nowa,nowb);
	}
}
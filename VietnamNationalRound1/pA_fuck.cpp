#include <cstdio>
using namespace std;

int main(){
	int T;
	scanf("%d",&T);
	while( T-- ){
		int k;
		scanf("%d",&k);
		switch(k){
			case 4:
				puts("1210 2020");
				break;
			case 5:
				puts("21200");
				break;
			case 7:
				puts("3211000");
				break;
			case 8:
				puts("42101000");
				break;
			case 9:
				puts("521001000");
				break;
			case 10:
				puts("6210001000");
				break;
			default:
				puts("-1");
		}
	}
	return 0;
}

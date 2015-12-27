#include <cstdio>
using namespace std;

int main() {
	puts("1");
	int num = 30000;
	printf("%d\n", num);
	int x=0, y=0;
	for(int i=1; i<=num; ++i) {
		printf("%d %d\n", x, y);
		x += 1000;
		y += i;
	}
	return 0;
}

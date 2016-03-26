#include <iostream>
#include <cstdio>
using namespace std;

int main () {
	int a, b, c, d;
	while(scanf("%d%d%d%d", &a, &b, &c, &d)==4 && a+b+c+d)
		printf("%d %d\n", c-b, d-a);
}

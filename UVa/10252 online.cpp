#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001;

int main() {
	char a[maxn], b[maxn];
	while (gets(a) != NULL && gets(b) != NULL) {
		sort (a, a + strlen(a));
		sort (b, b + strlen(b));
		for (int i = 0, j = 0; i < strlen(a) && j < strlen(b);) {
			if (a[i] == b[j]) {
				printf("%c", a[i]);
				i++, j++;
			}
			else if (a[i] > b[j])
				j++;
			else
				i++;
		}
		printf("\n");
	}
	return 0;
}

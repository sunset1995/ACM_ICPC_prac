#include <cstdio>
using namespace std;

int main() {
	FILE *out = fopen("input", "w");
	const int sz = 40000;
	fprintf(out, "%d %d 2\n",sz,sz-1);
	for(int i=1 ; i<sz ; ++i)
		fprintf(out, "%d %d\n",i,i+1);
	fprintf(out, "1 %d\n",sz);
	fclose(out);
	return 0;
}

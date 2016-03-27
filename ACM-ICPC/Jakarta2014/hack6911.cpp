#include <cstdio>
using namespace std;

int main(){
	FILE *out = fopen("hack6911.input" , "w");
	fprintf(out , "1\n100000\n");
	for(int i=1 ; i<=100000 ; ++i)
		fprintf(out , "%d %d %d\n",i,500000+i , 1000000-i);
	fclose(out);
	return 0;
}
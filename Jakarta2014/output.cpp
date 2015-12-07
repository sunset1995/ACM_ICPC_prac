#include <cstdio>
using namespace std;

int main(){
	FILE *out = fopen("test6915-2","w");
	fprintf(out , "50\n");
	for(int i=0 ; i<50 ; ++i){
		fprintf(out , "1000000 1\n");
		for(int j=0 ; j<1000000 ; ++j)
			fprintf(out , "%c" , '/');
		fprintf(out , "\n");
	}
	fclose(out);
}
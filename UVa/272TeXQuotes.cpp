#include<cstdio>
using namespace std;
int main(){
	char in;
	bool front = true;
	while( (in=getchar())!=EOF ){
		if(in=='"'){
			if(front){
				putchar('`');
				putchar('`');
				front = !front;
			}
			else{
				putchar('\'');
				putchar('\'');
				front = !front;
			}
		}
		else
			putchar(in);
	}
}

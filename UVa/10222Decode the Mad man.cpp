#include<cstdio>
#include<cstring>
using namespace std;

char table[100] = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
int len = strlen(table);
int findId(char befound){
	if( befound>='A' && befound<='Z' ) befound = befound-'A'+'a';
	for(int i=0;i<len;++i){
		if( befound==table[i] ) return i;
	}
	return 0;
}

int main(){
	char c;
	while( (c=getchar()) ){
		if( c!=' ' && c!='\n' ){
			putchar( table[findId(c)-2] );
		}
		else putchar(c);
	}
}

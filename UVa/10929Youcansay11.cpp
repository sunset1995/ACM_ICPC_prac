#include<cstdio>
using namespace std;
int main(){
	while(1){
		int s[2];
		s[0] = 0, s[1] = 0;
		bool which = 0;
		char input, allinput[1001];
		int top = -1;
		while( 1 ){
			input=getchar();
			if(input=='\n') break;
			allinput[++top] = input;
			s[ which ] += input - '0';
			which = !which;
		}
		if( s[0]==0 ) break;
		allinput[++top] = '\0';
		
		if( (s[0]-s[1])%11==0 )
			printf("%s is a multiple of 11.\n",allinput);
		else
			printf("%s is not a multiple of 11.\n",allinput);
	}
}

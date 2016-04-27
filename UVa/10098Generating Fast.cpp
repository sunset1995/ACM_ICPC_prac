#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

bool used[20];
char s[20],stack[20];
int top , len;
void permutation();

int main(){
  int n;
  scanf(" %d",&n);
  while( n-- ){
  	scanf(" %s",s);
  	len = strlen(s);
  	sort( s, s+len );
  	stack[len] = '\0';
  	top = -1;
  	for(int i=0;i<len;++i) used[i] = false;
  	
  	permutation();
  	printf("\n");
  }
} 

void permutation(){
	if( top>=len-1 ){
		stack[++top] = '\0';
		printf("%s\n",stack);
		--top;
		return;
	}
	char last = '0';
	for(int i=0;i<len;++i){
		if( !used[i] && s[i]!=last ){
			last = s[i];
			used[i] = true,
			stack[++top] = s[i];
			permutation();
			used[i] = false,
			--top;
		}
	}
}

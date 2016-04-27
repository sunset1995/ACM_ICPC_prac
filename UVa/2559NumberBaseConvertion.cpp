#include<cstdio>
#define MAX 1000
using namespace std;
char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int ascii[127];
int main(){
	int tmpval = 0;
	for(int i='0';i<='9';++i) ascii[i] = tmpval++;
	for(int i='A';i<='Z';++i) ascii[i] = tmpval++;
	for(int i='a';i<='z';++i) ascii[i] = tmpval++;
	int n;
	scanf(" %d",&n);
	while( n-- ){
		int ori , tar;
		char str[MAX];
		int val[MAX];
		int ans[MAX] , ansTop = -1;
		scanf(" %d%d%s",&ori,&tar,str);
		printf("%d %s\n",ori,str);
		int top;
		for(top=0;str[top]!='\0';++top)
			val[top] = ascii[ str[top] ];
		int now = 0;
		while( now<top ){
			int next = 0;
			for(int i=now;i<top;++i){
				val[i] += ori*next;
				next = val[i]%tar;
				val[i] /= tar;
			}
			ans[ ++ansTop ] = next;
			while( now<top && val[now]==0 ) ++now;
		}
		printf("%d ",tar);
		for(int i=ansTop;i>=0;--i){
			printf("%c",table[ ans[i] ]);
		}
		printf("\n\n");
	}
}

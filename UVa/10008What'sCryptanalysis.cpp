#include<cstdio>
using namespace std;
int main(){
	int n;
	char c;
	typedef struct{
		int count;
		char alph;
	} ch;
	ch total[26];
	
	while( scanf(" %d",&n)!=EOF ){
		char del[100];
		gets(del);
	for(int i=0;i<26;++i){
		total[i].count = 0;
		total[i].alph = 'A'+i;
	}
	while( n-- ){
		while( (c=getchar()) && c!='\n' ){
			if( c>='a' && c<='z' ){
				++total[c-'a'].count;
			}
			else if( c>='A' && c<='Z' ){
				++total[c-'A'].count;
			}
		}
	}
	
	for(int i=0;i<26;++i){
		if( total[i].count==0 ) continue;
		for(int j=i+1;j<26;++j){
			if( total[i].count < total[j].count || (total[i].count == total[j].count && total[i].alph>total[j].alph) ){
				ch tmp;
				tmp = total[i];
				total[i] = total[j];
				total[j] = tmp;
			}
		}
	}
	
	for(int i=0;i<26;++i)
		if( total[i].count )
			printf("%c %d\n",total[i].alph,total[i].count);
		
	}
	return 0;
}

#include <cstdio>
#include <cstring>
using namespace std;

struct Node{
	bool used;
	char ch;
	int inPath;
	bool next[26];
}node[26];
int myCmp(char *str1,char *str2){
	int index = 0;
	while( str1[index]!='\0' && str2[index]!='\0' && str1[index]==str2[index] )
		++index;
	if( str1[index]=='\0' || str2[index]=='\0' )
		return -1;
	return index;
}

int main(){
	for(int i=0;i<26;++i){
		node[i].used = false;
		node[i].ch = i+'A';
		node[i].inPath = 0;
		memset( node[i].next , 0 , sizeof(node[i].next) );
	}
	char tmp1[50] , tmp2[50];
	char *last , *now;
	last = tmp1 , now = tmp2;
	int cnt = 1;
	scanf(" %s",last);
	while( scanf(" %s",now)!=EOF && now[0]!='#' ){
		int which = myCmp( now,last );
		if( which!=-1 ){
			int smallOne = last[which]-'A' , bigOne = now[which]-'A';
			if( node[ smallOne ].next[ bigOne ]!=true ){
				node[ smallOne ].used = true;
				node[ bigOne ].used = true;
				node[ smallOne ].next[ bigOne ] = true;
				++node[ bigOne ].inPath;
			}
		}
		char *tmp = last;
		last = now;
		now = tmp;
		++cnt;
	}
	if( cnt==1 ){
		printf("%c\n",tmp1[0]);
		return 0;
	}
	int nowAt;
	for(int i=0;i<26;++i)
		if( node[i].used && node[i].inPath==0 ){
			nowAt = i;
			break;
		}
	bool stillNext = true;
	char ans[30] , top = -1;
	while( stillNext ){
		stillNext = false;
		ans[++top] = node[nowAt].ch;
		int tmp = nowAt;
		for(int i=0;i<26;++i)
			if( node[tmp].next[i] ){
				--node[i].inPath;
				if( node[i].inPath <= 0 )
					nowAt = i , stillNext = true;
			}
	}
	ans[++top] = '\0';
	printf("%s\n",ans);
}
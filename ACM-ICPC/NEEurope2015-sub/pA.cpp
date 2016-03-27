#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

struct myCmp{
	bool operator()(const char* const a,const char* const b) const{
		return strcmp(a,b)<0;
	}
};

void bmailize(char *str){
	bool login_part = true;
	for(int i=0,j=0 ; true ; ++i , ++j){
		while( login_part && str[j]=='.' ) ++j;
		str[i] = str[j];
		if( str[j]=='@' ) login_part = false;
		if( str[j]=='\0' ) break;
	}
	for(int i=0,j=0 ; true ; ++i , ++j){
		if( str[j]=='+' )
			while( str[j]!='@' )
				++j;
		str[i] = str[j];
		if( str[j]=='\0' ) break;
	}
}
void nomalize(char *str){
	for(int i=0 ; str[i]!='\0' ; ++i)
		if( str[i]>='A' && str[i]<='Z' )
			str[i] = str[i]-'A'+'a';

	bool bmail = false;
	for(int i=0 ; str[i]!='\0' ; ++i)
		if( str[i]=='@' ){
			bmail = strcmp(&str[i] , "@bmail.com")==0;
			break;
		}

	if( bmail )
		bmailize(str);
}

char ori[20004][104];
char nor[20004][104];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0 ; i<n; ++i){
		scanf("%s",ori[i]);
		strcpy(nor[i] , ori[i]);
	}

	for(int i=0 ; i<n ; ++i)
		nomalize(nor[i]);

	map<char*,int,myCmp> dic;
	vector< vector<int> > ans;
	for(int i=0 ; i<n ; ++i){
		auto it = dic.find(nor[i]);
		if( it==dic.end() ){
			dic.insert({nor[i] , ans.size()});
			ans.push_back({i});
		}
		else
			ans[it->second].push_back(i);
	}
	printf("%d\n",(int)ans.size());
	for(auto &v : ans){
		printf("%d",(int)v.size());
		for(auto &w : v)
			printf(" %s",ori[w]);
		puts("");
	}
	return 0;
}

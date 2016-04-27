#include<cstdio>
#include<cstring>
using namespace std;
int l1,l2,l3;
int top1,top2,top3;
char s1[201],s2[201],s3[401];
bool recursive();
int main(){
	int t;
	scanf(" %d",&t);
	for(int i=1;i<=t;++i){
		scanf(" %s%s%s",s1,s2,s3);
		l1=strlen(s1),l2=strlen(s2),l3=l1+l2;
		top1=0,top2=0,top3=0;
		//printf("Data set %d: ",i);
		//if( recursive() ) printf("yes\n");
		//else printf("no\n");
	}
} 

bool recursive(){
	if( top3==l3 ) return true;
	
	if(top1<l1 && s3[top3]==s1[top1]){
		++top1,++top3;
		if( recursive() ) return true;
		--top1,--top3;
	}
	
	if(top2<l2 && s3[top3]==s2[top2]){
		++top2,++top3;
		if( recursive() ) return true;
		--top2,--top3;
	}
	
	return false;
}

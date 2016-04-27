#include <cstdio>
#include <cstring>
using namespace std;

class trie{
	public:
		int init(){
			memset( next[0] , 0 , sizeof(next[0]) );
			top = 0;
		}
		bool addPhone(const char *phone){
			int now = 0;
			for(int i=0;phone[i]!='\0';++i){
				if( next[now][phone[i]-'0']==0 ){
					++top;
					memset( next[top] , 0 , sizeof(next[top]) );
					end[top] = false;
					next[now][phone[i]-'0'] = top;	
				}
				now = next[now][phone[i]-'0'];
				if( end[now]==true )
					return false;
			}
			end[now] = true;
			for(int i=0;i<10;++i)
				if( next[now][i]!=0 )
					return false;
			return true;
		}
	private:
		int next[100004][10];
		bool end[100004];
		int top;
} phoneList;

char buffer[50];
int main(){
	int t;
	scanf(" %d",&t);
	while( t-- ){
		phoneList.init();
		int n;
		scanf(" %d",&n);
		bool yes = true;
		for(int i=0;i<n;++i){
			scanf(" %s",buffer);
			if( yes )
				yes = phoneList.addPhone( buffer );
		}
		if( yes ) printf("YES\n");
		else printf("NO\n");
	}
}
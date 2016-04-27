#include <cstdio>
#include <vector>
using namespace std;
int main(){
	int CASE;
	char str[200];
	scanf(" %d",&CASE);
	fgets( str , 200 , stdin );
	while( CASE-- ){
		fgets( str , 200 , stdin );
		vector<char> wait;
		int index = 0;
		while( str[index]!='\n' ){
			if( str[index]=='(' || str[index]=='[' )
				wait.push_back( str[index] );
			else if( wait.empty() || (wait.back()=='(' && str[index]==']') || (wait.back()=='[' && str[index]==')') )
				break;
			else
				wait.pop_back();
			++index;
		}
		if( str[index]=='\n' && wait.empty() )
			printf("Yes\n");
		else
			printf("No\n");
	}
}
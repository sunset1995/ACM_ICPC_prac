#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct cmp1{
	bool operator()(const int &a,const int &b)const
	{return a<b;}
};

int main(){
	vector<int> plate;
	priority_queue< int , vector<int> ,cmp1 > listToDo;
	char input[1024];
	while( fgets(input,1024,stdin)!=NULL ){
		char *token = strtok(input," \n");
		bool first = true;
		while( token!=NULL ){
			int val;
			sscanf(token," %d",&val);
			if( !val ) break;
			plate.push_back(val);
			listToDo.push(val);
			if(first){
				printf("%d",val);
				first = !first;
			}
			else printf(" %d",val);
			token = strtok(NULL," \n");
		}
		printf("\n");
		int totalSize = plate.size();
		while( !plate.empty() && !listToDo.empty() ){
			int now = listToDo.top();
			listToDo.pop();
			if( plate.back()==now ){
				plate.pop_back();
				continue;
			}
			vector<int>::iterator id;
			id = find( plate.begin() , plate.end() , now );
			if( id-plate.begin() ){
				printf("%d ", totalSize-(int)(id-plate.begin()) ); 
				reverse( plate.begin() , ++id );
			}
			printf("%d ",totalSize-(int)plate.size()+1);
			reverse( plate.begin() , plate.end() );
			plate.pop_back();
		}
		printf("0\n");
		plate.clear();
		while( !listToDo.empty() ) listToDo.pop();
	}
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

bool killed[100004];
int data[100004][3];
struct event{
	int id , dataid , type;
	bool operator < (const event &rth) const{
		return id < rth.id;
	}
};

int main(){
	int T;
	scanf("%d",&T);
	for(int NCASE = 1 ; NCASE<=T ; ++NCASE){
		memset(killed , 0 , sizeof(killed));
		int N;
		scanf("%d",&N);
		set< int > st;
		for(int i=0,v ; i<N ; ++i){
			scanf("%d%d%d",&v,&data[i][0] , &data[i][1]);
			data[i][2] = v;
			st.insert( v );
		}
		
		int ans = st.size();
		vector< event > es;
		for(int i=0 ; i<N ; ++i){
			auto it = st.lower_bound( data[i][0] );
			if( it!=st.end() && (*it) == data[i][2] ) ++it;

			if( it!=st.end() && (*it) <= data[i][1] )
				killed[i] = true;
			else{
				es.push_back( {data[i][0] , i , 0} );
				es.push_back( {data[i][1] , i , 1} );
			}
		}

		sort( es.begin() , es.end() );
		vector<int> left;
		int lastSet = -1;
		for(auto &v : es){
			if( killed[ v.dataid ] ) continue;
			if( v.id == lastSet ){
				killed[ v.dataid ] = true;
				continue;
			}
			if( v.type == 0 )
				left.push_back( v.dataid );
			else{
				++ans;
				lastSet = v.id;
				for(auto &j : left)
					killed[j] = true;
				left.clear();
			}
		}
		printf("Case #%d: %d\n",NCASE , ans);
	}
	return 0;
}
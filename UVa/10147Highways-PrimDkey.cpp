#include <cstdio>
#include <vector>
using namespace std;

template<class pqType>
class pqDkey{
	private:
		// stop user from using assignment and copy constructor
		pqDkey& operator = (const pqDkey&);
		pqDkey(const pqDkey&);

		typedef bool(*comFunc)(const pqType&,const pqType&);
		comFunc userCmp;
	protected:
		// pqHeap is used to implement full binary tree
		std::vector< pqType > pqHeap;
		// to reference pqHeap
		std::vector< int > ref;
		// to let pqHeap reference ref
		std::vector< int > refref;
		int parent(int id) const{ return id/2; }
		int left(int id) const{ return id*2; }
		int right(int id) const{ return id*2+1; }
		bool hasParent(int id) const{ return id!=1; }
		bool hasLeft(int id) const{ return left(id)<pqHeap.size(); }
		bool hasRight(int id) const{ return right(id)<pqHeap.size(); }
		void pqHeapSwap(int,int);
		void downward(int);
		void upward(int);
	public:
		pqDkey(comFunc myCmp){
			userCmp = myCmp;
			init();
		}
		void init();
		bool empty();
		pqType extractMin();
		void push(const pqType&);
		void decrease(int,const pqType&);
};


template<class pqType>
void pqDkey<pqType>::pqHeapSwap(int id1,int id2){
	pqType tmpData = pqHeap[id1];
	pqHeap[id1] = pqHeap[id2];
	pqHeap[id2] = tmpData;

	int tmprefref = refref[id1];
	refref[id1] = refref[id2];
	refref[id2] = tmprefref;

	ref[ refref[id1] ] = id2;
	ref[ refref[id2] ] = id1;
}

template<class pqType>
void pqDkey<pqType>::downward(int id){
	if( !hasLeft(id) )
		return;
	int minId = left(id);
	if( hasRight(id) && userCmp( pqHeap[right(id)] , pqHeap[minId] ) )
		minId = right(id);
	if( userCmp( pqHeap[minId] , pqHeap[id] ) ){
		pqHeapSwap( minId , id );
		downward( minId );
	}
}

template<class pqType>
void pqDkey<pqType>::upward(int id){
	if( !hasParent(id) )
		return;
	int parentId = parent(id);
	if( userCmp( pqHeap[id] , pqHeap[parentId] ) ){
		pqHeapSwap( id , parentId );
		upward( parentId );
	}
}

template<class pqType>
void pqDkey<pqType>::init(){
	pqType zero;
	pqHeap.clear();
	pqHeap.push_back( zero );
	ref.clear();
	ref.push_back( 0 );
	// when pushIn data bind to ref
	// ref will always know where is the data in pqHeap
}

template<class pqType>
bool pqDkey<pqType>::empty(){
	return pqHeap.size()==1;
}

template<class pqType>
pqType pqDkey<pqType>::extractMin(){
	if( empty() )
		return pqHeap[0];
	pqType minData = pqHeap[1];

	pqHeap[1] = pqHeap.back();
	refref[1] = refref.back();
	ref[ refref[1] ] = 1;
	ref[ refref.back() ] = 0;
	pqHeap.pop_back();
	refref.pop_back();
	if( !empty() ) // if just only one data in pq
		downward(1);
	return minData;
}

template<class pqType>
void pqDkey<pqType>::push(const pqType &rth){
	pqHeap.push_back( rth );
	ref.push_back( pqHeap.size()-1 );
	refref.push_back( ref.size()-1 );
	upward( pqHeap.size()-1 );
}

template<class pqType>
void pqDkey<pqType>::decrease(int outsideID , const pqType &smallerData){
	int id = ref[ outsideID ];
	pqHeap[id] = smallerData;
	upward(id);
}

const int infinite = 0x3FFFFFFF;

struct NODE{
	int x,y,cost,from,id;
} node[800];
bool lowest[800];
int howmuch(const NODE &a,const NODE &b){
	int difX = a.x - b.x,
		 difY = a.y - b.y;
	return difX*difX + difY*difY;
}
int map[800][800];

bool myCmp(const NODE &a,const NODE &b){
	return a.cost < b.cost;
}
pqDkey<NODE> PQ(myCmp);
 
void prim(int N){
	for(int i=0;i<=N;++i)
		lowest[i] = false,
		node[i].cost = infinite,
		node[i].id = i;
	node[1].cost = 0;
	PQ.init();
	for(int i=1;i<=N;++i)
		PQ.push( node[i] );
	while( !PQ.empty() ){
		NODE nowAt = PQ.extractMin();
		lowest[ nowAt.id ] = true;
		for(int i=1;i<=N;++i)
			if( !lowest[i] && map[nowAt.id][i] < node[i].cost ){
				node[i].cost = map[nowAt.id][i];
				PQ.decrease( i , node[i] );
				node[i].from = nowAt.id;
			}
	}
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	while( NCASE-- ){
		int N,M;
		scanf(" %d",&N);
		for(int i=1;i<=N;++i){
			scanf(" %d%d",&node[i].x , &node[i].y);
			for(int j=1;j<=i;++j)
				map[i][j] = map[j][i] = howmuch(node[i],node[j]);
		}
		scanf(" %d",&M);
		for(int i=0,u,v;i<M;++i){
			scanf(" %d%d",&u,&v);
			map[u][v] = map[v][u] = 0;
		}
		prim(N);
		bool haveAns = false;
		for(int i=1;i<=N;++i)
			if( node[i].cost ){
				printf("%d %d\n",i,node[i].from);
				haveAns = true;
			}
		if( !haveAns )
			printf("No new highways need\n");
		if( NCASE )
			printf("\n");
	}
}
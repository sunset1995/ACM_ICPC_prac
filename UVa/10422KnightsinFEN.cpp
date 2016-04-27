#include <cstdio>
#include <queue>
using namespace std;

struct stateDetail{
	int knight , blank , step;
	inline int state() const{
		return (blank<<25) + knight;
	}
};
class knightProblem{
	public:
		void setProblem();
		void solveProblem();
	private:
		stateDetail now;
		int ansState();
		int countDiff(const int&);
		void dfs(const stateDetail&,const int&);
		bool ansFound;
		const int nextGo[8][2] = { {1,2} , {-1,-2} , {-1,2} , {1,-2} , {2,1} , {-2,-1} , {-2,1} , {2,-1} };
		const int hFunc[25] = {
			4,1,2,1,4,
			1,2,3,2,1,
			2,3,0,3,2,
			1,2,3,2,1,
			4,1,2,1,4
		};
};
int knightProblem::ansState() {
	static int content = 0b11001111101111000110000100000;
	return content;
}
int knightProblem::countDiff(const int &tmpState){
	static int careNum = 25;
	int count = 0;
	int diff = (tmpState^ansState());
	for(int i=0,mask=1 ; i<careNum ; ++i,mask<<=1)
		if( diff&mask )
			++count;
	return count;
}
void knightProblem::setProblem(){
	now.knight = 0 , now.step = 0;
	char input[20];
	for(int i=0;i<5;++i){
		fgets( input , 20 , stdin );
		for(int j=0;j<5;++j){
			now.knight <<= 1;
			switch( input[j] ){
				case'1': ++now.knight; break;
				case' ': now.blank = (4-i)*5 + (4-j);
			}
		}
	}
	ansFound = false;
}
void knightProblem::solveProblem(){
	for(int i=0;i<11 && !ansFound;++i)
		dfs( now , i );
	if( ansFound )
		printf("Solvable in %d move(s).\n",now.step);
	else
		printf("Unsolvable in less than 11 move(s).\n");
}
void knightProblem::dfs(const stateDetail &nowAt,const int &deep){
	if( nowAt.step==deep ){
		if( nowAt.state()==ansState() ){
			ansFound = true;
			now = nowAt;
		}
		return;
	}
	if( nowAt.step + countDiff(nowAt.knight)/2 > 10 )
		return;
	for(int i=0;i<8 && !ansFound;++i){
		int x = nowAt.blank%5;
		if( x+nextGo[i][1]<0 || x+nextGo[i][1]>4 ) continue;
		stateDetail tmp = { nowAt.knight , nowAt.blank+nextGo[i][0]*5+nextGo[i][1] , nowAt.step+1 };
		if( tmp.blank>24 || tmp.blank<0 || tmp.step+hFunc[ tmp.blank ]>10 ) continue;
		if( tmp.knight & (1<<tmp.blank) ){
			tmp.knight &= ~(1<<tmp.blank);
			tmp.knight |= 1<<nowAt.blank;
		}
		if( tmp.step + countDiff(tmp.knight)/2 > 10 )
			continue;
		dfs( tmp , deep );
	}
}

int main(){
	int NCASE;
	scanf(" %d",&NCASE);
	char garbageNewline[20];  fgets( garbageNewline , 20 , stdin );

	knightProblem table;
	while( NCASE-- ){
		table.setProblem();
		table.solveProblem();
	}
}
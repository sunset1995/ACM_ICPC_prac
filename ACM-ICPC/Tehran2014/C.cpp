#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int T, P ,S;
int sts[154][20];
bool good() {
	for(int i=0; i<T; ++i) {
		int teamSolved = 0;
		for(int j=0; j<P; ++j)
			teamSolved += sts[i][j];
		if( teamSolved==0 || teamSolved==P ) {
			//printf("GG %d\n", teamSolved);
			return false;
		}
	}
	for(int i=0; i<P; ++i) {
		int beSolved = 0;
		for(int j=0; j<T; ++j)
			beSolved += sts[j][i];
		if( beSolved==0 || beSolved==T ) {
			//printf("BB %d\n", beSolved);
			return false;
		}
	}
	return true;
}

long long cvTime(int HH, int MM, int SS) {
	return HH*10000 + MM*100 + SS;
}
void showTime(int T) {
	printf("%02d:%02d:%02d", T/10000, T%10000/100, T%100);
}
struct event {
	int stime, problem, team;
	event(int stime, int problem, int team)
	:stime(stime), problem(problem), team(team) {}
	bool operator < (const event &rth) const {
		return stime < rth.stime;
	}
};

int main() {
	while( scanf("%d%d%d", &T, &P, &S)!=EOF ) {
		if(!T && !P && !S) break;
		vector<event> es;
		int team, HH, MM, SS;
		char problem[100], st[100];
		for(int i=0; i<S; ++i) {
			scanf("%d", &team);
			scanf("%s", problem);
			scanf("%d:%d:%d", &HH, &MM, &SS);
			fgets(st, 100, stdin);
			if( strstr(st, "Yes")!=nullptr )
				es.emplace_back(event(
					cvTime(HH, MM, SS),
					problem[0]-'A',
					team-1
				));
		}
		memset(sts, 0, sizeof(sts));
		sort(es.begin(), es.end());
		int sGood=-1, eGood=-1;
		for(int i=0; i<es.size(); ++i) {
			sts[es[i].team][es[i].problem] = 1;
			if( sGood==-1 ) {
				if( good() ) sGood = es[i].stime;
			}
			else if( eGood==-1 ) {
				if( !good() ) eGood = es[i].stime;
			}
		}
		if( sGood==-1 )
			puts("--:--:-- --:--:--");
		else if( eGood==-1 ) {
			showTime(sGood);
			puts(" --:--:--");
		}
		else {
			showTime(sGood);
			putchar(' ');
			showTime(eGood);
			putchar('\n');
		}
	}
	return 0;
}

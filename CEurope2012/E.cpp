#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <map>
using namespace std;
const int N=505 , LENG=2020 ;
struct node {
	int L , R ;
	string str ;
	bool app[26] , mer ;
	node(){}
	node(int L_,int R_,string str_):L(L_),R(R_),str(str_){
		int i ;
		memset(app,0,sizeof(app)) ;
		for(i=0 ; i<str.size() ; i++)
			app[str[i]-'a'] = 1 ;
		mer = 0 ;
	}
} nd[N] ;
map<string,int> num ;
int ndnum ;
char pattern[LENG] ;
void init() {
	num.clear() ;
	ndnum = 0 ;
}
int index(string s) {
	if(num.count(s))
		return num[s] ;
	return num[s] = ndnum++ ;
}
void DFS(int u,int &pt) {
	//puts("AAAAAAA") ;
	if(!pattern[pt]) return ;
	if(nd[u].L!=-1 && nd[u].R!=-1) {
		if(!pattern[pt]) return ;
		if(!nd[u].mer || nd[nd[u].L].app[pattern[pt]-'a']) DFS(nd[u].L,pt) ;
		if(!pattern[pt]) return ;
		if(!nd[u].mer || nd[nd[u].R].app[pattern[pt]-'a']) DFS(nd[u].R,pt) ;
		if(!pattern[pt]) return ;
		if(!nd[u].mer) {
			for(int i=0 ; i<26 ; i++) {
				nd[u].app[i] |= nd[nd[u].L].app[i] ;
				nd[u].app[i] |= nd[nd[u].R].app[i] ;
			}
			nd[u].mer = 1 ;
		}
	} else {
		for(int i=0 ; nd[u].app[pattern[pt]-'a'] && pattern[pt] && i<nd[u].str.size() ; i++) {
			if(!pattern[pt]) return ;
			if(pattern[pt] == nd[u].str[i])
				pt++ ;
			if(!pattern[pt]) return ;
		}
	}
}
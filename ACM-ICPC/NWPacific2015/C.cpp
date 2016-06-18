#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#define N 1010
using namespace std;
int clas[N][256], dis[N], lst[N];
string name[N];
bool cmp(int u,int v) {
	for(int i = 0; i < dis[u] || i < dis[v]; i++)
		if(clas[u][i] != clas[v][i])
			return clas[u][i] < clas[v][i];
	return strcmp(name[u].c_str(), name[v].c_str()) > 0;
}
int main () {
	//cout << strcmp("dad", "unclebob") << endl;
	int n;
	char empty[3];
	scanf("%d", &n);
	gets(empty);
	for(int i = 0; i < n; i++) {
		string in;
		getline(cin, in);
		stringstream input(in);
		input >> name[i];
		name[i] = name[i].substr(0,name[i].size()-1);
		dis[i] = 0;
		lst[i] = i;
		memset(clas[i], 0, sizeof(clas[i]));
		while(input >> in) {
			if(in == "upper")
				clas[i][dis[i]++] = 1;
			else if(in == "middle")
				clas[i][dis[i]++] = 0;
			else
				clas[i][dis[i]++] = -1;
		}
		reverse(clas[i], clas[i]+dis[i]);
	}
	sort(lst, lst+n, cmp);
	for(int i = n-1; i >= 0; i--)
		cout << name[lst[i]] << endl;
}

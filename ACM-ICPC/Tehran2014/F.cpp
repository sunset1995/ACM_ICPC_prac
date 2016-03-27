#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

int main()
{
	long long int h = 0, m = 0, th, tm, op;
	string str, hs, ms;
	char opc;

	while (getline(cin, str)){
		if (str == "$$$" || str == "###"){
			h += m / 60;
			m = m % 60;
			if (m < 0LL){
				h -= 1; m += 60;
			}
			cout << h << ":" << setw(2) <<setfill('0')<< m << endl;
			h = 0LL, m = 0LL;
			if (str == "###"){
				break;
			}
			else{
				continue;
			}
		}
		opc = str[0];
		str = str.substr(1, str.size());

		int sep;
		if ((sep = str.find(":")) != string::npos){
			hs = str.substr(0, sep);
			ms = str.substr(sep + 1, str.size() - sep);
		}
		else if ((sep = str.find(".")) != string::npos){
			hs = str.substr(0, sep);
			ms = str.substr(sep + 1, str.size() - sep);
		}

		if (hs.size() == 0)hs = "0";
		if (ms.size() == 0)ms = "0";
		//cout << "TEST::" << hs << " " << ms << endl;

		op = opc == '-' ? -1LL : 1LL;
		h += stoi(hs) * op;
		m += stoi(ms) * op;
	}
	//system("pause");
	return 0;
}

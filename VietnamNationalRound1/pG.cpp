#include <iostream>
#include <cstring>
using namespace std;

char board[250][250] = { 0 };
int movX[4] = { 1,1,-1,-1 };
int movY[4] = { 1,-1,-1,1 };

int main()
{
	int test_num, n;

	cin.tie(NULL);
	cin.sync_with_stdio(false);

	memset(board, 'w', sizeof(board));
	board[100][100] = 'b';
	for (int i = 97; i >= -102; i -= 3) {
		for (int px = i, py = 100, it = -1; it != 4; px = px + movX[it], py = py + movY[it]) {
			if (px == 100 || py == 100)it++;
			if (px < 0 || px>230 || py < 0 || py>230) {
				continue;
			}
			board[px][py] = 'b';
		}
	}

	cin >> test_num;
	while (test_num--) {
		cin >> n;
		for (int i = 100 - n; i <= 100 + n; i++) {
			for (int j = 100 - n; j <= 100 + n; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	}
	//system("pause");
	return 0;
}
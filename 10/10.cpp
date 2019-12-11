#include <iostream>
#include <string>
#include <numeric>
#include <iomanip>

using namespace std;

int main()
{
	const int MAX = 50;
	int board[MAX][MAX];
	bool asts[MAX][MAX];
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = 0;
			asts[i][j] = false;
		}
	}

	string s;
	int h = 0, w = 0;
	{
	int i = 1;
	do {
		getline(cin, s);
		if (cin.eof()) break;
		w = s.size();
		for (int j = 1; j <= s.size(); j++) {
			asts[i][j] = s[j - 1] == '#' ? true : false;
		}
		i++;
	} while (!cin.eof());
	h = i - 1;
	}

	int maks = 0, maxx, maxy;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (!asts[i][j]) continue;
			for (int k = j + 1; k <= w; k++) {
				if (asts[i][k]) {
					board[i][j]++;
					board[i][k]++;
					break;
				}
			}
			for (int k = i + 1; k <= h; k++) {
				if (asts[k][j]) {
					board[i][j]++;
					board[k][j]++;
					break;
				}
			}
			for (int k = i + 1; k <= h; k++) {
				for (int l = 1; l <= w; l++) {
					if (j == l || !asts[k][l]) continue;
					cout << i << " " << j << " " << k << " " << l << "\n";
					int a = i - k;
					int b = j - l;
					int c = 1;
					while ((c = gcd(a, b)) != 1) {
						a /= c;
						b /= c;
					}
					int x = k + a, y = l + b;
					bool collision = false;
					while (x != i) {
						if (asts[x][y]) {
							collision = true;
							break;
						}
						x += a;
						y += b;
					}
					if (!collision) {
						board[i][j]++;
						board[k][l]++;
					}
				}
			}
			if (maks < board[i][j]) {
				maks = board[i][j];
				maxx = i;
				maxy = j;
			}
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cout << setw(3) << board[i][j];
		}
		cout << "\n";
	}
	cout << h << " " << w << "\n";
	cout << maks << "\n";
}

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int W = 25;
const int H = 6;
const int BITS = W*H;
struct layer {
	layer() {
		for (int i = 0; i < 3; i++) {
			bits[i] = 0;
		}
		for (int i = 0; i < BITS; i++) {
			lay[i] = 0;
		}
	}
	int bits[3];
	int lay[BITS];
};

int main()
{
	vector <layer> ls;
	int j = 0;
	while (!cin.eof()) {
		ls.push_back({});
		for (int i = 0; i < BITS; i++) {
			char c;
			cin >> c;
			if (cin.eof()) break;
			ls[j].bits[c - '0']++;
			ls[j].lay[i] = c - '0';
		}
		++j;
	}
	{
		int mini = 100000;
		int mi = 0;
		for (int i = 0; i < ls.size() - 1; i++) {
			if (mini > ls[i].bits[0]) {
				mini = ls[i].bits[0];
				mi = i;
			}
		}
		cout << "first answer: " << ls[mi].bits[1] * ls[mi].bits[2] << "\n";
	}

	int answer[BITS];
	for (int i = 0; i < BITS; i++) {
		answer[i] = 2;
	}

	for (int j = 0; j < ls.size(); j++) {
		for (int i = 0; i < BITS; i++) {
			if (answer[i] == 2) {
				answer[i] = ls[j].lay[i];
			}
		}
	}
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (answer[i * W + j] == 1) {
				cout << "# ";
			} else {
				cout << "  ";
			}
		}
		cout << "\n";
	}
}

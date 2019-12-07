#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	const int MAX = 1000;
	int buffer[MAX];
	int buffer2[MAX];
	int n;
	int i = 0;
	while (true) {
		cin >> n;
		if (cin.eof()) break;
		buffer2[i++] = n;
		cin.get();
	}
	for (int k = 0; k < 100; k++) {
		for (int p = 0; p < 100; p++) {
			memcpy(buffer, buffer2, MAX);
			buffer[1] = k;
			buffer[2] = p;
			for (int j = 0; j < i; j += 4) {
				int a = buffer[j + 3];
				if (buffer[j] == 1) {
					buffer[a] = buffer[buffer[j + 1]] + buffer[buffer[j + 2]];
				} else if (buffer[j] == 2) {
					buffer[a] = buffer[buffer[j + 1]] * buffer[buffer[j + 2]];
				} else if (buffer[j] == 99) {
					break;
				}
			}
			cout << 100 * k + p << "\n";
			if (buffer[0] == 19690720) {
				cout << ":D\n";
				return 0;
			}
		}
	}
}

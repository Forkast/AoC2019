#include <iostream>
#include <cstring>

using namespace std;

int mpow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * mpow(x, p-1);
}

int main()
{
	int sum = 0;
	int sums[10];
	for (int i = 264793; i < 803935; i++) {
		for (int j = 5; j >= 1; j--) {
			int a = (i / mpow(10, j)) % 10;
			int b = (i / (mpow(10, j - 1)) % 10);
			if (b < a) {
				for (int k = j; k >= 1; k--) {
					int c = (i / (mpow(10, k - 1)) % 10);
					i += (a - c) * mpow(10, k - 1);
				}
				break;
			}
		}
		if (i > 803935) break;
		cout << i << "\n";
		for (int j = 0; j < 10; j++) {
			sums[j] = 0;
		}
		for (int j = 0; j < 6; j++) {
			int a = (i / mpow(10, j)) % 10;
			int b = (i / (mpow(10, j + 1)) % 10);
			if (j + 1 == 6) b = 100;
			sums[a]++;
			if (a != b) {
				if (sums[a] == 2) {
					sum++;
					cout << "dodane\n";
					break;
				}
				sums[a] = 0;
			}
		}
		
	}
	cout << sum << "\n";
}

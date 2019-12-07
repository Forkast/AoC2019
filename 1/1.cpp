#include <iostream>

using namespace std;

int main()
{
	int n;
	long long int sum = 0;
	while (!cin.eof()) {
		cin >> n;
		if (cin.eof()) break;
		int b = n / 3 - 2;
		while (b > 0) {
			sum += b;
			b = b / 3 - 2;
		}
	}
	cout << sum << endl;
}

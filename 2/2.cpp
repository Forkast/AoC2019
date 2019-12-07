#include <iostream>

using namespace std;

int main()
{
	int buffer[1000];
	int n;
	int i = 0;
	while (true) {
		cin >> n;
		if (cin.eof()) break;
		buffer[i++] = n;
		cout << i - 1 << " -> " << n << endl;
		cin.get();
	}
	buffer[1] = 12;
	buffer[2] = 2;
	for (int j = 0; j < i; j += 4) {
		int a = buffer[j + 3];
		if (buffer[j] == 1) {
			buffer[a] = buffer[buffer[j + 1]] + buffer[buffer[j + 2]];
			cout << "buffer[" <<  a << "] = " << buffer[buffer[j + 1]] << " + " << buffer[buffer[j + 2]] << " = " << buffer[a] << "\n";
		} else if (buffer[j] == 2) {
			buffer[a] = buffer[buffer[j + 1]] * buffer[buffer[j + 2]];
			cout << buffer[a] << " = " << buffer[buffer[j + 1]] << " * " << buffer[buffer[j + 2]] << " = " << buffer[a] << "\n";
		} else if (buffer[j] == 99) {
			break;
		}
	}
	cout << buffer[0] << endl;
}

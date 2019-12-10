#include <iostream>
#include <sstream>

using namespace std;


inline
void parameters(long long buffer[], int i, int base, long long & first, int fmode)
{
	switch (fmode) {
	case 0:
		first = buffer[buffer[i + 1]];
		break;
	case 1:
		first = buffer[i + 1];
		break;
	case 2:
		first = buffer[base + buffer[i + 1]];
		break;
	}
}

inline
void parameters(long long buffer[], int i, int base, long long & first, int fmode, long long & second, int smode)
{
	parameters(buffer, i, base, first, fmode);
	parameters(buffer, i + 1, base, second, smode);
}

inline
void parameters(long long buffer[], int i, int base, long long & first, int fmode, long long & second, int smode, long long & third)
{
	parameters(buffer, i, base, first, fmode);
	parameters(buffer, i + 1, base, second, smode);
	parameters(buffer, i + 2, base, third, 1);
}

inline
void parameters(long long buffer[], int i, int base, long long & first, int fmode, long long & second, int smode, long long & third, int tmode)
{
	parameters(buffer, i, base, first, fmode);
	parameters(buffer, i + 1, base, second, smode);
	parameters(buffer, i + 2, base, third, tmode);
}

int main()
{
	long long buffer[20000];
	int n;
	int i = 0;
	int input = 2;
	int base = 0;
	string s;
	getline(cin, s);
	stringstream ss(s);
	while (true) {
		ss >> n;
		buffer[i++] = n;
// 		cout << i - 1 << " -> " << n << " " << buffer[i - 1] << endl;
		if (ss.eof()) break;
		ss.ignore();
	}
	
	for (int j = 0; j < i;) {
		int fmode = buffer[j] / 100 % 10;
		int smode = buffer[j] / 1000 % 10;
		int tmode = buffer[j] / 10000 % 10;
		int opcode = buffer[j] % 100;
		cout << "opcode " << buffer[j] << " " << opcode << " " << buffer[j + 1] << " " << buffer[j + 2] << " " << buffer[j + 3] << "\n";
		long long first, second, third;
		switch (opcode) {
		case 1:
			parameters(buffer, j, base, first, fmode, second, smode, third);
			if (tmode == 2) third += base;
			buffer[third] = first + second;
			cout << "buffer[" <<  third << "] = " << first << " + " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 2:
			parameters(buffer, j, base, first, fmode, second, smode, third);
			if (tmode == 2) third += base;
			buffer[third] = first * second;
			cout << "buffer[" << third << "] = " << first << " * " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 99:
			j++;
			return 0;
		case 3:
			tmode = fmode;
			if (fmode == 2) tmode = 1;
			parameters(buffer, j, base, first, tmode);
			cout << "buffer[" << first << "] = " << input << " = " << buffer[first] << "\n";
			if (fmode == 2)
				first = base + first;
			buffer[first] = input;
			cout << "buffer[" << first << "] = " << input << " = " << buffer[first] << "\n";
			j += 2;
			break;
		case 4:
			parameters(buffer, j, base, first, fmode);
			cout << "output: " << first << "\n";
			j += 2;
			break;
		case 5:
			parameters(buffer, j, base, first, fmode, second, smode);
			cout << first << " != 0, jump to " << second << "\n";
			if (first != 0) {
				j = second;
			} else {
				j += 3;
			}
			break;
		case 6:
			cout << first << " " << second << " " << smode << " " << base << "\n";
			parameters(buffer, j, base, first, fmode, second, smode);
			cout << first << " " << second << " " << smode << " " << base << "\n";
			cout << first << " == 0, jump to " << second << "\n";
			if (first == 0) {
				j = second;
			} else {
				j += 3;
			}
			break;
		case 7:
			parameters(buffer, j, base, first, fmode, second, smode, third);
			if (tmode == 2) third += base;
			if (first < second) {
				buffer[third] = 1;
			} else {
				buffer[third] = 0;
			}
			cout << "buffer[" << third << "] = " << first << " < " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 8:
			parameters(buffer, j, base, first, fmode, second, smode, third);
			if (tmode == 2) third += base;
			if (first == second) {
				buffer[third] = 1;
			} else {
				buffer[third] = 0;
			}
			cout << "buffer[" << third << "] = " << first << " == " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 9:
			tmode = fmode;
			if (fmode == 2) tmode = 1;
			parameters(buffer, j, base, first, tmode);
			if (fmode == 2) {
				cout << "mode buffer[" << base + first << "] = " << buffer[base + first] << "\n";
				first = buffer[base + first];
			}
			base += first;
			j += 2;
			break;
		}
	}
}

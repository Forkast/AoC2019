#include <iostream>
#include <sstream>

using namespace std;


inline
void parameters(int buffer[], int i, int & first, bool fmode)
{
	if (fmode) {
		first = buffer[i + 1];
	} else {
		first = buffer[buffer[i + 1]];
	}
}

inline
void parameters(int buffer[], int i, int & first, bool fmode, int & second, bool smode)
{
	parameters(buffer, i, first, fmode);
	parameters(buffer, i + 1, second, smode);
}

inline
void parameters(int buffer[], int i, int & first, bool fmode, int & second, bool smode, int & third)
{
	parameters(buffer, i, first, fmode);
	parameters(buffer, i + 1, second, smode);
	parameters(buffer, i + 2, third, true);
}

inline
void parameters(int buffer[], int i, int & first, bool fmode, int & second, bool smode, int & third, bool tmode)
{
	parameters(buffer, i, first, fmode);
	parameters(buffer, i + 1, second, smode);
	parameters(buffer, i + 2, third, tmode);
}

int main()
{
	int buffer[1000];
	int n;
	int i = 0;
	int input = 5;
	string s;
	getline(cin, s);
	stringstream ss(s);
	while (true) {
		ss >> n;
		buffer[i++] = n;
		cout << i - 1 << " -> " << n << " " << buffer[i - 1] << endl;
		if (ss.eof()) break;
		ss.ignore();
	}
	
	for (int j = 0; j < i;) {
		int fmode = buffer[j] / 100 % 10;
		int smode = buffer[j] / 1000 % 10;
// 		int tmode = buffer[j] / 10000 % 10;
		int opcode = buffer[j] % 100;
		cout << "opcode " << opcode << " " << buffer[j + 1] << " " << buffer[j + 2] << " " << buffer[j + 3] << "\n";
		int first, second, third;
		switch (opcode) {
		case 1:
			parameters(buffer, j, first, fmode, second, smode, third);
			buffer[third] = first + second;
			cout << "buffer[" <<  third << "] = " << first << " + " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 2:
			parameters(buffer, j, first, fmode, second, smode, third);
			buffer[third] = first * second;
			cout << "buffer[" << third << "] = " << first << " * " << second << " = " << buffer[third] << "\n";
			j += 4;
			break;
		case 99:
			j++;
			return 0;
		case 3:
			cout << "input " << buffer[j + 1] << " " << j + 1 << "\n";
			buffer[buffer[j + 1]] = input;
			j += 2;
			break;
		case 4:
			parameters(buffer, j, first, fmode);
			cout << "output: " << first << "\n";
			if (first < 0 || first > 0) {
				cout << "fail on position " << j << "\n";
			}
			j += 2;
			break;
		case 5:
			parameters(buffer, j, first, fmode, second, smode);
			if (first != 0) {
				j = second;
			} else {
				j += 3;
			}
			break;
		case 6:
			parameters(buffer, j, first, fmode, second, smode);
		cout << "opcode " << opcode << " " << first << " " << second << " " << buffer[15] << "\n";
			if (first == 0) {
				j = second;
			} else {
				j += 3;
			}
			break;
		case 7:
			parameters(buffer, j, first, fmode, second, smode, third);
			if (first < second) {
				buffer[third] = 1;
			} else {
				buffer[third] = 0;
			}
			j += 4;
			break;
		case 8:
			parameters(buffer, j, first, fmode, second, smode, third);
			if (first == second) {
				buffer[third] = 1;
			} else {
				buffer[third] = 0;
			}
			j += 4;
			break;
		}
	}
}
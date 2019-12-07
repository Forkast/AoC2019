#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

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


int run(int buffer[], const vector<int> & input, int & j, int & i)
{
	while (true) {
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
			return -99;
		case 3:
			cout << "input " << buffer[j + 1] << " " << j + 1 << "\n";
			buffer[buffer[j + 1]] = input[i++];
			j += 2;
			break;
		case 4:
			parameters(buffer, j, first, fmode);
			cout << "output: " << first << "\n";
			j += 2;
			return first;
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
	return -1;
}

struct state {
	int buffer[1000];
	int pos;
	int in_pos;
	vector<int> input;
};

int main()
{
	int program[1000];
	int n;
	int i = 0;
	vector <int> phase_perm{5, 6, 7, 8, 9};
	vector <state> states;
	int phase = 0;
	string s;
	getline(cin, s);
	stringstream ss(s);
	int max = 0;
	while (true) {
		ss >> n;
		program[i++] = n;
		cout << i - 1 << " -> " << n << " " << program[i - 1] << endl;
		ss.ignore();
		if (ss.eof()) break;
	}
	bool next = true;
	while (next) {
		cout << "NEW CONFIGURATION\n";
		states.clear();
		for (int i = 0; i < phase_perm.size(); i++) {
			state si;
			copy(program, program + i, si.buffer);
			si.pos = 0;
			si.in_pos = 0;
			states.push_back(si);
		}
		for (int i = 0; i < phase_perm.size(); i++) {
			states[i].input.push_back(phase_perm.at(i));
		}
		states[0].input.push_back(0);
		bool exit = false;
		while (!exit) {
			for (int i = 0; i < phase_perm.size(); i++) {
				cout << "PROGRAM NUMBER " << i << " WITH PHASE " << phase_perm[i] << "\n";
				int output = run(program,
								 states[i].input,
								 states[i].pos,
								 states[i].in_pos
								);
				cout << "OUTPUT " << output << "\n";
				if (output == -99) {
					exit = true;
					break;
				}
				cout << "PUSHING INTO " << (i + 1) % phase_perm.size() << "\n";
				states[(i + 1) % phase_perm.size()]
					.input
					.push_back(output);
			}
			cout << "EXIT " << exit << "\n";
		}
		next = next_permutation(phase_perm.begin(), phase_perm.end());
		cout << states[0].input.back() << "\n";
		max = max < states[0].input.back() ? states[0].input.back() : max;
		cout << "the end " << max << "\n";
		cout << "NEXT " << next << "\n";
	}
	cout << "the end " << max << "\n";
}

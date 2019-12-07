#include <iostream>
#include <istream>
#include <unordered_map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

using namespace std;

unordered_map<string,vector<string>> nodes;
unordered_map<string, int> values;
int summer = 0;
int min_common = 0;

void insert(const string & index)
{
	cout << "insert " << index << "\n";
	if (nodes.find(index) == nodes.end()) return;
	const vector<string> & toInsert = nodes.at(index);
	int sum = values[index];
	for (const auto & n : toInsert) {
		values[n] = sum + 1;
		summer += sum + 1;
		insert(n);
	}
}

int common(const string & index)
{
	int retval = 0;
	if (!index.compare("YOU") || !index.compare("SAN")) retval = 1;
	if (nodes.find(index) == nodes.end()) return retval;
	const vector<string> & toInsert = nodes.at(index);
	for (const auto & n : toInsert) {
		retval += common(n);
	}

	if (retval == 2) {
		if (min_common < values[index]) min_common = values[index];
		cout << values[index] << "\n";
	}
	if (retval > 2) {
		cout << "dupa\n";
	}
	return retval;
}

int main()
{

	string s;
	while (!cin.eof()) {
		getline(cin, s);
		int pos = s.find(')');
		if (pos != std::string::npos) {
			cout << s.substr(0, pos) << " " << s.substr(pos + 1) << "\n";
			if (nodes.find(s.substr(0, pos)) == nodes.end()) {
				nodes[s.substr(0, pos)] = {s.substr(pos + 1)};
			} else {
				nodes.at(s.substr(0, pos)).push_back(s.substr(pos + 1));
			}
		}
	}
	const string com("COM");
	values[com] = 0;
	insert(com);
	common(com);
	cout << summer << "\n";
	cout << values["YOU"] << " " << values["SAN"] << "\n";
	cout << values["YOU"] - min_common + values["SAN"] - min_common << "\n";
	cout << "common: " << min_common << "\n";
}
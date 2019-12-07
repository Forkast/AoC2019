#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct point {
	int x, y;
}

void parse(vector<point> & v, const string & s) {
	stringstream ss(s);
	while (!ss.eof()) {
		char dir;
		int num;
		ss >> dir >> num;
		ss.ignore(1);
		if (ss.eof()) return;
		int x = v.at(v.size() - 1).x, y = v.at(v.size() - 1).y;
		point p{x, y};
		switch (dir) {
			case 'U':
				p.y += num
				break;
			case 'D':
				p.y -= num
				break;
			case 'R':
				p.x += num
				break;
			case 'L':
				p.x -= num
				break;
		}
		v.push_back(p);
	}
}

inline int minimum(int a, int b)
{
	return a < b ? a : b;
}

inline int maximum(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	string line1;
	string line2;
	vector<point> v1{1, {0, 0}};
	vector<point> v2{1, {0, 0}};
	getline(stdin, line1);
	getline(stdin, line2);
	parse(v1, line1);
	parse(v2, line2);
	int miin = 100000;
	for (int i = 0; i < v1.size() - 1; i++) {
		for (int j = 0; j < v2.size() - 1; j++) {
			point p11 = {minimum(v1.at(i).x, v1.at(i + 1).x), minimum(v1.at(i).y, v1.at(i + 1).y)};
			point p12 = {maximum(v1.at(i).x, v1.at(i + 1).x), maximum(v1.at(i).y, v1.at(i + 1).y)};
			point p21 = {minimum(v2.at(i).x, v2.at(i + 1).x), minimum(v2.at(i).y, v2.at(i + 1).y)};
			point p22 = {maximum(v2.at(i).x, v2.at(i + 1).x), maximum(v2.at(i).y, v2.at(i + 1).y)};
			if (
				
			) {
				int mn = abs(p.x) + abs(p.y);
				if (mn < miin) {
					miin = mn;
				}
			}
		}
	}
}

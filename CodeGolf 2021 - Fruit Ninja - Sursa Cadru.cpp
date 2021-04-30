#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <memory>
#include <iterator>
#include <functional>

using namespace std;

int  n;
int  m;
std::vector<std::vector<unsigned char>> s;

void f(unsigned char t, unsigned char r, unsigned char c, unsigned char l)
{

}

int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		cout << "No arguments";
		return 1;
	}

	string inputFile = argv[1];
	ifstream in(inputFile.c_str(), ios::in);
	std::streambuf* cinbuf = std::cin.rdbuf();      // save stdin buffer
	std::cin.rdbuf(in.rdbuf());                     // redirect std::cin to input file (.in)
	if (!in.is_open())
	{
		cout << "Cannot open input file";
		return 1;
	}

	string line;

	getline(in, line);
	std::istringstream smn(line);
	smn >> n >> m;

	unsigned char t;
	int r, c, l;
	while (getline(in, line)) {
		std::istringstream ss(line);
		ss >> t >> r >> c;
		if (ss >> l) {
			f(t, (unsigned char)r, (unsigned char)c, (unsigned char)l);
		}
		else {
			f(t, (unsigned char)r, (unsigned char)c, NULL);
		}
	}

	std::cin.rdbuf(cinbuf);                        // reset to stdin again
	return 0;
}

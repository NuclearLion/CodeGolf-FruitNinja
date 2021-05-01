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

int n;
int m;
std::vector<std::vector<unsigned char>> s;

void f(unsigned char t, unsigned char r, unsigned char c, unsigned char l) {
    static int round;
    static int score;
    static int missed;
    vector<unsigned char> lin;
    vector<unsigned char> linSpec;
    round++;
    if (round == 1) {
        for (int i = 0; i < n; ++i)
            lin.push_back('.');
        for (int i = 0; i < n; ++i)
            if (i != c - 1)
                linSpec.push_back('.');
            else
                linSpec.push_back('o');

        for (int j = 0; j < m; ++j)
            if (j != r - 1)
                s.push_back(lin);
            else
                s.push_back(linSpec);
    } else {

    }


    cout << "Round: " << round << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << s[i][j];
        cout << '\n';
    }
    cout << "Score: " << score << '\n';

}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        cout << "No arguments";
        return 1;
    }

    string inputFile = argv[1];
    ifstream in("test.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();      // save stdin buffer
    std::cin.rdbuf(in.rdbuf());                     // redirect std::cin to input file (.in)
    if (!in.is_open()) {
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
            f(t, (unsigned char) r, (unsigned char) c, (unsigned char) l);
        } else {
            f(t, (unsigned char) r, (unsigned char) c, NULL);
        }
    }

    std::cin.rdbuf(cinbuf);                        // reset to stdin again
    return 0;
}

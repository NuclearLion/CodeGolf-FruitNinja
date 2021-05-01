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
    vector<int> del;
    struct fruitInside {
        int currentI, currentJ;
        unsigned char type;

        void setParameters(int i, int j, unsigned char ty) {
            currentI = i;
            currentJ = j;
            type = ty;
        }
    };
    static vector<fruitInside> droppedFruits;

    if (round == 0) {
        s.resize(n, vector<unsigned char>(m, '.'));
        s[r - 1][c - 1] = 'o';
        droppedFruits.push_back(fruitInside());
        droppedFruits[round].setParameters(r - 1, c - 1, t);

    } else {
        for (int frPoz = 0; frPoz < droppedFruits.size(); ++frPoz) {
            s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
            droppedFruits[frPoz].currentI += 1;
        }

        droppedFruits.push_back(fruitInside());
        droppedFruits[round].setParameters(r - 1, c - 1, t);

        int tempSize = droppedFruits.size();
        for (int frPoz = 0; frPoz < tempSize; ++frPoz) {
            if (droppedFruits[frPoz].currentI >= n) {
                missed++;
                tempSize--;
                droppedFruits.erase(droppedFruits.begin() + frPoz);
            }
        }
        for (int frPoz = 0; frPoz < tempSize; ++frPoz) {
            s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = 'o';

        }
    }

    cout << "Round: " << round + 1 << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << s[i][j];
        cout << '\n';
    }
    cout << "Score: " << score << '\n';
    cout << "Missed: ";
    if(missed > 0) {
        for (int i = 1; i <= missed; ++i)
            cout << 'X';
             
    }
    cout << '\n' << '\n';
    ++round;
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

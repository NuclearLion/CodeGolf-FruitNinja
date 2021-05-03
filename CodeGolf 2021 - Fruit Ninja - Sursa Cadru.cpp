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

ofstream fout("output.out");

void f(unsigned char t, unsigned char r, unsigned char c, unsigned char l) {
    static int round;
    static int score;
    static int missed;
    vector<int> del;
    struct fruitInside {
        int currentI, currentJ;
        int type;

        void setParameters(int i, int j, int ty) {
            currentI = i;
            currentJ = j;
            type = ty - '0';
        }
    };
    static vector<fruitInside> droppedFruits;
    if (round == 0) { //first generation
        s.resize(n, vector<unsigned char>(m, '.'));
        s[r - 1][c - 1] = 'o';
        droppedFruits.push_back(fruitInside());
        droppedFruits[round].setParameters(r - 1, c - 1, t);

    } else { //next iterations
        cout << '\n' << '\n';
        //matrix dropping. replace fruits with '.'. Increasing I in stack
        for (int frPoz = 0; frPoz < droppedFruits.size(); ++frPoz) {
            switch (droppedFruits[frPoz].type) {
                case 1:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                case 2:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ + 1] = '.';
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                default:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    cout << "!!!DEBUG1!!!";
            }
        }
        /*for(auto fruit : droppedFruits)
        { //TODO look into it
            switch (fruit.type) {
                case 1:
                    s[fruit.currentI][fruit.currentJ] = '.';
                    fruit.currentI += fruit.type;
                    break;
                case 2:
                    s[fruit.currentI][fruit.currentJ] = '.';
                    s[fruit.currentI][fruit.currentJ + 1] = '.';
                    fruit.currentI += fruit.type;
                    break;
                default:
                    s[fruit.currentI][fruit.currentJ] = '.';
                    fruit.currentI += fruit.type;
                    cout << "!!!DEBUG1!!!";
            }
        }*/

        //delete outside fruits from the stack
        auto it = droppedFruits.begin();
        while (it != droppedFruits.end()) {
            if (it->currentI >= n) {
                it = droppedFruits.erase(it);
                missed++;
            } else {
                ++it;
            }
        }
        //add new fruits in the stack
        int iter = droppedFruits.size();
        droppedFruits.push_back(fruitInside());
        droppedFruits[iter].setParameters(r - 1, c - 1, t);
        //draw the new matrix
        for(auto fruit : droppedFruits){
            switch (fruit.type) {
                case 1:
                    s[fruit.currentI][fruit.currentJ] = 'o';
                    break;
                case 2:
                    s[fruit.currentI][fruit.currentJ] = '+';
                    s[fruit.currentI][fruit.currentJ + 1] = '+';
                    break;
                default:
                    cout << "CurrentI " << fruit.currentI << " CurrentJ "
                         << fruit.currentJ << " type " << fruit.type;
                    cout << "!!!DEBUG2!!!";
                    s[fruit.currentI][fruit.currentJ] = 'P';
            }
        }
    }

    //display
    cout << "Round: " << round + 1 << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << s[i][j];
        cout << '\n';
    }
    cout << "Score: " << score << '\n';
    cout << "Missed: ";
    for (int i = 1; i <= missed; ++i)
        cout << 'X';
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

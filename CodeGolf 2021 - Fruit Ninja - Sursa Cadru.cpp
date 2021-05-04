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
        int finalI, finalJ;
        bool cut = false;

        void setParameters(int i, int j, int ty) {
            currentI = i;
            currentJ = j;
            type = ty - '0';
            switch (type) {
                case 1:
                    finalI = i;
                    finalJ = j;
                    break;
                case 2:
                    finalI = i;
                    finalJ = j + 1;
                    break;
                case 3:
                    finalI = i + 2;
                    finalJ = j;
                    break;
                case 4:
                    finalI = i + 1;
                    finalJ = j + 1;
                    break;
                case 5:
                    finalI = i + 2;
                    finalJ = j + 2;
                    break;
                case 6:
                    finalI = i + 2;
                    finalJ = j + 4;
                    break;
                default:
                    cout << "debug set parameters";
            }
        }
    };
    static vector<fruitInside> droppedFruits;
    if (round == 0) { //first generation
        s.resize(n, vector<unsigned char>(m, '.'));
        droppedFruits.push_back(fruitInside());
        droppedFruits[round].setParameters(r - 1, c - 1, t);
        switch (droppedFruits[0].type) {
            case 1:
                s[r - 1][c - 1] = 'o';
                break;
            case 2:
                s[r - 1][c - 1] = '+';
                s[r - 1][c] = '+';
                break;
            case 3:
                s[r - 1][c - 1] = '(';
                s[r][c - 1] = '(';
                s[r + 1][c - 1] = '(';
                break;
            case 4:
                s[r - 1][c - 1] = '@';
                s[r - 1][c] = '@';
                s[r][c - 1] = '@';
                s[r][c] = '@';
                break;
            case 5:
                for (int i = r - 1; i <= r + 1; ++i)
                    for (int j = c - 1; j <= c + 1; ++j)
                        s[i][j] = '^';
                break;
            case 6:
                for (int i = r - 1; i <= r + 1; ++i)
                    for (int j = c - 1; j <= c + 3; ++j)
                        s[i][j] = '{';
                break;
            default:
                cout << "DEBUG 1st";
                s[r - 1][c - 1] = 'D';
        }
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
                case 3:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    if (droppedFruits[frPoz].currentI + 1 < n)
                        s[droppedFruits[frPoz].currentI + 1][droppedFruits[frPoz].currentJ] = '.';
                    if (droppedFruits[frPoz].currentI + 2 < n)
                        s[droppedFruits[frPoz].currentI + 2][droppedFruits[frPoz].currentJ] = '.';
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                case 4:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ + 1] = '.';
                    if (droppedFruits[frPoz].currentI + 1 < n) {
                        s[droppedFruits[frPoz].currentI + 1][droppedFruits[frPoz].currentJ] = '.';
                        s[droppedFruits[frPoz].currentI + 1][droppedFruits[frPoz].currentJ + 1] = '.';
                    }
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                case 5:
                    for (int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 2; ++i) {
                        if (i < n) {
                            for (int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 2; ++j)
                                s[i][j] = '.';
                        } else
                            break;
                    }
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                case 6:
                    for (int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 2; ++i) {
                        if (i < n) {
                            for (int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 4; ++j)
                                s[i][j] = '.';
                        } else
                            break;
                    }
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    break;
                default:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = '.';
                    droppedFruits[frPoz].currentI += droppedFruits[frPoz].type;
                    cout << "!!!DEBUG1!!!";
            }
        }
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


        ///ADD fruits or CUT fruits
        if (t != '-') { //ADD
            //add new fruits in the stack
            int iter = droppedFruits.size();
            droppedFruits.push_back(fruitInside());
            droppedFruits[iter].setParameters(r - 1, c - 1, t);
        } else {//DELETE
            switch (t) {
                case '-':
                    for (int frPoz = 0; frPoz < droppedFruits.size(); ++frPoz) {
                        for (int Xc = c - 1; Xc <= c - 2 + l; ++Xc)
                            if ((droppedFruits[frPoz].currentI <= r - 1 || droppedFruits[frPoz].finalI >= r - 1) &&
                                (droppedFruits[frPoz].currentJ <= Xc || droppedFruits[frPoz].finalJ >= Xc)) {
                                droppedFruits[frPoz].cut = true;
                            }
                    }
                    auto it = droppedFruits.begin();
                    while (it != droppedFruits.end()) {
                        if (it->cut == true) {
                            score += it->type;
                            it = droppedFruits.erase(it);
                        } else {
                            ++it;
                        }
                    }
                    break;
            }
        }

        //draw the new matrix
        for (auto fruit : droppedFruits) {
            switch (fruit.type) {
                case 1:
                    s[fruit.currentI][fruit.currentJ] = 'o';
                    break;
                case 2:
                    s[fruit.currentI][fruit.currentJ] = '+';
                    s[fruit.currentI][fruit.currentJ + 1] = '+';
                    break;
                case 3:
                    s[fruit.currentI][fruit.currentJ] = '(';
                    if (fruit.currentI + 1 < n)
                        s[fruit.currentI + 1][fruit.currentJ] = '(';
                    if (fruit.currentI + 2 < n)
                        s[fruit.currentI + 2][fruit.currentJ] = '(';
                    break;
                case 4:
                    s[fruit.currentI][fruit.currentJ] = '@';
                    s[fruit.currentI][fruit.currentJ + 1] = '@';
                    if (fruit.currentI + 1 < n) {
                        s[fruit.currentI + 1][fruit.currentJ] = '@';
                        s[fruit.currentI + 1][fruit.currentJ + 1] = '@';
                    }
                    break;
                case 5:
                    for (int i = fruit.currentI; i <= fruit.currentI + 2; ++i) {
                        if (i < n)
                            for (int j = fruit.currentJ; j <= fruit.currentJ + 2; ++j)
                                s[i][j] = '^';
                        else
                            break;
                    }
                    break;
                case 6:
                    for (int i = fruit.currentI; i <= fruit.currentI + 2; ++i) {
                        if (i < n)
                            for (int j = fruit.currentJ; j <= fruit.currentJ + 4; ++j)
                                s[i][j] = '{';
                        else
                            break;
                    }
                    break;
                default:
                    cout << "CurrentI " << fruit.currentI << " CurrentJ "
                         << fruit.currentJ << " type " << fruit.type;
                    cout << "!!!DEBUG2!!!";
                    s[fruit.currentI][fruit.currentJ] = 'D';
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

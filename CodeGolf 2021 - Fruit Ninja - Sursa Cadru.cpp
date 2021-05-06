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
    static bool redrawn = false;
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
                case 7:
                    finalI = i + 1;
                    finalJ = j + 2;
                    break;
                default:
                    cout << "debug set parameters";
            }
        }
    };
    static vector<fruitInside> droppedFruits;

    if (round == 0) { ///first generation
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
            case 7:
                for (int i = r - 1; i <= r; ++i)
                    for (int j = c - 1; j <= c + 1; ++j)
                        s[i][j] = '$';
                break;
            default:
                cout << "DEBUG 1st";
                s[r - 1][c - 1] = 'D';
        }
    } else { ///next iterations
        cout << '\n' << '\n';
        ///matrix dropping. replace fruits with '.'. Increasing I in stack
        if (missed < 3) {
            for (auto & droppedFruit : droppedFruits) {
                switch (droppedFruit.type) {
                    case 1:
                        s[droppedFruit.currentI][droppedFruit.currentJ] = '.';
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 2:
                        s[droppedFruit.currentI][droppedFruit.currentJ] = '.';
                        s[droppedFruit.currentI][droppedFruit.currentJ + 1] = '.';
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 3:
                        s[droppedFruit.currentI][droppedFruit.currentJ] = '.';
                        if (droppedFruit.currentI + 1 < n)
                            s[droppedFruit.currentI + 1][droppedFruit.currentJ] = '.';
                        if (droppedFruit.currentI + 2 < n)
                            s[droppedFruit.currentI + 2][droppedFruit.currentJ] = '.';
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 4:
                        s[droppedFruit.currentI][droppedFruit.currentJ] = '.';
                        s[droppedFruit.currentI][droppedFruit.currentJ + 1] = '.';
                        if (droppedFruit.currentI + 1 < n) {
                            s[droppedFruit.currentI + 1][droppedFruit.currentJ] = '.';
                            s[droppedFruit.currentI + 1][droppedFruit.currentJ + 1] = '.';
                        }
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 5:
                        for (int i = droppedFruit.currentI; i <= droppedFruit.currentI + 2; ++i) {
                            if (i < n) {
                                for (int j = droppedFruit.currentJ; j <= droppedFruit.currentJ + 2; ++j)
                                    s[i][j] = '.';
                            } else
                                break;
                        }
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 6:
                        for (int i = droppedFruit.currentI; i <= droppedFruit.currentI + 2; ++i) {
                            if (i < n) {
                                for (int j = droppedFruit.currentJ; j <= droppedFruit.currentJ + 4; ++j)
                                    s[i][j] = '.';
                            } else
                                break;
                        }
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    case 7:
                        for (int i = droppedFruit.currentI; i <= droppedFruit.currentI + 1; ++i) {
                            if (i < n) {
                                for (int j = droppedFruit.currentJ; j <= droppedFruit.currentJ + 2; ++j)
                                    s[i][j] = '.';
                            } else
                                break;
                        }
                        droppedFruit.currentI += droppedFruit.type;
                        droppedFruit.finalI += droppedFruit.type;
                        break;
                    default:
                        s[droppedFruit.currentI][droppedFruit.currentJ] = '.';
                        droppedFruit.currentI += droppedFruit.type;
                        cout << "!!!DEBUG1!!!";
                }
            }
            ///delete outside fruits from the stack
            auto it = droppedFruits.begin();
            while (it != droppedFruits.end()) {
                if (it->currentI >= n) {
                    if (it->type != 7)
                        missed++;
                    it = droppedFruits.erase(it);
                } else {
                    ++it;
                }
            }
        }
        ///GAME OVER
        if (missed == 3) {
            if (!redrawn) {
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
                        case 7:
                            for (int i = fruit.currentI; i <= fruit.currentI + 1; ++i) {
                                if (i < n)
                                    for (int j = fruit.currentJ; j <= fruit.currentJ + 2; ++j)
                                        s[i][j] = '$';
                                else
                                    break;
                            }
                            break;
                        default:
                            cout << "CurrentI " << fruit.currentI << " CurrentJ "
                                 << fruit.currentJ << " type " << fruit.type;
                            cout << "!!!DEBUG game over!!!";
                            s[fruit.currentI][fruit.currentJ] = 'D';
                    }
                }
                redrawn = true;
            }
            //cout << '\n' << '\n';
            cout << "Round: " << round + 1 << '\n';
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j)
                    cout << s[i][j];
                cout << '\n';
            }
            cout << "Score: " << score << '\n';
            cout << "Missed: " << "XXX" << '\n' << "Game Over! You lost!";
            ++round;
            return;
        }
        ///ADD fruits or CUT fruits
        if (t >= 48 && t <= 71) { //ADD
            //add new fruits in the stack
            int iter = droppedFruits.size();
            droppedFruits.push_back(fruitInside());
            droppedFruits[iter].setParameters(r - 1, c - 1, t);
        } else {///CUT
            switch (t) {
                case '-':
                    for (auto & droppedFruit : droppedFruits) {
                        for (int Xc = c - 1; Xc <= c - 2 + l; ++Xc)
                            if ((droppedFruit.currentI <= r - 1 && droppedFruit.finalI >= r - 1) &&
                                (droppedFruit.currentJ <= Xc && droppedFruit.finalJ >= Xc)) {
                                if (droppedFruit.type != 7)
                                    droppedFruit.cut = true;
                                else {
                                    score += 100;
                                    break;
                                }
                            }
                    }
                    break;
                case '|':
                    for (auto & droppedFruit : droppedFruits) {
                        for (int Xr = r - 1; Xr >= r - l; --Xr) //deleted -2
                            if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                                (droppedFruit.currentJ <= c - 1 && droppedFruit.finalJ >= c - 1))
                                if (droppedFruit.type != 7)
                                    droppedFruit.cut = true;
                                else {
                                    score += 100;
                                    break;
                                }
                    }
                    break;
                case '/':
                    for (auto & droppedFruit : droppedFruits) {
                        int Xr = r - 1;
                        int Xc = c - 1;
                        while (Xc <= c - 2 + l) {
                            if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                                (droppedFruit.currentJ <= Xc &&
                                 droppedFruit.finalJ >= Xc))
                                if (droppedFruit.type != 7)
                                    droppedFruit.cut = true;
                                else {
                                    score += 100;
                                    break;
                                }
                            --Xr;
                            ++Xc;
                        }
                    }
                    break;
                case '\\':
                    for (auto & droppedFruit : droppedFruits) {
                        int Xr = r - 1;
                        int Xc = c - 1;
                        while (Xr >= r - l) { //deleted -2
                            if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                                (droppedFruit.currentJ <= Xc &&
                                 droppedFruit.finalJ >= Xc))
                                if (droppedFruit.type != 7)
                                    droppedFruit.cut = true;
                                else {
                                    score += 100;
                                    break;
                                }
                            --Xr;
                            --Xc;
                        }
                    }
                    break;
                default:
                    cout << "DEBUG cutting";
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
        }
        ///placement of the first pivot
        for(auto &fruit : droppedFruits)
        {
            switch (fruit.type) {
                case 1:
                    s[fruit.currentI][fruit.currentJ] = 'o';
                    break;
                case 2:
                    s[fruit.currentI][fruit.finalJ] = '+';
                    cout << "\n pozitie +" << fruit.currentI << " " << fruit.currentJ  << " " << s[17][5] << '\n'; //todo del
                    break;
                case 3:
                    s[fruit.currentI][fruit.finalJ] = '(';
                    break;
                case 4:
                    s[fruit.currentI][fruit.finalJ] = '@';
                    break;
                case 5:
                    s[fruit.currentI][fruit.finalJ] = '^';
                    break;
                case 6:
                    s[fruit.currentI][fruit.finalJ] = '{';
                    break;
                case 7:
                    s[fruit.currentI][fruit.finalJ] = '$';
                    break;
            }
        }

        ///draw the new matrix
        for (int frPoz = 0; frPoz < droppedFruits.size(); ++frPoz) {
            switch (droppedFruits[frPoz].type) {
                case 1:
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = 'o';
                    break;
                case 2:
                    for(int j = droppedFruits[frPoz].currentJ + 1; j <= droppedFruits[frPoz].currentJ + 1; ++j)
                        if(s[droppedFruits[frPoz].currentI][j] == '.')
                            s[droppedFruits[frPoz].currentI][j] = '+';
                    break;
                case 3:
                    for(int i = droppedFruits[frPoz].currentI + 1; i <= droppedFruits[frPoz].currentI + 2; ++i)
                        if(i < n) {
                            if (s[i][droppedFruits[frPoz].currentJ] == '.') {
                                cout << "\n pozitie (" << i << " " << droppedFruits[frPoz].currentJ  << '\n'; //todo del
                                s[i][droppedFruits[frPoz].currentJ] = '(';
                            }
                        }
                        else
                            break;
                    break;
                case 4:
                    for(int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 1; ++i)
                        if(i < n){
                            for(int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 1; ++j)
                                if(s[i][j] == '.')
                                    s[i][j] = '@';
                        }
                        else
                            break;
                    break;
                case 5:
                    for (int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 2; ++i) {
                        if (i < n)
                            for (int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 2; ++j) {
                                if (s[i][j] == '.')
                                    s[i][j] = '^';
                            }
                        else
                            break;
                    }
                    break;
                case 6:
                    for (int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 2; ++i) {
                        if (i < n)
                            for (int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 4; ++j)
                                s[i][j] = '{';
                        else
                            break;
                    }
                    break;
                case 7:
                    for (int i = droppedFruits[frPoz].currentI; i <= droppedFruits[frPoz].currentI + 1; ++i) {
                        if (i < n)
                            for (int j = droppedFruits[frPoz].currentJ; j <= droppedFruits[frPoz].currentJ + 2; ++j)
                                s[i][j] = '$';
                        else
                            break;
                    }
                    break;
                default:
                    cout << "CurrentI " << droppedFruits[frPoz].currentI << " CurrentJ "
                         << droppedFruits[frPoz].currentJ << " type " << droppedFruits[frPoz].type;
                    cout << "!!!DEBUG2!!!";
                    s[droppedFruits[frPoz].currentI][droppedFruits[frPoz].currentJ] = 'D';
            }
        }
    }
    ///display
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

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
    static bool broken = false;
    static bool frozen = false;
    static bool bombHit = false;
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
                case 8:
                    finalI = i + 4;
                    finalJ = j;
                    break;
                case 9:
                    finalI = i + 2;
                    finalJ = j + 3;
                    break;
            }
        }
    };
    static vector<fruitInside> droppedFruits;
    auto displayMatrix = [](bool gameOver, bool gameWon, bool swordBroken) {
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
        if (gameOver)
            cout << '\n' << "Game Over! You lost!";
        if (gameWon)
            cout << '\n' << "Well played! You won!";
        if (swordBroken)
            cout << '\n' << "Game Over! My sword is broken!";
        if (frozen)
            cout << '\n' << "Banana freeze on! Nothing falls next turn!";
        if (bombHit)
            cout << '\n' << "Game Over! You hit the bomb!";
    };

    auto decr = [](fruitInside a, fruitInside b) {
        if (a.type == 6 && b.type == 7)
            return a.type < b.type;
        else if (a.type == 8)
            return a.type < b.type;
        else
            return a.type > b.type;
    };

    auto drawFruitInside = [&](fruitInside fruit, int X, int Y) {
        switch (fruit.type) {
            case 1:
                s[X][Y] = 'o';
                break;
            case 2:
                for (int j = Y; j <= Y + 1; ++j)
                    s[X][j] = '+';
                break;
            case 3:
                for (int i = X; i <= X + 2; ++i)
                    if (i < n)
                        s[i][Y] = '(';
                    else
                        break;
                break;
            case 4:
                for (int i = X; i <= X + 1; ++i)
                    if (i < n)
                        for (int j = Y; j <= Y + 1; ++j)
                            s[i][j] = '@';
                    else
                        break;
                break;
            case 5:
                for (int i = X; i <= X + 2; ++i)
                    if (i < n)
                        for (int j = Y; j <= Y + 2; ++j) {
                            if (s[i][j] != '$')
                                s[i][j] = '^';
                        }
                    else
                        break;
                break;
            case 6:
                for (int i = X; i <= X + 2; ++i)
                    if (i < n)
                        for (int j = Y; j <= Y + 4; ++j) {
                            if (s[i][j] != '$')
                                s[i][j] = '{';
                        }
                    else
                        break;
                break;
            case 7:
                for (int i = X; i <= X + 1; ++i)
                    if (i < n)
                        for (int j = Y; j <= Y + 2; ++j)
                            s[i][j] = '$';
                    else
                        break;
                break;
            case 8:
                for (int i = X; i <= X + 4; ++i)
                    if (i < n)
                        s[i][Y] = '?';
                    else
                        break;
                break;
            case 9:
                for (int i = X; i <= X + 1; ++i)
                    if (i < n)
                        for (int j = Y; j <= Y + 3; ++j)
                            s[i][j] = '!';
                    else
                        break;
                break;
        }
    };

    auto cutFruit = [&](unsigned char type, int X, int Y, int l) {
        if (X >= n && Y >= m) {
            broken = true;
            return;
        }
        switch (type) {
            case '-':
                if (Y + l - 1 >= m)
                    broken = true;

                for (auto &droppedFruit : droppedFruits) {
                    for (int Xc = Y; Xc <= Y - 1 + l; ++Xc)
                        if ((droppedFruit.currentI <= X && droppedFruit.finalI >= X) &&
                            (droppedFruit.currentJ <= Xc && droppedFruit.finalJ >= Xc)) {
                            if (droppedFruit.type == 9) {
                                bombHit = true;
                                droppedFruits.clear();
                                break;
                            }
                            if (droppedFruit.type != 7) {
                                if (droppedFruit.type == 8)
                                    frozen = true;
                                droppedFruit.cut = true;
                            } else {
                                score += 100;
                                break;
                            }
                        }
                }

                break;
            case '|':
                if (X - l + 1 < 0)
                    broken = true;

                for (auto &droppedFruit : droppedFruits) {
                    for (int Xr = X; Xr >= X - l + 1; --Xr)
                        if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                            (droppedFruit.currentJ <= Y && droppedFruit.finalJ >= Y)) {
                            if (droppedFruit.type == 9) {
                                bombHit = true;
                                droppedFruits.clear();
                                break;
                            }
                            if (droppedFruit.type != 7) {
                                if (droppedFruit.type == 8)
                                    frozen = true;
                                droppedFruit.cut = true;
                            } else {
                                score += 100;
                                break;
                            }
                        }
                }
                break;
            case '/':
                if (Y - 1 + l >= n)
                    broken = true;

                for (auto &droppedFruit : droppedFruits) {
                    int Xr = X;
                    int Xc = Y;
                    while (Xc <= Y - 1 + l) {
                        if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                            (droppedFruit.currentJ <= Xc && droppedFruit.finalJ >= Xc)) {
                            if (droppedFruit.type == 9) {
                                bombHit = true;
                                droppedFruits.clear();
                                break;
                            }
                            if (droppedFruit.type != 7) {
                                if (droppedFruit.type == 8)
                                    frozen = true;
                                droppedFruit.cut = true;
                            } else {
                                score += 100;
                                break;
                            }
                        }
                        --Xr;
                        ++Xc;
                    }
                }
                break;
            case '\\':
                if (X - 1 - l >= n)
                    broken = true;

                for (auto &droppedFruit : droppedFruits) {
                    int Xr = X;
                    int Xc = Y;
                    while (Xr >= X - 1 - l) {
                        if ((droppedFruit.currentI <= Xr && droppedFruit.finalI >= Xr) &&
                            (droppedFruit.currentJ <= Xc && droppedFruit.finalJ >= Xc)) {
                            if (droppedFruit.type == 9) {
                                bombHit = true;
                                droppedFruits.clear();
                                break;
                            }
                            if (droppedFruit.type != 7) {
                                if (droppedFruit.type == 8)
                                    frozen = true;
                                droppedFruit.cut = true;
                            } else {
                                score += 100;
                                break;
                            }
                        }
                        --Xr;
                        --Xc;
                    }
                }
                break;
        }
    };

    if (round == 0) {
        s.resize(n, vector<unsigned char>(m, '.'));
        if (r <= n && c <= m) {
            droppedFruits.push_back(fruitInside());
            droppedFruits[round].setParameters(r - 1, c - 1, t);
            drawFruitInside(droppedFruits[round], r - 1, c - 1);
        }
    } else {
        cout << '\n' << '\n';
        if (!bombHit) {
            if (broken) {
                displayMatrix(false, false, true);
                ++round;
                return;
            }
            if (round >= 29) {
                if (missed < 3)
                    displayMatrix(false, true, false);
                ++round;
                return;
            }
            if (missed < 3) {
                if (frozen != 1) {
                    for (auto &droppedFruit : droppedFruits) {
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
                                for (
                                        int i = droppedFruit.currentI;
                                        i <= droppedFruit.currentI + 2; ++i) {
                                    if (i < n) {
                                        for (
                                                int j = droppedFruit.currentJ;
                                                j <= droppedFruit.currentJ + 2; ++j)
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
                                        for (
                                                int j = droppedFruit.currentJ;
                                                j <= droppedFruit.currentJ + 4; ++j)
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
                            case 8:
                                for (int i = droppedFruit.currentI; i <= droppedFruit.currentI + 4; ++i) {
                                    if (i < n)
                                        s[i][droppedFruit.currentJ] = '.';
                                    else
                                        break;
                                }
                                droppedFruit.currentI += droppedFruit.type;
                                droppedFruit.finalI += droppedFruit.type;
                                break;
                            case 9:
                                for (int i = droppedFruit.currentI; i <= droppedFruit.currentI + 1; ++i) {
                                    if (i < n)
                                        for (int j = droppedFruit.currentJ; j <= droppedFruit.currentJ + 3; ++j)
                                            s[i][j] = '.';
                                    else
                                        break;
                                }
                                droppedFruit.currentI += droppedFruit.type;
                                droppedFruit.finalI += droppedFruit.type;
                                break;
                        }
                    }
                } else
                    frozen = 0;
                auto it = droppedFruits.begin();
                while (it != droppedFruits.end()) {
                    if (it->currentI >= n) {
                        if (it->type != 7 && it->type != 9)
                            missed++;
                        it = droppedFruits.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            if (missed == 3) {
                if (!redrawn) {
                    for (auto fruit : droppedFruits)
                        drawFruitInside(fruit, fruit.currentI, fruit.currentJ);
                    redrawn = true;
                }
                displayMatrix(true, false, false);
                ++round;
                return;
            }

            if (t >= 48 && t <= 71) {
                if (r <= n && c <= m) {
                    int iter = droppedFruits.size();
                    droppedFruits.push_back(fruitInside());
                    droppedFruits[iter].setParameters(r - 1, c - 1, t);
                }
            } else {
                cutFruit(t, r - 1, c - 1, l);
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
            sort(droppedFruits.begin(), droppedFruits.end(), decr);
            for (auto &droppedFruit: droppedFruits)
                drawFruitInside(droppedFruit, droppedFruit.currentI, droppedFruit.currentJ);
        }
    }
    if (bombHit) {
        displayMatrix(false, false, false);
        ++round;
        return;
    } else {
        if (!broken)
            displayMatrix(false, false, false);
        else
            displayMatrix(false, false, true);
    }
    ++round;
}


int main(int argc, const char *argv[]) {
    if (argc == 1) {
        fout << "No arguments";
        return 1;
    }

    string inputFile = argv[1];
    ifstream in(inputFile.c_str(), ios::in);
    std::streambuf *cinbuf = std::cin.rdbuf();      // save stdin buffer
    std::cin.rdbuf(in.rdbuf());                     // redirect std::cin to input file (.in)
    if (!in.is_open()) {
        fout << "Cannot open input file";
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

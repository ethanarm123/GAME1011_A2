#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<cstdlib>
#include<conio.h>

using namespace std;

class Character {
public:
    int row, col;
    char symbol;
    Character(int row, int col, char symbol) {
        this->row = row;
        this->col = col;
        this->symbol = symbol;
    }
};

class Exit {
public:
    int row, col;
    char symbol;
    Exit(int row, int col, char symbol) {
        this->row = row;
        this->col = col;
        this->symbol = symbol;
    }
};

class MapLevel {
private:
    int** mapData;
    int maxRows, maxCols;
    Character* player;
    Exit* exit;
public:

    MapLevel(string filename) {
        ifstream input;
        input.open(filename.c_str());
        if (input.is_open()) {
            string line;
            getline(input, line);
            stringstream ss(line);
            ss >> maxRows;
            ss >> maxCols;
            //create the 2 dimensional array of size maxRows and maxCols
            mapData = new int* [maxRows];
            for (int x = 0; x < maxRows; x++) {
                mapData[x] = new int[maxCols];
            }
            // load the array
            for (int r = 0; r < maxRows; r++) {
                getline(input, line);
                stringstream ss(line);
                for (int c = 0; c < maxCols; c++) {
                    ss >> mapData[r][c];
                }
            }

            input.close();
        }

    }

    void addPlayer(Character* p) {
        this->player = p;
    }

    void addExit(Exit* e) {
        this->exit = e;
    }

    string printMap()const {
        stringstream ss;
        char wallSymbol = (char)176;
        for (int r = 0; r < maxCols + 2; r++) ss << wallSymbol;
        ss << "\n";
        for (int r = 0; r < maxRows; r++) {
            ss << wallSymbol;
            for (int c = 0; c < maxCols; c++) {
                if (r == player->row && c == player->col) {
                    ss << player->symbol;
                }
                if (r == exit->row && c == exit->col) {
                    ss << exit->symbol;
                }
                else {
                    if (mapData[r][c] == 0 || mapData[r][c] == 2) {
                        ss << "  ";
                    }
                    if (mapData[r][c] == 1) {
                        ss << wallSymbol;
                    }
                    if (mapData[r][c] == 3) {
                        ss << "*";
                    }
                }
            }
            ss << wallSymbol << "\n";
        }
        for (int r = 0; r < maxCols + 2; r++) ss << wallSymbol;
        ss << "\n";
        return ss.str();
    }

    string printMapSquare()const {
        stringstream ss;
        char wallSymbol = (char)176;
        for (int r = 0; r < maxCols * 2 + 2; r++) ss << wallSymbol;
        ss << "\n";
        for (int r = 0; r < maxRows; r++) {
            ss << wallSymbol;
            for (int c = 0; c < maxCols; c++) {
                if (r == player->row && c == player->col) {
                    ss << player->symbol;
                }
                if (r == exit->row && c == exit->col) {
                    ss << exit->symbol << " ";
                }
                else {
                    if (mapData[r][c] == 0 || mapData[r][c] == 2) {
                        ss << "  ";
                    }
                    if (mapData[r][c] == 1) {
                        ss << wallSymbol << wallSymbol;
                    }
                    if (mapData[r][c] == 3) {
                        ss << "**";
                    }
                }
            }
            ss << wallSymbol << "\n";
        }
        for (int r = 0; r < maxCols * 2 + 2; r++) ss << wallSymbol;
        ss << "\n";
        return ss.str();
    }

    void clearUpMap() {
        for (int r = 0; r < maxRows; r++) {
            for (int c = 0; c < maxCols; c++) {
                if (mapData[r][c] == 2 || mapData[r][c] == 3) {
                    mapData[r][c] = 0;
                }
            }
        }
    }

    bool isValid(int row, int col) {
        if (mapData[row][col] == 1 || row < 0 || row >= maxRows || col < 0 || col >= maxCols) {
            return false;
        }
        return true;
    }
};

int main() {
    char dir;
    Character* p1 = new Character(2, 1, 'P');
    Exit* e1 = new Exit(10, 12, 'O');
    MapLevel ml("map1.txt");
    ml.addPlayer(p1);
    ml.addExit(e1);
    Character* pp = p1;
    cout << ml.printMapSquare();
    cout << "Please enter a direction w,a,s,d or E to exit:";
    dir = _getch();
    while (dir != 'E') {
        if (dir == 'w' || dir == 'W') {
            if (ml.isValid(pp->row - 1, pp->col)) {
                pp->row = pp->row - 1;
            }
        }

        if (dir == 's' || dir == 'S') {
            if (ml.isValid(pp->row + 1, pp->col)) {
                pp->row = pp->row + 1;
            }
        }

        if (dir == 'd' || dir == 'D') {
            if (ml.isValid(pp->row, pp->col + 1)) {
                pp->col = pp->col + 1;
            }
        }

        if (dir == 'a' || dir == 'A') {
            if (ml.isValid(pp->row, pp->col - 1)) {
                pp->col = pp->col - 1;
            }
        }
        system("cls");
        ml.clearUpMap();
        cout << ml.printMapSquare();
        cout << "Please enter a direction w,a,s,d or E to exit:";
        dir = _getch();
    }

    return 0;
}
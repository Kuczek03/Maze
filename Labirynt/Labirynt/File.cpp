#include "File.h"

// Funkcja generuj�ca plansz� z pliku
vector<vector<char>> File::loadBoardFromFile(const string& filename, int& m, int& n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie mo�na otworzy� pliku " << filename << endl;
        exit(EXIT_FAILURE);
    }

    file >> m >> n;
    vector<vector<char>> board(m, vector<char>(n));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> board[i][j];
        }
    }

    file.close();
    return board;
}

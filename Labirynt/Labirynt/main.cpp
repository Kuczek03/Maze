#include "asstes.h"
#include "Board.h"
#include "File.h"

int main() {
    setlocale(LC_CTYPE, "Polish");
    int m, n;
    string filename;
    cout << "Podaj nazw� pliku z plansz�: ";
    cin >> filename;

    Board brd;
    File fl;
    // Wczytaj plansz� z pliku
    vector<vector<char>> board = fl.loadBoardFromFile(filename, m, n);

    // Wypisz plansz�
    cout << "Plansza:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    // Rozwi�� problem labiryntu
    vector<string> path = brd.findPath(board);

    ofstream outputFile("odp.txt");
    if (!outputFile.is_open()) {
        cerr << "Nie mo�na utworzy� pliku odpowiedz.txt" << endl;
        return EXIT_FAILURE;
    }

    if (path.empty()) {
        outputFile << "nie" << endl;
    }
    else {
        outputFile << "tak  ";
        for (const string& direction : path) {
            outputFile << direction << " ";
        }
        outputFile << endl;
    }

    outputFile.close();

    cout << "Wynik zapisano w pliku odpowiedz.txt." << endl;

    return 0;
}
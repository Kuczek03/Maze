#include "File.h"

// Generating board form the file
vector<vector<char>> File::loadBoardFromFile(const string& filename, int& m, int& n) 
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file " << filename <<"." << endl;
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

int File::saveSolution(const string& outname, vector<string> path)
{
    ofstream outputFile(outname);
    if (!outputFile.is_open()) {
        cerr << "Cannot create file " << outname << "." << endl;
        return EXIT_FAILURE;
    }

    if (path.empty()) {
        outputFile << "There is no solution." << endl;
    }
    else {
        outputFile << "Here is the solution:  ";
        for (const string& direction : path) {
            outputFile << direction << endl;
        }
        outputFile << endl;
    }

    outputFile.close();

    cout << "Solution saved in file " << outname << "." << endl;

    return 1;
}

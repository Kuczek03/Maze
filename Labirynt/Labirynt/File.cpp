#include "File.h"
#include <filesystem>

// Generating board form the file
vector<vector<char>> File::loadBoardFromFile(const string& filename, int& r, int& c) 
{
    ifstream file(filename);
    if (!file.is_open()) {
        
        cout << "Cannot open file " << filename <<"." << endl;
        //exit(EXIT_FAILURE);
    }

    file >> r >> c;
    vector<vector<char>> board(r, vector<char>(c));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
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
        outputFile << "Here is the solution:\n";
        
            for (const string& direction : path) {
                outputFile << direction << endl;
            }
        
        outputFile << endl;
    }

    outputFile.close();

    cout << "Solution saved in file " << outname << "." << endl;

    return 1;
}

/*int File::saveAllSolution(const string& outname, vector<vector<string>> paths)
{
    ofstream outputFile(outname);
    if (!outputFile.is_open()) {
        cerr << "Cannot create file " << outname << "." << endl;
        return EXIT_FAILURE;
    }

    if (paths.empty()) {
        outputFile << "There is no solution." << endl;
    }
    else {
        outputFile << "Here is the solution:\n";

        for (const auto& path : paths) {
            for (const string& direction : path) {
                outputFile << direction << endl;
            }
            outputFile << "----" << endl;  // Separate paths with "----"
        }
    }

    outputFile << endl;
    outputFile.close();

    cout << "Solution saved in file " << outname << "." << endl;

    return 1;
}*/

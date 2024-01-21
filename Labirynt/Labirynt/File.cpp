#include "File.h"

// Generating board form the file
vector<vector<char>> File::loadBoardFromFile(const string& filename, int& r, int& c) 
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file " << filename <<"." << endl;
        exit(EXIT_FAILURE);
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

void File::readAndUpdatePathFromFile(const string& filePath, vector<vector<char>> board)
{
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string direction;
    int x = 0, y = 0;  // Starting position

    while (file >> direction)
    {
        // Convert the direction to lowercase
        std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);

        // Check if the movement is valid and not affecting 'S' or 'M'
        if (direction == "Up" && x > 0 && board[x - 1][y] == 'B')
        {
            // Override 'B' with 'b'
            board[x - 1][y] = 'b';
            x--;
        }
        else if (direction == "Down" && x < board.size() - 1 && board[x + 1][y] == 'B')
        {
            // Override 'B' with 'b'
            board[x + 1][y] = 'b';
            x++;
        }
        else if (direction == "L" && y > 0 && board[x][y - 1] == 'B')
        {
            // Override 'B' with 'b'
            board[x][y - 1] = 'b';
            y--;
        }
        else if (direction == "Rigth" && y < board[0].size() - 1 && board[x][y + 1] == 'B')
        {
            // Override 'B' with 'b'
            board[x][y + 1] = 'b';
            y++;
        }
        // Ignore invalid directions
    }

    file.close();
}

int File::saveAllSolution(const string& outname, vector<vector<string>> paths)
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
}
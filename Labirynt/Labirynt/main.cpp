#include "asstes.h"
#include "Board.h"
#include "Window.h"
using namespace std;
int main() 
{
    Window window;
    Board board;
    int choice;
    int r, c;
    double wallProbability;
    string filename, outname = "odp.txt";

    cout << "1. Choose maze from the file. \n";
    cout << "2. Choose random generated maze . \n";
    cout << "3. Choose random generated maze with probability for the walls. \n";
    cin >> choice;

    if (choice == 1){
        cout << "Read board from file: ";
        cin >> filename;
        //cout << "Save in file: ";
        //cin >> outname;

        window.mazeFromFile(filename, outname);
    }/*else if (choice == 2) {

        cout << "Insert number of rows and columns (r c): ";
        cin >> r >> c;

        vector<vector<char>> maze = board.generateRandomMaze(r, c);

        //Wypisz labirynt
        cout << "Labirynt:" << endl;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }*/else if(choice == 2){  
        cout << "Insert number of rows and columns (r c): ";
        cin >> r >> c;
        
        window.drawMaze(outname, choice, r, c);
    }
    else if (choice == 3) {
        cout << "Insert number of rows and columns (r c): ";
        cin >> r >> c;
        cout << "Insert probability of walls: ";
        cin >> wallProbability;

        // Validate wall probability
        if (wallProbability < 0.0 || wallProbability > 1.0) {
            cerr << "Error: Wall probability must be between 0 and 1." << endl;
            return 1; // Exit with an error code
        }

        // Generate and display the maze
        board.generateMazeWithProbability(r, c, wallProbability);
    }
    return 0;
}
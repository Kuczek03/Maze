#include "asstes.h"
#include "Board.h"
#include "Window.h"
using namespace std;
int main() 
{
    Window window;
    Board board;
    int choice;
    string filename, outname = "odp.txt";

    cout << "1. Choose maze from the file. \n";
    cout << "2. Choose random generated maze. \n";
    cin >> choice;
    switch (choice)
    {
    case 1:
       
        cout << "Read board from file: ";
        cin >> filename;
        //cout << "Save in file: ";
        //cin >> outname;

        window.mazeFromFile(filename, outname);
        break;
    case 2:
        int m, n;
        cout << "Podaj wymiary labiryntu (m n): ";
        cin >> m >> n;

        vector<vector<char>> maze = board.generateRandomMaze(m, n);

        // Wypisz labirynt
        cout << "Labirynt:" << endl;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
        break;
    }
   
   
    return 0;
}
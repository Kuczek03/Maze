#include "asstes.h"
#include "Board.h"
#include "Window.h"
using namespace std;
int main() 
{
    Window window;
    Board board;
    int choice;
    int m, n, o, p;
    string filename, outname = "odp.txt";

    cout << "1. Choose maze from the file. \n";
    cout << "2. Choose random generated maze method 1. \n";
    cout << "3. Choose random generated maze method 2. \n";
    cin >> choice;

    if (choice == 1){
        cout << "Read board from file: ";
        cin >> filename;
        //cout << "Save in file: ";
        //cin >> outname;

        window.mazeFromFile(filename, outname);
    }else if (choice == 2){

        cout << "Insert number of rows and columns (m n): ";
        cin >> m >> n;

        vector<vector<char>> maze = board.generateRandomMaze(m, n);

        //Wypisz labirynt
        cout << "Labirynt:" << endl;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    }else if(choice ==3){  
        cout << "Insert number of rows and columns (o p): ";
        cin >> o >> p;
        board.generateMaze(o, p);   
    }
    return 0;
}
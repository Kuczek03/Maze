#include "asstes.h"
#include "Board.h"
#include "Window.h"
using namespace std;
int main() 
{
    Window window;
    /*Board board;
    int choice=4;
    int r, c;
    double wallProbability;
    string filename, outname = "odp.txt";

    cout << "1. Choose maze from the file. \n";
    cout << "2. Choose random generated maze . \n";
    cout << "3. Choose random generated maze with probability for the walls. \n";
    //cin >> choice;

    if (choice == 1){
        cout << "Read board from file: ";
        cin >> filename;
        //cout << "Save in file: ";
        //cin >> outname;

        window.mazeFromFile(filename, outname);

    }else if(choice == 2){  
        cout << "Insert number of rows and columns (r c): ";
        cin >> r >> c;
        
        //window.drawRandomMaze("outname", choice, r, c);
    }
    else if (choice == 3) {
        cout << "Insert number of rows and columns (r c): ";
        cin >> r >> c;
        do {
            cout << "Insert probability of walls: ";
            cin >> wallProbability;

            // Validate wall probability
            if (wallProbability < 0.0 || wallProbability > 1.0) {
                cerr << "Error: Wall probability must be between 0 and 1." << endl;
            }
        } while (wallProbability < 0.0 || wallProbability > 1.0);
        // Generate and display the maze        
        window.drawRandomMaze(outname, r, c, wallProbability);
    }
    else if (choice == 4) {}*/
    
       window.menu();
    
    return 0;
}
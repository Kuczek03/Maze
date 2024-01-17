#include "asstes.h"
#include "Window.h"
using namespace std;
int main() {
   
    Window window;
    
    string filename, outname = "odp.txt";
    cout << "Read board from file: ";
    cin >> filename;
    //cout << "Save in file: ";
    //cin >> outname;
   
    window.windowLoop(filename, outname);
   
    return 0;
}
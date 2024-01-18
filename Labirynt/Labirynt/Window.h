#include "asstes.h"
#include "Board.h"
#include "File.h"
class Window
{
private:
	Board board;
	File file;
	int m, n;
public:
	void mazeFromFile(const string& filename, const string& outname);
	void randomGeneratedMaze(const string& filename, const string& outname);
};


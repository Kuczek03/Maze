#include "asstes.h"
#include "Board.h"
#include "File.h"
class Window
{
private:
	Board board;
	File file;
	int r, c;
	const int tileSize = 20;

	sf::RenderWindow* window= new sf::RenderWindow;
	bool isStartModified = true;
public:
	void mazeFromFile(const string& filename, const string& outname);
	//void randomGeneratedMaze(const string& filename, const string& outname);

	void drawMaze(const string& outname, int choice, int r, int c);
};


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
	void drawRandomMaze(const string& outname, int r, int c, double wallProbability);	
	void menu();
	int noPathBox();

};


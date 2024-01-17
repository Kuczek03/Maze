#include "asstes.h"
#include <fcntl.h>
class Board
{
private:
	// Structure representing coordinates on board
	struct Point {
		int x, y;

		Point(int x, int y) : x(x), y(y) {}
	};
	vector<string> path;
	queue<tuple<int, int, vector<string>>> queue; // BFS queue
	
	const int tileSize = 40;
public:
	vector<string> BFS(vector<vector<char>>& board);

	bool isValid(int x, int y, int m, int n);
	void drawBoard(sf::RenderWindow& window, const vector<vector<char>>& board, const vector<string>& path);
};


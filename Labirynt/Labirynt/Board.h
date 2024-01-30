#pragma once
#include "asstes.h"
class Board
{
private:
/*struct Point {
		int x, y;

		Point(int x, int y) : x(x), y(y) {}
	};*/
	

	struct Node{
		int x, y;
		int g;
		int h;
		Node* parent;  

		Node(int x, int y, int g, int h, Node* parent): x(x), y(y), g(g), h(h), parent(parent) {}

		int getF() const { return g + h; }
	};

	const int tileSize = 20;	
	int calculateManhattanDistance(int x1, int y1, int x2, int y2){ return abs(x1 - x2) + abs(y1 - y2); }				
	bool isBoardModified = true;
	
	vector<string> lastPath, pathh;	
public:		
	bool isValid(int x, int y, int r, int c){return x >= 0 && x < r && y >= 0 && y < c;}
	void drawBoard(sf::RenderWindow& window,  vector<vector<char>>& board, vector<string>& path, int r, int c);
	void updateBoardWithMouseClick(sf::Vector2i mousePos, vector<vector<char>>& maze);
	void updateAllBtoB(vector<vector<char>>& maze, int r, int c);
	vector<vector<char>> setPathChar(vector<vector<char>>& board, vector<string>& path, int r, int c);

	void setBoardModified() { isBoardModified = true; }
	bool hasBoardModified() const {	return isBoardModified;}	
	void resetBoardModified() { isBoardModified = false; }

	vector<vector<char>> generateMaze(int r, int c);
	vector<vector<char>> generateMazeWithProbability(int r, int c, double wallProbability);

	void cellChange(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addStartPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addEndPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);	
	
	vector<string> AStar(vector<vector<char>>& board);
	};


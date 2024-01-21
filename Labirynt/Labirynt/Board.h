#pragma once
#include "asstes.h"
#include <fcntl.h>
#include <cmath>
class Board
{
private:
	// Structure representing coordinates on board
	struct Point {
		int x, y;

		Point(int x, int y) : x(x), y(y) {}
	};

	struct Node{
		int x, y;
		int g;  // cost from start
		int h;  // heuristic (Manhattan distance to goal)
		Node* parent;  // pointer to the parent node

		Node(int x, int y, int g, int h, Node* parent)
			: x(x), y(y), g(g), h(h), parent(parent) {}

		// A* uses f = g + h to prioritize nodes
		int getF() const
		{
			return g + h;
		}
	};

	
	queue<tuple<int, int, vector<string>>> queue; // BFS queue
	
	const int tileSize = 40;
	
	int calculateManhattanDistance(int x1, int y1, int x2, int y2)
	{
		return abs(x1 - x2) + abs(y1 - y2);
	}

	
	bool isBoardModified = true;
	
	vector<string> lastPath, pathh;

	

public:
	vector<vector<char>> brd;
	vector<string> BFS(vector<vector<char>>& board);

	bool isValid(int x, int y, int r, int c);
	void drawBoard(sf::RenderWindow& window,  vector<vector<char>>& board,  
					vector<string>& path, int r, int c);
	void updateBoardWithMouseClick(sf::Vector2i mousePos, vector<vector<char>>& maze);

	// Function to set the modification status to true
	void setBoardModified() { isBoardModified = true; }

	// Function to check if the board has been modified
	vector<vector<char>> setPathChar(vector<vector<char>>& board, vector<string>& path);
	bool hasBoardModified() const {	return isBoardModified;}
	void updateAllBtoB(vector<vector<char>>& maze, int r, int c);
	
	
	vector<vector<char>> generateMaze(int r, int c);
	vector<vector<char>> generateMazeWithProbability(int r, int c, double wallProbability);

	void cellChange(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addStartPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addEndPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	
	vector<string> AStar(vector<vector<char>>& board);

	// Function to reset the board modification status
	void resetBoardModified(){isBoardModified = false;}		

	vector<vector<string>> AStarWithAllPaths(vector<vector<char>>& board);
	int updateStartAndEndPoints(vector<vector<char>>& board);
	vector<vector<string>> getShortestPaths(vector<vector<char>>& board, int r, int c);
	void drawBoardAllPaths(sf::RenderWindow& window, vector<vector<char>>& board, const vector<string>& path, const vector<vector<string>>& allPaths, int r, int c);
};


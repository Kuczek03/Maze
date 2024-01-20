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

	vector<string> path;
	queue<tuple<int, int, vector<string>>> queue; // BFS queue
	
	const int tileSize = 40;
	
	int calculateManhattanDistance(int x1, int y1, int x2, int y2)
	{
		return abs(x1 - x2) + abs(y1 - y2);
	}

	bool boardModified;

	vector<string> lastShortestPath; // Variable to store the last shortest path

	void updateBoardInternal(sf::RenderWindow& window, const vector<string>& path, vector<vector<char>>& board);
public:
	vector<string> BFS(vector<vector<char>>& board);

	bool isValid(int x, int y, int r, int c);
	void drawBoard(sf::RenderWindow& window, const vector<vector<char>>& board, const vector<string>& path, int r, int c);

	vector<vector<char>> generateMaze(int r, int c);
	vector<vector<char>> generateMazeWithProbability(int r, int c, double wallProbability);

	void cellChange(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addStartPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void addEndPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze);
	void floydWarshall(vector<vector<char>>& maze, int r, int c);
	void visualizeShortestPath(sf::RenderWindow& window, const vector<vector<char>>& maze, int r, int c);

	vector<string> AStar(vector<vector<char>>& board);

	// Upadating the board
	Board() : boardModified(false) {}
	// Function to get the status of board modification
	bool isBoardModified() const{return boardModified;}
	// Function to reset the board modification status
	void resetBoardModified(){boardModified = false;}
	void updateBoard(sf::RenderWindow& window, const vector<string>& path, vector<vector<char>>& board);
	
	// Function to get the last shortest path
	const vector<string>& getLastShortestPath() const
	{
		return lastShortestPath;
	}

	// Function to update the board and store the current path as the last path
	void updateBoardd(sf::RenderWindow& window, const vector<string>& path, vector<vector<char>>& board)
	{
		// Update the board and set the last path
		lastShortestPath = path;
		updateBoardInternal(window, path, board);
	}
	};


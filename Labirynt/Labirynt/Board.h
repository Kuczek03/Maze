#pragma once
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

	bool isValid(int x, int y, int r, int c);
	void drawBoard(sf::RenderWindow& window, const vector<vector<char>>& board, const vector<string>& path);

	//vector<vector<char>> generateRandomMaze(int r, int c);
	//bool isAvailable(const vector<vector<char>>& maze, int x, int y, int r, int c);
	//int countAvailableNeighbors(const vector<vector<char>>& maze, int x, int y);
	//void generate(vector<vector<char>>& maze, int x, int y, mt19937& gen);

	vector<vector<char>> generateMaze(int r, int c);
	vector<vector<char>> generateMazeWithProbability(int r, int c, double wallProbability);

	void toggleCellFromFile(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& mazeFromFile);
};


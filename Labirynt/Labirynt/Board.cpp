#include "Board.h"

void Board::drawBoard(sf::RenderWindow& window, vector<vector<char>>& board, vector<string>& path, int r, int c)
{    
	setPathChar(board,path,r,c);
	sf::Color
		field(149,183,222),
		wall(25,95,176),
		start(70,189,102),
		end(184,35,35),
		pathC(237,226,109);


	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setOutlineThickness(2);
			tile.setOutlineColor(sf::Color::Black);
			tile.setPosition(j * tileSize, i * tileSize);

			if (board[i][j] == 'B') {
				tile.setFillColor(field);
			}
			else if (board[i][j] == 'C') {
				tile.setFillColor(wall);
			}
			else if (board[i][j] == 'S') {
				tile.setFillColor(start);
			}
			else if (board[i][j] == 'M') {
				tile.setFillColor(end);
			}
			else if (board[i][j] == 'b') {
				tile.setFillColor(pathC);
			}                            
			window.draw(tile);
		}
	}    
}

void Board::updateBoardWithMouseClick(sf::Vector2i mousePos, vector<vector<char>>& maze) {
	int row = mousePos.y / tileSize;
	int col = mousePos.x / tileSize;

	if (row >= 0 && row < maze.size() && col >= 0 && col < maze[0].size()) {
		if (maze[row][col] == 'b') {
			maze[row][col] = 'B';
			setBoardModified(); 
		}
	}
	
}

vector<vector<char>> Board::setPathChar(vector<vector<char>>& board, vector<string>& path, int r, int c)
{
	int x = 0, y = 0;
	bool isStartChanged = false;
	bool isEndChanged = false;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (board[i][j] == 'S' && std::find(lastPath.begin(), lastPath.end(), "S") == lastPath.end()) {
				isStartChanged = true;
			}
		}
	}
	if (isStartChanged || isEndChanged) {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (board[i][j] == 'S') {
					x = j;
					y = i;
				}
		path = AStar(board);
	}
	
	for (const string& direction : path) {
		if (direction == "Up") {
			y--;
		}
		else if (direction == "Down") {
			y++;
		}
		else if (direction == "Left") {
			x--;
		}
		else if (direction == "Right") {
			x++;
		}
		else {
			//cerr << "Error. Unknown direction on path" << endl;
			//exit(EXIT_FAILURE);
			
		}
		if (board[y][x] == 'B') {
			board[y][x] = 'b';
		}
		
	}
	
	return board;
	
}


void Board::updateAllBtoB(vector<vector<char>>& maze, int r, int c)
{
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (maze[i][j] == 'b') {
				maze[i][j] = 'B';
			}
		}
	}
	isBoardModified = false;
}

vector<vector<char>> Board::generateMaze(int r, int c) {
	
	srand(time(NULL));

	vector<vector<char>> maze(r, vector<char>(c));

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			maze[i][j] = 'C';
		}
	}
	for (int i = 1; i < r - 1; ++i) {
		for (int j = 1; j < c - 1; ++j) {
			if (rand() % 2 == 0) {
				maze[i][j] = 'B';
			}
		}
	}
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	return maze;
}

vector<vector<char>> Board::generateMazeWithProbability(int r, int c, double wallProbability)
{
	srand(time(NULL)); 

	vector<vector<char>> maze(r, vector<char>(c));

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			double randomValue = static_cast<double>(rand()) / RAND_MAX;
			maze[i][j] = (randomValue < wallProbability) ? 'C' : 'B';
		}
	}
	/*for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << maze[i][j];
		}
		cout << endl;
	}*/
	
	return maze;
}

void Board::cellChange(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze)
{
	int row = mousePos.y / tileSize;
	int col = mousePos.x / tileSize;

	if (row >= 0 && row < r && col >= 0 && col < c) {
		if (maze[row][col] != 'S' && maze[row][col] != 'M') {
			if (maze[row][col] == 'B') {
				maze[row][col] = 'C';
			}
			else {
				maze[row][col] = 'B';
			}
		}
		setBoardModified();
	}
}

void Board::addStartPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze) 
{
	int row = mousePos.y / tileSize;
	int col = mousePos.x / tileSize;

	if (row >= 0 && row < r && col >= 0 && col < c) {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (maze[i][j] == 'S') {
					maze[i][j] = 'B';
				}
			}
		}
		if (maze[row][col] != 'M')
			maze[row][col] = 'S';
		if(maze[row][col]=='b'){
			maze[row][col] = 'S';
		}
		setBoardModified();
	}
}

void Board::addEndPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze)
{
	int row = mousePos.y / tileSize;
	int col = mousePos.x / tileSize;

	if (row >= 0 && row < r && col >= 0 && col < c) {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (maze[i][j] == 'M') {
					maze[i][j] = 'B';
				}
			}
		}
		if (maze[row][col] != 'S')
			maze[row][col] = 'M';
		setBoardModified();
	}
}

vector<string> Board::AStar(vector<vector<char>>& board)
{
	int r = board.size();
	int c = board[0].size();

	auto calculateManhattanDistance = [](int x1, int y1, int x2, int y2) {
		return abs(x1 - x2) + abs(y1 - y2);
	};
	auto comparator = [](Node* a, Node* b) {
		return a->getF() > b->getF();
	};

	priority_queue<Node*, vector<Node*>, decltype(comparator)> pq(comparator);
	vector<vector<int>> costs(r, vector<int>(c, INT_MAX));

	int startX, startY, endX, endY;
	bool hasStart = false;
	bool hasEnd = false;

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (board[i][j] == 'S')
			{
				startX = i;
				startY = j;
				hasStart = true;
			}
			else if (board[i][j] == 'M')
			{
				endX = i;
				endY = j;
				hasEnd = true;
			}
		}
	}
	if (!hasStart)
	{
		board[0][0] = 'S';
		startX = 0;
		startY = 0;
	}
	if (!hasEnd)
	{
		board[r - 1][c - 1] = 'M';
		endX = r - 1;
		endY = c - 1;
	}		
	Node* startNode = new Node(startX, startY, 0, calculateManhattanDistance(startX, startY, endX, endY), nullptr);
	pq.push(startNode);
	costs[startX][startY] = 0;

	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };
	string directions[] = { "Up", "Down", "Left", "Right" };

	while (!pq.empty())
	{
		Node* current = pq.top();
		pq.pop();
		if (current->x == endX && current->y == endY)
		{
			vector<string> path;
			while (current->parent != nullptr)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (current->parent->x + dx[i] == current->x && current->parent->y + dy[i] == current->y)
					{
						path.push_back(directions[i]);
						break;
					}
				}
				current = current->parent;
			}
			reverse(path.begin(), path.end());
			return path;
		}
		for (int i = 0; i < 4; ++i)
		{
			int nextX = current->x + dx[i];
			int nextY = current->y + dy[i];

			if (isValid(nextX, nextY, r, c) &&
				board[nextX][nextY] != 'C' &&  
				costs[nextX][nextY] > current->g + 1) 
			{
				costs[nextX][nextY] = current->g + 1;
				Node* nextNode = new Node(nextX, nextY, current->g + 1, calculateManhattanDistance(nextX, nextY, endX, endY), current);
				pq.push(nextNode);
			}
		}
	}
	return {};
}

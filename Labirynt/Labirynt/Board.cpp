#include "Board.h"

/*vector<string> Board::BFS(vector<vector<char>>& board) 
{
    
    int r = board.size(); // Number of rows
    int c = board[0].size(); // Number od columns
    vector<vector<bool>> visited(r, vector<bool>(c, false)); // Array of visited fields

    // First row of queue is starting points
    for (int i = 0; i < c; ++i) {
        if (board[0][i] == 'B') {
            queue.push({ 0, i, {to_string(i + 1)} });
            visited[0][i] = true;
        }
    }

    // Use BFS
    while (!queue.empty()) {
        int x, y;
        
        tie(x, y, pathh) = queue.front();
        queue.pop();

        if (x == r - 1) {
            // If we at last row we return path
            return pathh;
        }

        // Possible moves: up, down, left, rigth
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        string directions[] = { "Up", "Down", "Left", "Rigth" };

        for (int i = 0; i < 4; ++i) {
            int X = x + dx[i];
            int Y = y + dy[i];

            if (isValid(X, Y, r, c) && !visited[X][Y] && board[X][Y] == 'B') {
                visited[X][Y] = true;
                vector<string> newPath = pathh;
                newPath.push_back(directions[i]);
                queue.push({ X, Y, newPath });
            }
        }
    }

    // If there is no path found, return empty list.
    return {};
}*/

void Board::drawBoard(sf::RenderWindow& window, vector<vector<char>>& board, vector<string>& path, int r, int c)
{    
    setPathChar(board,path,r,c);

    // Draw the maze
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Black);
            tile.setPosition(j * tileSize, i * tileSize);
            // Set color based on board content
            if (board[i][j] == 'B') {
                tile.setFillColor(sf::Color::White);
            }
            else if (board[i][j] == 'C') {
                tile.setFillColor(sf::Color::Black);
            }
            else if (board[i][j] == 'S') {
                tile.setFillColor(sf::Color::Green);
            }
            else if (board[i][j] == 'M') {
                tile.setFillColor(sf::Color::Red);
            }
            else if (board[i][j] == 'b') {
                tile.setFillColor(sf::Color::Blue);
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
            setBoardModified();  // Set the modification status to true
        }
    }
    
}

vector<vector<char>> Board::setPathChar(vector<vector<char>>& board, vector<string>& path, int r, int c)
{
    // Check if 'S' or 'M' has changed
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
    // If 'S' has changed, update the path
    if (isStartChanged || isEndChanged) {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (board[i][j] == 'S') {
                    x = j;
                    y = i;
                }
        path = AStar(board);
    }
    // Draw the current path by changing 'B' to 'b'
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
            cerr << "Error. Unknown direction on path" << endl;
            exit(EXIT_FAILURE);
        }

        // Change 'B' to 'b' in the maze
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
    isBoardModified = false;  // Reset the modification status
}

vector<vector<char>> Board::generateMaze(int r, int c) {
    
    srand(time(NULL)); // Seed for random number generator

    // Create a 2D array to represent the maze
    vector<vector<char>> maze(r, vector<char>(c));
    // Fill the maze with walls ("C")
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            maze[i][j] = 'C';
        }
    }
    // Generate random floors ("B")
    for (int i = 1; i < r - 1; ++i) {
        for (int j = 1; j < c - 1; ++j) {
            // Randomly decide whether to make the cell a floor
            if (rand() % 2 == 0) {
                maze[i][j] = 'B';
            }
        }
    }
    // Print the generated maze
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
    srand(time(NULL)); // Seed for random number generator

    // Create a 2D array to represent the maze
    vector<vector<char>> maze(r, vector<char>(c));

    // Fill the maze with walls ("C") based on user-defined probability
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            maze[i][j] = (randomValue < wallProbability) ? 'C' : 'B';
        }
    }
    // Print the generated maze
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
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

    // Helper function to calculate Manhattan distance
    auto calculateManhattanDistance = [](int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    };

    // Priority queue to store nodes with the lowest f value on top
    auto comparator = [](Node* a, Node* b) {
        return a->getF() > b->getF();
    };

    priority_queue<Node*, vector<Node*>, decltype(comparator)> pq(comparator);

    // Create a 2D array to store costs (g values)
    vector<vector<int>> costs(r, vector<int>(c, INT_MAX));

    // Find the start and end points
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
    // If there is no 'S', create it in the first row and first column
    if (!hasStart)
    {
        board[0][0] = 'S';
        startX = 0;
        startY = 0;
    }

    // If there is no 'M', create it in the last row and last column
    if (!hasEnd)
    {
        board[r - 1][c - 1] = 'M';
        endX = r - 1;
        endY = c - 1;
    }
         
    // Initialize the start node and add it to the priority queue
    Node* startNode = new Node(startX, startY, 0, calculateManhattanDistance(startX, startY, endX, endY), nullptr);
    pq.push(startNode);
    costs[startX][startY] = 0;

    // Possible moves: up, down, left, right
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    string directions[] = { "Up", "Down", "Left", "Right" };

    while (!pq.empty())
    {
        Node* current = pq.top();
        pq.pop();

        // Goal check
        if (current->x == endX && current->y == endY)
        {
            // Reconstruct the path
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
            // Reverse the path to get it from start to end
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (int i = 0; i < 4; ++i)
        {
            int nextX = current->x + dx[i];
            int nextY = current->y + dy[i];

            if (isValid(nextX, nextY, r, c) &&
                board[nextX][nextY] != 'C' &&  // Cannot go through walls
                costs[nextX][nextY] > current->g + 1)  // New path is cheaper
            {
                costs[nextX][nextY] = current->g + 1;
                Node* nextNode = new Node(nextX, nextY, current->g + 1, calculateManhattanDistance(nextX, nextY, endX, endY), current);
                pq.push(nextNode);
            }
        }
    }

    // No path found
    return {};
}


vector<vector<string>> Board::findAllPaths(vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<tuple<int, int, vector<string>>> q;

    // Initialize the queue
    for (int i = 0; i < n; ++i) {
        if (board[0][i] == 'B') {
            q.push({0, i, {to_string(i + 1)}});
            visited[0][i] = true;
        }
    }

    vector<vector<string>> shortestPaths;
    int minPathLength = INT_MAX;

    while (!q.empty()) {
        int x, y;
        vector<string> path;
        tie(x, y, path) = q.front();
        q.pop();

        // Check if reached the end of the maze
        if (x == m - 1) {
            if (path.size() < minPathLength) {
                minPathLength = path.size();
                shortestPaths.clear();
            }
            if (path.size() == minPathLength) {
                shortestPaths.push_back(path);
            }
            continue;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        string directions[] = {"Up", "Down", "Left", "Right"};

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY, m, n) && !visited[newX][newY] &&
                (board[newX][newY] == 'B' || board[newX][newY] == 'M')) {
                visited[newX][newY] = true;
                vector<string> newPath = path;
                newPath.push_back(directions[i]);
                q.push({newX, newY, newPath});
            }
        }
    }

    return shortestPaths;
}
/*void Board::drawAllBoard(sf::RenderWindow& window, vector<vector<char>>& board, const vector<vector<string>>& allPaths, int r, int c)
{
    // Find or create 'S' and 'M' positions
    int startRow = -1, startCol = -1;
    int endRow = -1, endCol = -1;

    
    // If 'S' does not exist, create it at the first row and column
    if (startRow == -1 || startCol == -1) {
        startRow = 0;
        startCol = 0;
        board[startRow][startCol] = 'S';
    }

    // If 'M' does not exist, create it at the last row and column
    if (endRow == -1 || endCol == -1) {
        endRow = r - 1;
        endCol = c - 1;
        board[endRow][endCol] = 'M';
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (board[i][j] == 'S') {
                startRow = i;
                startCol = j;
            }
            else if (board[i][j] == 'M') {
                endRow = i;
                endCol = j;
            }
        }
    }

    // Update the maze with paths
    for (size_t pathIndex = 0; pathIndex < allPaths.size(); ++pathIndex) {
        const vector<string>& path = allPaths[pathIndex];
        int x = 0, y = 0;  // Initialize position

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

            // Change 'B' to 'b' in the maze
            if (board[y][x] == 'B') {
                board[y][x] = 'b';
            }
        }
    }

    // Draw the maze
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Black);
            tile.setPosition(j * tileSize, i * tileSize);

            // Set color based on board content
            if (board[i][j] == 'B') {
                tile.setFillColor(sf::Color::White);
            }
            else if (board[i][j] == 'C') {
                tile.setFillColor(sf::Color::Black);
            }
            else if (board[i][j] == 'S') {
                tile.setFillColor(sf::Color::Green);
            }
            else if (board[i][j] == 'M') {
                tile.setFillColor(sf::Color::Red);
            }
            else if (board[i][j] == 'b') {
                tile.setFillColor(sf::Color::Blue);
            }
            window.draw(tile);
        }
    }
}*/


#include "Board.h"
using namespace std;

// Cheching if coordinates are valid on board
bool Board::isValid(int x, int y, int r, int c) 
{
    return x >= 0 && x < r && y >= 0 && y < c;
}


vector<string> Board::BFS(vector<vector<char>>& board) 
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
        
        tie(x, y, path) = queue.front();
        queue.pop();

        if (x == r - 1) {
            // If we at last row we return path
            return path;
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
                vector<string> newPath = path;
                newPath.push_back(directions[i]);
                queue.push({ X, Y, newPath });
            }
        }
    }

    // If there is no path found, return empty list.
    return {};
}

// Funkcja rysuj¹ca planszê w oknie SFML
void Board::drawBoard(sf::RenderWindow& window, const vector<vector<char>>& board, const vector<string>& path, int r, int c)
{
    // Draw the maze
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Black);
            tile.setPosition(j * tileSize, i * tileSize);

            // Check if the current position (i, j) is in the last path
            if (std::find(lastShortestPath.begin(), lastShortestPath.end(), to_string(j + 1)) != lastShortestPath.end() && board[i][j] == 'B') {
                tile.setFillColor(sf::Color::Blue);
            }
            else {
                // Check if the current position (i, j) is in the current path
                if (std::find(path.begin(), path.end(), to_string(j + 1)) != path.end() && board[i][j] == 'B') {
                    tile.setFillColor(sf::Color::Green);  // You can use a different color for the current path
                }
                else {
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
                }
            }

            window.draw(tile);
        }
    }

    // Draw the current path in blue
    int x = 0, y = 0;
    sf::RectangleShape pathTile(sf::Vector2f(tileSize, tileSize));
    pathTile.setFillColor(sf::Color::Blue);

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

        // Skip drawing blue next to 'M'
        if (board[y][x] != 'M') {
            pathTile.setPosition(x * tileSize, y * tileSize);
            window.draw(pathTile);
        }
        //pathTile.setPosition(x * tileSize, y * tileSize);
       // window.draw(pathTile);
    }
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
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    return maze;
}

void Board::cellChange(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze) {
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
    }
}

void Board::addStartPoint(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& maze) {
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
        if(maze[row][col] != 'S')
            maze[row][col] = 'M';
    }
}

void Board::floydWarshall(vector<vector<char>>& maze, int r, int c) {
    // Set start vertex to "S" if not provided
    bool hasStart = false;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (maze[i][j] == 'S') {
                hasStart = true;
                break;
            }
        }
        if (hasStart) {
            break;
        }
    }
    if (!hasStart) {
        maze[0][0] = 'S';
    }

    // Set end vertex to "M" if not provided
    bool hasEnd = false;
    for (int i = r - 1; i >= 0; --i) {
        for (int j = c - 1; j >= 0; --j) {
            if (maze[i][j] == 'M') {
                hasEnd = true;
                break;
            }
        }
        if (hasEnd) {
            break;
        }
    }
    if (!hasEnd) {
        maze[r - 1][c - 1] = 'M';
    }

    // Main algorithm
    for (int k = 0; k < r * c; ++k) {
        for (int i = 0; i < r * c; ++i) {
            for (int j = 0; j < r * c; ++j) {
                if (maze[i / c][i % c] == 'B' && maze[j / c][j % c] == 'B' &&
                    maze[i / c][i % c] + maze[j / c][j % c] < maze[i / c][j % c]) {
                    maze[i / c][j % c] = maze[i / c][i % c] + maze[j / c][j % c];
                }
            }
        }
    }
}

void Board::visualizeShortestPath(sf::RenderWindow& window, const vector<vector<char>>& maze, int r, int c) {
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Replace with the path to a font file on your system

    // Draw the maze
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
            cell.setPosition(j * tileSize, i * tileSize);
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(1);

            // Draw the cell based on its content
            if (maze[i][j] == 'S') {
                cell.setFillColor(sf::Color::Green); // Start cell in green
            }
            else if (maze[i][j] == 'M') {
                cell.setFillColor(sf::Color::Red); // End cell in red
            }
            else if (maze[i][j] == 'B') {
                cell.setFillColor(sf::Color::White); // Floor cell in white
            }
            else if (maze[i][j] == 'C') {
                cell.setFillColor(sf::Color::Black); // Wall cell in black
            }

            window.draw(cell);
        }
    }

    // Draw the shortest path in blue
    sf::VertexArray path(sf::LinesStrip);

    // Find the start and end vertices
    int startVertex = -1;
    int endVertex = -1;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (maze[i][j] == 'S') {
                startVertex = i * c + j;
            }
            else if (maze[i][j] == 'M') {
                endVertex = i * c + j;
            }
        }
    }

    // Add the shortest path vertices to the drawing
    if (startVertex != -1 && endVertex != -1) {
        path.append(sf::Vertex(sf::Vector2f((startVertex % c) * tileSize + tileSize/2, (startVertex / c) * tileSize + tileSize/2), sf::Color::Blue));

        while (startVertex != endVertex) {
            int nextVertex = -1;

            // Check adjacent vertices
            for (int i = 0; i < r * c; ++i) {
                if (maze[startVertex / c][startVertex % c] == 'B' &&
                    maze[i / c][i % c] == 'B' &&
                    maze[startVertex / c][startVertex % c] + maze[i / c][i % c] == maze[startVertex / c][i % c]) {
                    nextVertex = i;
                    break;
                }
            }

            if (nextVertex == -1) {
                break; // No valid path found
            }

            // Add the next vertex to the path
            path.append(sf::Vertex(sf::Vector2f((nextVertex % c) * tileSize + tileSize/2, (nextVertex / c) * tileSize + tileSize/2), sf::Color::Blue));
            startVertex = nextVertex;
        }
    }

    window.draw(path);
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
void Board::updateBoard(sf::RenderWindow& window, const vector<string>& path, vector<vector<char>>& maze)
{
    int r = maze.size();
    int c = maze[0].size();
    int x = 0, y = 0;  // Starting position

    for (const string& direction : path)
    {
        if (direction == "Up" && x > 0)
        {
            // Move up
            swap(maze[x][y], maze[x - 1][y]);
            x--;
        }
        else if (direction == "Down" && x < r - 1)
        {
            // Move down
            swap(maze[x][y], maze[x + 1][y]);
            x++;
        }
        else if (direction == "Left" && y > 0)
        {
            // Move left
            swap(maze[x][y], maze[x][y - 1]);
            y--;
        }
        else if (direction == "Right" && y < c - 1)
        {
            // Move right
            swap(maze[x][y], maze[x][y + 1]);
            y++;
        }
        // Ignore invalid directions
    }

    // Set the board modification status to true
    boardModified = true;

    // Redraw the updated board
    drawBoard(window, maze, path, r, c);
}

void Board::updateBoardInternal(sf::RenderWindow& window, const vector<string>& path, vector<vector<char>>& board)
{
    int r = board.size();
    int c = board[0].size();
    int x = 0, y = 0;  // Starting position

    // Find the positions of 'S' and 'M' before the path changes
    int startX, startY, endX, endY;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (board[i][j] == 'S')
            {
                startX = i;
                startY = j;
            }
            else if (board[i][j] == 'M')
            {
                endX = i;
                endY = j;
            }
        }
    }

    for (const string& direction : path)
    {
        // Convert the direction to lowercase
        string lowercaseDirection = direction;
        std::transform(lowercaseDirection.begin(), lowercaseDirection.end(), lowercaseDirection.begin(), ::tolower);

        // Check if the movement is valid and not affecting 'S' or 'M'
        if (lowercaseDirection == "up" && x > 0 && (x - 1 != startX || y != startY) && (x - 1 != endX || y != endY))
        {
            // Move up
            swap(board[x][y], board[x - 1][y]);
            x--;
        }
        else if (lowercaseDirection == "down" && x < r - 1 && (x + 1 != startX || y != startY) && (x + 1 != endX || y != endY))
        {
            // Move down
            swap(board[x][y], board[x + 1][y]);
            x++;
        }
        else if (lowercaseDirection == "left" && y > 0 && (x != startX || y - 1 != startY) && (x != endX || y - 1 != endY))
        {
            // Move left
            swap(board[x][y], board[x][y - 1]);
            y--;
        }
        else if (lowercaseDirection == "right" && y < c - 1 && (x != startX || y + 1 != startY) && (x != endX || y + 1 != endY))
        {
            // Move right
            swap(board[x][y], board[x][y + 1]);
            y++;
        }
        // Ignore invalid directions
    }

    // Check if 'S' or 'M' positions have changed
    bool hasStartChanged = false;
    bool hasEndChanged = false;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (board[i][j] == 'S' && (i != startX || j != startY))
            {
                hasStartChanged = true;
            }
            else if (board[i][j] == 'M' && (i != endX || j != endY))
            {
                hasEndChanged = true;
            }
        }
    }

    // Mark the last path by changing 'B' to 'b'
    for (const string& direction : lastShortestPath)
    {
        // Convert the direction to lowercase
        string lowercaseDirection = direction;
        std::transform(lowercaseDirection.begin(), lowercaseDirection.end(), lowercaseDirection.begin(), ::tolower);

        // Check if the movement is valid and not affecting 'S' or 'M'
        if (lowercaseDirection == "up" && x > 0 && (x - 1 != startX || y != startY) && (x - 1 != endX || y != endY) && board[x - 1][y] == 'B')
        {
            // Mark 'B' as 'b'
            board[x - 1][y] = 'b';
        }
        else if (lowercaseDirection == "down" && x < r - 1 && (x + 1 != startX || y != startY) && (x + 1 != endX || y != endY) && board[x + 1][y] == 'B')
        {
            // Mark 'B' as 'b'
            board[x + 1][y] = 'b';
        }
        else if (lowercaseDirection == "left" && y > 0 && (x != startX || y - 1 != startY) && (x != endX || y - 1 != endY) && board[x][y - 1] == 'B')
        {
            // Mark 'B' as 'b'
            board[x][y - 1] = 'b';
        }
        else if (lowercaseDirection == "right" && y < c - 1 && (x != startX || y + 1 != startY) && (x != endX || y + 1 != endY) && board[x][y + 1] == 'B')
        {
            // Mark 'B' as 'b'
            board[x][y + 1] = 'b';
        }
    }

    // Reset the modification status to false
    resetBoardModified();

    // Redraw the updated board
    drawBoard(window, board, path, r , c);

    // Check and handle if 'S' or 'M' positions have changed
    if (hasStartChanged)
    {
        cout << "Start position has changed." << endl;
        // Handle as needed
    }

    if (hasEndChanged)
    {
        cout << "End position has changed." << endl;
        // Handle as needed
    }
}
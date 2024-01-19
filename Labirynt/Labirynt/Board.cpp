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

/*// Funkcja pomocnicza do sprawdzenia, czy dane pole jest dostêpne
bool Board::isAvailable(const vector<vector<char>>& maze, int x, int y, int m, int n) {
    return x > 0 && x < m - 1 && y > 0 && y < n - 1 && maze[x][y] == 'C';
}

// Funkcja pomocnicza do sprawdzenia liczby dostêpnych s¹siadów
int Board::countAvailableNeighbors(const vector<vector<char>>& maze, int x, int y) {
    int count = 0;
    if (isAvailable(maze, x - 2, y, maze.size(), maze[0].size())) count++;
    if (isAvailable(maze, x + 2, y, maze.size(), maze[0].size())) count++;
    if (isAvailable(maze, x, y - 2, maze.size(), maze[0].size())) count++;
    if (isAvailable(maze, x, y + 2, maze.size(), maze[0].size())) count++;
    return count;
}

// Funkcja generuj¹ca labirynt przy u¿yciu algorytmu Recursive Backtracking
void Board::generate(vector<vector<char>>& maze, int x, int y, mt19937& gen) {
    vector<Point> directions = { {0, 2}, {0, -2}, {2, 0}, {-2, 0} };
    shuffle(directions.begin(), directions.end(), gen);

    for (const auto& dir : directions) {
        int newX = x + dir.x;
        int newY = y + dir.y;

        if (isAvailable(maze, newX, newY, maze.size(), maze[0].size())) {
            maze[x + dir.x / 2][y + dir.y / 2] = 'B'; // Oznaczamy œrodek drogi jako dostêpny
            maze[newX][newY] = 'B'; // Oznaczamy nowe pole jako dostêpne
            generate(maze, newX, newY, gen);
        }
    }
}

// Funkcja generuj¹ca losowy labirynt
vector<vector<char>> Board::generateRandomMaze(int m, int n) {
    vector<vector<char>> maze(m, vector<char>(n, 'C')); // Inicjalizacja ca³ego labiryntu jako œciany

    random_device rd;
    mt19937 gen(rd());

    // Losowo wybieramy punkt startowy i oznaczamy go jako dostêpny
    uniform_int_distribution<int> startXDist(1, m - 2);
    uniform_int_distribution<int> startYDist(1, n - 2);

    int startX = startXDist(gen);
    int startY = startYDist(gen);
    maze[startX][startY] = 'B';

    generate(maze, startX, startY, gen);

    return maze;
}*/



// Funkcja rysuj¹ca planszê w oknie SFML
void Board::drawBoard(sf::RenderWindow& window, const vector<vector<char>>& board, const vector<string>& path) 
{
    /*sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Cannot load the font. " << endl;
        exit(EXIT_FAILURE);
    }*/

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setOutlineThickness(2);
            tile.setOutlineColor(sf::Color::Black);
            tile.setPosition(j * tileSize, i * tileSize);


            if (board[i][j] == 'B') {
                tile.setFillColor(sf::Color::White);
            }
            else if (board[i][j] == 'C') {
                tile.setFillColor(sf::Color::Black);
            }

            window.draw(tile);
        }
    }

    /*// Draw the path
    for (size_t i = 0; i < path.size(); ++i) {
        sf::Text text(path[i], font, 20);
        text.setPosition(i * tileSize, board.size() * tileSize);
        window.draw(text);
    }*/
    /*// Zamaluj znalezion¹ œcie¿kê na zielono
    int x = 0;
    int y = 0;

    sf::RectangleShape pathTile(sf::Vector2f(tileSize, tileSize));
    pathTile.setFillColor(sf::Color::Green);

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
        else if (direction == "Rigth") {
            x++;
        }
        else {
            cerr << "Error. Unown direction on path" << endl;
            exit(EXIT_FAILURE);
        }

        pathTile.setPosition(x * tileSize, y * tileSize);
        window.draw(pathTile);
    }*/
    

    // Set starting point as cyan square
    for (size_t j = 0; j < board[0].size(); ++j) {
        if (board[0][j] == 'B') {
            sf::RectangleShape startTile(sf::Vector2f(tileSize, tileSize));
            startTile.setOutlineThickness(2);
            startTile.setOutlineColor(sf::Color::Black);
            startTile.setPosition(j * tileSize, 0);
            startTile.setFillColor(sf::Color::Cyan);
            window.draw(startTile);
        }
    }
}

vector<vector<char>> Board::generateMaze(int r, int c) {
    
    srand(time(0)); // Seed for random number generator

    // Create a 2D array to represent the maze
    //char maze[200][200];
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
    srand(time(0)); // Seed for random number generator

    // Create a 2D array to represent the maze
    //char maze[200][200];
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

void Board::toggleCellFromFile(int r, int c, sf::Vector2i mousePos, vector<vector<char>>& mazeFromFile) {
    int row = mousePos.y / tileSize;
    int col = mousePos.x / tileSize;

    if (row >= 0 && row < r && col >= 0 && col < c) {
        if (mazeFromFile[row][col] == 'B') {
            mazeFromFile[row][col] = 'C';
        }
        else {
            mazeFromFile[row][col] = 'B';
        }
    }
}
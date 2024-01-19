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
            else if (board[i][j] == 'S') {
                tile.setFillColor(sf::Color::Green);
            }
            else if (board[i][j] == 'M') {
                tile.setFillColor(sf::Color::Red);
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
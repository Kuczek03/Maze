#include "Board.h"

// Cheching if coordinates are valid on board
bool Board::isValid(int x, int y, int m, int n) 
{
    return x >= 0 && x < m && y >= 0 && y < n;
}


vector<string> Board::BFS(vector<vector<char>>& board) 
{
    
    int m = board.size(); // Number of rows
    int n = board[0].size(); // Number od columns
    vector<vector<bool>> visited(m, vector<bool>(n, false)); // Array of visited fields

    // First row of queue is starting points
    for (int i = 0; i < n; ++i) {
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

        if (x == m - 1) {
            // If we at last row we return path
            return path;
        }

        // Possible moves: up, down, left, rigth
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        string directions[] = { "Up ", "Down ", "Left ", "Rigth " };

        for (int i = 0; i < 4; ++i) {
            int X = x + dx[i];
            int Y = y + dy[i];

            if (isValid(X, Y, m, n) && !visited[X][Y] && board[X][Y] == 'B') {
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

            window.draw(tile);
        }
    }

    /*// Draw the path
    for (size_t i = 0; i < path.size(); ++i) {
        sf::Text text(path[i], font, 20);
        text.setPosition(i * tileSize, board.size() * tileSize);
        window.draw(text);
    }*/
    
    // Set starting point as black square
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
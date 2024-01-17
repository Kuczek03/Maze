#include "Board.h"

// Funkcja sprawdzaj�ca, czy dane wsp�rz�dne s� poprawne na planszy
bool Board::isValid(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

// Funkcja rozwi�zuj�ca problem labiryntu
vector<string> Board::findPath(vector<vector<char>>& board) {
    int m = board.size(); // Liczba wierszy planszy
    int n = board[0].size(); // Liczba kolumn planszy
    vector<vector<bool>> visited(m, vector<bool>(n, false)); // Tablica odwiedzonych p�l
    queue<tuple<int, int, vector<string>>> q; // Kolejka BFS

    // Dodaj pierwszy wiersz do kolejki jako punkty startowe
    for (int i = 0; i < n; ++i) {
        if (board[0][i] == 'B') {
            q.push({ 0, i, {to_string(i + 1)} });
            visited[0][i] = true;
        }
    }

    // Przeszukuj labirynt za pomoc� BFS
    while (!q.empty()) {
        int x, y;
        vector<string> path;
        tie(x, y, path) = q.front();
        q.pop();

        if (x == m - 1) {
            // Je�li doszli�my do ostatniego wiersza, zwracamy znalezion� �cie�k�
            return path;
        }

        // Mo�liwe ruchy: w g�r�, w d�, w lewo i w prawo
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        string directions[] = { "Up", "Down", "Left", "Rigth" };

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY, m, n) && !visited[newX][newY] && board[newX][newY] == 'B') {
                visited[newX][newY] = true;
                vector<string> newPath = path;
                newPath.push_back(directions[i]);
                q.push({ newX, newY, newPath });
            }
        }
    }

    // Je�li nie uda�o si� znale�� �cie�ki, zwracamy pust� list�
    return {};
}


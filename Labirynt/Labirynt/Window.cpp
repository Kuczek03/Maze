#include "Window.h"

void Window::mazeFromFile(const string& filename, const string& outname)
{
    // Loading the board
    vector<vector<char>> maze = file.loadBoardFromFile(filename, m, n);

    // Returning board
    cout << "Board:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    // Solving labirinth
    vector<string> path = board.BFS(maze);

    sf::RenderWindow window(sf::VideoMode(n * 40, m * 40), "Labirynt");

    // Window loop
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        } 
        window.clear();
        board.drawBoard(window, maze, path);
        window.display();
    }
    file.saveSolution(outname, path);
}

void Window::randomGeneratedMaze(const string& filename, const string& outname)
{

    // Loading the board
    vector<vector<char>> maze = file.loadBoardFromFile(filename, m, n);

    // Returning board
    cout << "Board:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    // Solving labirinth
    vector<string> path = board.BFS(maze);

    sf::RenderWindow window(sf::VideoMode(n * 40, m * 40), "Labirynt");

    // Window loop
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        board.drawBoard(window, maze, path);
        window.display();
    }
    file.saveSolution(outname, path);
}

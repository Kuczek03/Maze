#include "Window.h"

void Window::mazeFromFile(const string& filename, const string& outname)
{
    // Loading the board
    vector<vector<char>> maze = file.loadBoardFromFile(filename, r, c);

    // Returning board
    cout << "Board:" << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    // Solving labirinth
    vector<string> path = board.AStar(maze);
    vector<vector<string>> path2 = board.findAllPaths(maze);
    window->create(sf::VideoMode(c * tileSize, r * tileSize), "Maze from the file");

    // Window loop
    while (window->isOpen()) {
        sf::Event ev;

        while (window->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window->close();
            }
            else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.updateBoardWithMouseClick(mousePos, maze);
                board.cellChange(r, c, mousePos, maze);

            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::S) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.addStartPoint(r, c, mousePos, maze);
            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::M) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.addEndPoint(r, c, mousePos, maze);

            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::R) {}
        }

        window->clear();

        // Draw the board with all paths
       if (board.hasBoardModified()) {
            // Redraw the updated board
            path = board.AStar(maze);
            board.updateAllBtoB(maze, r, c);
            board.drawBoard(*window, maze, path, r, c);
            board.resetBoardModified();
            window->display();
        }
        /*if (board.hasBoardModified()) {
            // Redraw the updated board
            path2 = board.findAllPaths(maze);
            board.updateAllBtoB(maze, r, c);
            board.drawAllBoard(*window, maze, path2, r, c);
            board.resetBoardModified();
            window->display();
        }*/
        
    }
        vector<string> newPath = board.AStar(maze);
        //vector<vector<string>> newPath2 = board.findAllPaths(maze);
        file.saveSolution(outname, newPath);
        //file.saveAllSolution(outname, newPath2);
    }

void Window::drawMaze(const string& outname, int choice, int r, int c)
{
    vector<vector<char>> maze = board.generateMaze(r, c);
    vector<string> path = board.AStar(maze);
    window->create(sf::VideoMode(c * tileSize, r * tileSize), "Random generated maze");
    
    

    while (window->isOpen()) {
        sf::Event ev;

        while (window->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window->close();
            }
            else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) { 
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.cellChange(r, c, mousePos, maze);
            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::S) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.addStartPoint(r, c, mousePos, maze);
            }
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::M) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                board.addEndPoint(r, c, mousePos, maze);
            }
        }

        window->clear();
        //board.drawBoard(*window, maze, path);
        //board.floydWarshall(maze, r, c);
        //board.visualizeShortestPath(*window, maze, r, c);
        window->display();
    }
    //vector<string> newPath = board.AStar(maze);
    //file.saveSolution(outname, newPath);
}

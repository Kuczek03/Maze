#include "Window.h"

void Window::windowLoop(const string& filename, const string& outname)
{
    Board board;
    File file;

    int m, n;

    // Loading the board
    vector<vector<char>> labirynth = file.loadBoardFromFile(filename, m, n);

    // Returning board
    cout << "Board:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << labirynth[i][j] << " ";
        }
        cout << endl;
    }

    vector<string> path = board.BFS(labirynth);

    sf::RenderWindow window(sf::VideoMode(n * 40, m * 40), "Labirynt");

    // Window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Solving labirinth



        window.clear();
        board.drawBoard(window, labirynth, path);
        window.display();
    }
    file.saveSolution(outname, path);
}

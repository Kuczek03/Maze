#include "Window.h"
#include "Button.h"
#include "InputBox.h"

void Window::mazeFromFile(const string& filename, const string& outname)
{
	vector<vector<char>> maze = file.loadBoardFromFile(filename, r, c);	
	
	vector<string> path = board.AStar(maze);

	window->create(sf::VideoMode(c * tileSize, r * tileSize), "Maze from the file", sf::Style::Titlebar | sf::Style::Close);

	while (window->isOpen()) {
		sf::Event ev;
		while (window->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window->close();
				board.setBoardModified();
				menu();
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

		

	   if (board.hasBoardModified()) {
		   window->clear();
			path = board.AStar(maze);
			board.updateAllBtoB(maze, r, c);
			board.drawBoard(*window, maze, path, r, c);
			board.resetBoardModified();
			window->display();
			if (path.empty() && window->isOpen())
				noPathBox();
		}		
	}
		vector<string> newPath = board.AStar(maze);		
		file.saveSolution(outname, newPath);		
}

void Window::drawRandomMaze(const string& outname, int r, int c, double wallProbability)
{
	vector<vector<char>> maze = board.generateMazeWithProbability(r, c, wallProbability);
	vector<string> path = board.AStar(maze);

	window->create(sf::VideoMode(c * tileSize, r * tileSize), "Random generated maze", sf::Style::Titlebar | sf::Style::Close);
	
	while (window->isOpen()) {
		sf::Event ev;
		while (window->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {				
				window->close();
				board.setBoardModified();
				menu();				
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
			
		}

		

		if (board.hasBoardModified()) {	
			window->clear();
			path = board.AStar(maze);			
			board.updateAllBtoB(maze, r, c);
			
			board.drawBoard(*window, maze, path, r, c);
			
			board.resetBoardModified();
			window->display();

			if (path.empty()&&window->isOpen())
				noPathBox();
		}
	}
	vector<string> newPath = board.AStar(maze);
	file.saveSolution("RandomOdp.txt", newPath);
}


void Window::menu() {

	window->create(sf::VideoMode(400,400), "Path finder", sf::Style::Titlebar | sf::Style::Close);
	
	sf::Font font;
	sf::Color 
		blue(117, 208, 236),
		background(102, 153, 255);
	if (!font.loadFromFile("fonts/Lato-Italic.ttf")) {
		return;
	}

	Button
		pathFromFile(125.f, 110.f, 150.f, 75.f, "Random Maze", font, blue, sf::Color::White),
		randomMaze(125.f, 200.f, 150.f, 75.f, "Maze from file", font, blue, sf::Color::White),
		exit(125.f, 290.f, 150.f, 75.f, "Exit", font, blue, sf::Color::White);
	
	sf::Text title;
	title.setFont(font);
	title.setString("Path Finder!");
	title.setCharacterSize(60);
	title.setOutlineThickness(2);
	title.setOutlineColor(sf::Color::Black);
	title.setFillColor(sf::Color::White);
	title.setPosition(50.f, 15.f);
	
	while (window->isOpen()) {
		sf::Event ev;
		
		while (window->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window->close();
				wypierdol = false;
			}

			if (ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Left) {				 
				
				if (pathFromFile.isMouseOver(*window)) {					

					InputBox inputBox("Enter R C and WallProb", font);
					auto result = inputBox.r3n();

					int r = std::get<0>(result);
					int c = std::get<1>(result);
					double w = std::get<2>(result);
					
					drawRandomMaze("RandomOpd.txt",r,c,w);
				}
				
				if (randomMaze.isMouseOver(*window)) {										
					string userInput;
					
					do{	
						InputBox inputBox("Enter file name:", font);
						userInput = inputBox.run();
						ifstream file(userInput);
					
						if (inputBox.event.type == sf::Event::Closed)
							break;
						if (file.good()){
							mazeFromFile(userInput, "odp.txt");
							break;
						}							
						else {						
							file.clear();
						}
						
					} while (true);
					
					
				}
				if (exit.isMouseOver(*window)) {
					window->close();
					wypierdol = false;
				}				
			}
		} 
		window->clear(background);
		window->draw(title);
		pathFromFile.draw(*window);
		randomMaze.draw(*window);
		exit.draw(*window);
		window->display();
	}
}

int Window::noPathBox() {
	sf::RenderWindow window(sf::VideoMode(200, 100), "Error");
	sf::Color background(102, 153, 255);
	sf::Font font;
	if (!font.loadFromFile("fonts/Lato-Italic.ttf")) {
		return EXIT_FAILURE;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Path not found");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setPosition((window.getSize().x - textBounds.width) / 2.f, (window.getSize().y - textBounds.height) / 2.f - 10);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(background); 

		window.draw(text);

		window.display();
	}

	return EXIT_SUCCESS;
}

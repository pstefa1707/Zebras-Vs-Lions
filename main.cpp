#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "lib/Grid.hpp"
#include "lib/Animal.hpp"


void render_text(sf::RenderWindow& window, sf::Clock& CLOCK, sf::Font& FONT, sf::Vector3i& data, int& window_width, int& window_height);
int main()
{
	//Setup
	int window_width;
	int window_height;
	int wator_size;

	std::cout << "Enter window width: ";
	std::cin >> window_width;
	std::cout << "Enter window height: ";
	std::cin >> window_height;
	std::cout << "Enter wator size: ";
	std::cin >> wator_size;

	//Initilises grid to begin simulation
	int starting_zebra_percentage = 15;
	int starting_lion_percentage = 2;
	Grid grid(sf::Vector2f(wator_size, wator_size), sf::Vector2f(window_width, window_height));
	grid.init(starting_zebra_percentage, starting_lion_percentage);
	sf::RenderWindow window(sf::VideoMode(window_width, window_height, 32), "Pstefa's Zebras and Lions");
	sf::Font arial;
	arial.loadFromFile("./lib/arial.ttf");
	sf::Event event;
	sf::Clock CLOCK;
	CLOCK.restart();
	int years = 0;

	while (window.isOpen())
	{
		years ++;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			grid.init(starting_zebra_percentage, starting_lion_percentage);
			years = 0;
		}
		window.clear(sf::Color(30, 150, 30));
		sf::Vector3i data = grid.step(window, years);
		render_text(window, CLOCK, arial, data, window_width, window_height);
		window.display();
	}

	return 0;
}

void render_text(sf::RenderWindow& window, sf::Clock& CLOCK, sf::Font& FONT, sf::Vector3i& data, int& window_width, int& window_height)
{
	std::string fps = "FPS: " + std::to_string((int)round(1 / CLOCK.getElapsedTime().asSeconds()));
	sf::Text FPS(fps, FONT, 30);
	sf::Text ANIMALS("Zebras: " + std::to_string(data.x) + "\nLions: " + std::to_string(data.y) + "\nYear: " + std::to_string(data.z), FONT, 30);
	FPS.setFillColor(sf::Color::Black);
	ANIMALS.setFillColor(sf::Color::Black);
	ANIMALS.setPosition(sf::Vector2f(5, 5));
	FPS.setPosition(sf::Vector2f(window_width - 130, window_height - 35));
	window.draw(ANIMALS);
	window.draw(FPS);
	CLOCK.restart();
}

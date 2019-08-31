#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#pragma once

class Animal;

class Grid
{
	private:
		sf::Vector2f _Grid_Size;
		sf::Vector2f _Cell_Size;
		sf::Vector2f _Window_Size;
		std::vector<Animal*> _animals;
		void _move(Animal& zebra, const sf::Vector2i& end_position);
		void _reproduce(Animal* zebra, const sf::Vector2i& end_position);
		void _eat(const sf::Vector2i& end_position);
		void _kill(const sf::Vector2i& position);
		Animal* _get_cell(sf::Vector2i pos);
	public:
		Grid(const sf::Vector2f& Grid_Size, const sf::Vector2f& WINDOW_SIZE)
		{
			_Window_Size = WINDOW_SIZE;
			_Grid_Size = Grid_Size;
			_Cell_Size.x = WINDOW_SIZE.x/Grid_Size.x;
			_Cell_Size.y = WINDOW_SIZE.y/Grid_Size.y;
			_animals.resize(_Grid_Size.x * _Grid_Size.y);
		}
		sf::Vector3i step(sf::RenderWindow& window, int& years);
		void init(int percentage_zebra, int percentage_lions);
};

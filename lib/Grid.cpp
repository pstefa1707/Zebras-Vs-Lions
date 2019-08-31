#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Grid.hpp"
#include "Animal.hpp"

#define REPRODUCTION_RATE 2

void Grid::init(int percentage_zebra, int percentage_lions)
{
	for (int x = 0; x < this->_Grid_Size.x; x++)
	{
		for (int y = 0; y < this->_Grid_Size.y; y++)
		{
			if ((rand() % 100) < percentage_lions)
			{
				this->_animals[y * this->_Grid_Size.x + x] = new Animal(sf::Vector2i(x, y), Animal::type::lion);
			}
			else if ((rand() % 100) < percentage_zebra)
			{
				this->_animals[y * this->_Grid_Size.x + x] = new Animal(sf::Vector2i(x, y), Animal::type::zebra);
			}
			else
			{
				this->_animals[y * this->_Grid_Size.x + x] = nullptr;
			}

		}
	}
}

void Grid::_move(Animal& animal, const sf::Vector2i& end_position)
{
	this->_animals[end_position.y * this->_Grid_Size.x + end_position.x] = this->_animals[animal.get_position().y * this->_Grid_Size.x + animal.get_position().x];
	this->_animals[animal.get_position().y * this->_Grid_Size.x + animal.get_position().x] = nullptr;
	this->_animals[end_position.y * this->_Grid_Size.x + end_position.x]->set_position(end_position);
}

void Grid::_reproduce(Animal* zebra, const sf::Vector2i& end_position)
{
	delete	this->_animals[end_position.y * this->_Grid_Size.x + end_position.x];
	this->_animals[end_position.y * this->_Grid_Size.x + end_position.x] =  new Animal(end_position, Animal::type::zebra);
	this->_animals[end_position.y * this->_Grid_Size.x + end_position.x]->set_health(zebra->get_health());
}

void Grid::_eat(const sf::Vector2i& end_position)
{
	int index = end_position.y * this->_Grid_Size.x + end_position.x;
	Animal* temp_animal = this->_animals[index];
	this->_animals[index] = new Animal(end_position, Animal::type::lion);
	this->_animals[index]->set_health(temp_animal->get_health());
	delete temp_animal;
}

void Grid::_kill(const sf::Vector2i& position)
{
	delete this->_animals[position.y * this->_Grid_Size.x + position.x];
	this->_animals[position.y * this->_Grid_Size.x + position.x] = nullptr;
}

Animal* Grid::_get_cell(sf::Vector2i pos)
{
	return this->_animals[pos.y * this->_Grid_Size.x + pos.x];
}

sf::Vector3i Grid::step(sf::RenderWindow& window, int& years)
{
	int zebras = 0;
	int lions = 0;
	for (Animal* animal: this->_animals)
	{
		if (animal == nullptr) continue;
		animal->update();

		int new_x = animal->get_position().x + (rand() % 3) - 1;
		int new_y = animal->get_position().y + (rand() % 3) - 1;

		//Checks
		if (new_x >= this->_Grid_Size.x) new_x = new_x % (int)this->_Grid_Size.x;
		if (new_y >= this->_Grid_Size.y) new_y = new_y % (int)this->_Grid_Size.y;
		if (new_x < 0) new_x = this->_Grid_Size.x + new_x;
		if (new_y < 0) new_y = this->_Grid_Size.y + new_y;
		if (new_x == animal->get_position().x && new_y == animal->get_position().y) continue;

		Animal* other_cell = this->_get_cell(sf::Vector2i(new_x, new_y));

		sf::RectangleShape rect;
		rect.setSize(this->_Cell_Size);
		rect.setPosition(animal->get_position().x * this->_Cell_Size.x, animal->get_position().y * this->_Cell_Size.y);

		switch (animal->get_type())
		{
			case Animal::type::zebra:
				zebras ++;
				rect.setFillColor(sf::Color::White);
				if (other_cell == nullptr)
				{
					if (animal->get_health() >= animal->get_max_health()/REPRODUCTION_RATE)
					{
						animal->set_health(10);
						this->_reproduce(animal, sf::Vector2i(new_x, new_y));
					}
					else
					{
						this->_move(*animal, sf::Vector2i(new_x, new_y));
					}
				}
				break;
			case Animal::type::lion:
				lions ++;
				rect.setFillColor(sf::Color::Red);
				if (animal->get_health() <= 0)
				{
					this->_kill(animal->get_position());
					break;
				}
				else if (other_cell == nullptr)
				{
					this->_move(*animal, sf::Vector2i(new_x, new_y));
				}
				else if (other_cell->get_type() == Animal::type::zebra)
				{
					animal->heal(other_cell->get_health());
					this->_eat(sf::Vector2i(new_x, new_y));
				}
				break;
			default:
				break;
		}
		window.draw(rect);
	}
	return sf::Vector3i(zebras, lions, years);
}
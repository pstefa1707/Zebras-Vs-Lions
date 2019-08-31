#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Animal.hpp"
#include "Grid.hpp"

Animal::type Animal::get_type()
{
	return this->_type;
}

sf::Vector2i Animal::get_position()
{
	return this->_position;
}

void Animal::set_position(const sf::Vector2i& pos)
{
	this->_position = pos;
}

int Animal::get_health()
{
	return this->_health;
}

int Animal::get_max_health()
{
	return this->_max_health;
}

void Animal::set_health(int amount)
{
	this->_health = amount;
}

void Animal::heal(int amount)
{
	this->_health -= amount;
	if (this->_health < 0)
	{
		this->_health = 0;
	}
}

void Animal::update()
{
	switch (this->_type)
	{
		case type::zebra:
			this->_health ++;
			if (this->_health > this->_max_health) this->_health = this->_max_health;
			break;
		case type::lion:
			this->_health --;
			break;
		default:
			break;
	}
}
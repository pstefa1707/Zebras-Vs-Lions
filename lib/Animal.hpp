#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class Animal
{
	public:
		enum class type {zebra, lion};
		Animal(sf::Vector2i position, Animal::type animal_type)
		{
			_type = animal_type;
			_position = position;
			_health = round(_max_health / 5);
		}
		Animal::type get_type();
		sf::Vector2i get_position();
		int get_health();
		int get_max_health();
		void set_health(int amount);
		void heal(int amount);
		void update();
		void set_position(const sf::Vector2i& pos);
	private:
		sf::Vector2i _position;
		int _health;
		Animal::type _type;
		int _max_health = 80;
};
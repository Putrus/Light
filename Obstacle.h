#pragma once
#include <SFML/Graphics.hpp>
class Obstacle : public sf::VertexArray
{
private:
public:
	Obstacle();
	Obstacle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
	Obstacle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
	void setColor(sf::Color color);
	void setPosition(sf::Vector2f);
	void setPosition(float x, float y);

};


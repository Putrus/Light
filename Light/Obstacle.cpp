#include "Obstacle.h"

Obstacle::Obstacle(){}

Obstacle::Obstacle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) : sf::VertexArray(sf::Triangles, 3)
{
	this->operator[](0).position = a;
	this->operator[](1).position = b;
	this->operator[](2).position = c;
}

Obstacle::Obstacle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) : sf::VertexArray(sf::Quads, 4)
{
	this->operator[](0).position = a;
	this->operator[](1).position = b;
	this->operator[](2).position = c;
	this->operator[](3).position = d;
}


void Obstacle::setColor(sf::Color color)
{
	for (int i = 0; i < this->getVertexCount(); i++)
	{
		this->operator[](i).color = color;
	}
	
}

void Obstacle::setPosition(sf::Vector2f pos)
{}

void Obstacle::setPosition(float x, float y)
{}
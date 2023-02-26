#pragma once
#include <SFML/Graphics.hpp>
#include "BadVertexException.h"
#include "Obstacle.h"
#include <iostream>
#include <windows.h>
#include <cmath>
class LineTest : public sf::VertexArray
{
private:
	float T;
	float alpha;
public:
	float x_a2, y_a2;
public:
	LineTest(sf::Vector2f a, sf::Vector2f b);

	void setVertexPosition(int vertex, sf::Vector2f pos);
	void setVertexPosition(int vertex, float x, float y);
	sf::Vector2f getVertexPosition(int vertex);
	float calcCollision(float x_b, float y_b, float x_b2, float y_b2);
	void calcCollision(std::vector<Obstacle> obstacles);
	void calcDerivativePosition(float alpha, LineTest line, float length);
	float getLength();
	void calcAlpha();
	float getAlpha();
};


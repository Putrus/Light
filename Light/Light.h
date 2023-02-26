#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "LineTest.h"
#include "Obstacle.h"
class Light
{
private:
	float x;
	float y;
	float size;
	std::vector<LineTest*> lines;
	sf::VertexArray* shape;
	sf::Shader* shader;
public:
	Light();
	Light(float x, float y, float size, std::vector<Obstacle> obstacles);
	~Light();
	void draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void update(std::vector<Obstacle> obstacles);
	std::vector<LineTest*> getLines();
	void setBrightness(float brightness);
};


#include "Light.h"


Light::Light(){
	this->x = 0.0f;
	this->y = 0.0f;
	this->size = 200;
}


Light::Light(float x, float y, float size, std::vector<Obstacle> obstacles)
{
	this->x = x;
	this->y = y;
	this->size = size;
	for (int i = 0; i < (int)obstacles.size(); i++)
	{
		for (int j = 0; j < (int)obstacles[i].getVertexCount(); j++)
		{
			LineTest* line = new LineTest(sf::Vector2f(x, y),obstacles[i][j].position);
			this->lines.push_back(line);
			LineTest* dLine = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
			LineTest* dLine2 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
			this->derivativeLines.push_back(dLine);
			this->derivativeLines.push_back(dLine2);
		}
		LineTest* line1 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine1 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine12 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line2 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 600.0f));
		LineTest* dLine2 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine22 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line3 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(600.0f, 600.0f));
		LineTest* dLine3 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine32 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line4 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(600.0f, 0.0f));
		LineTest* dLine4 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine42 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		this->lines.push_back(line1);
		this->derivativeLines.push_back(dLine1);
		this->derivativeLines.push_back(dLine12);
		this->lines.push_back(line2);
		this->derivativeLines.push_back(dLine2);
		this->derivativeLines.push_back(dLine22);
		this->lines.push_back(line3);
		this->derivativeLines.push_back(dLine3);
		this->derivativeLines.push_back(dLine32);
		this->lines.push_back(line4);
		this->derivativeLines.push_back(dLine4);
		this->derivativeLines.push_back(dLine42);

		
	}
}


void Light::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		window.draw(*lines[i]);
	}
	for (size_t i = 0; i < derivativeLines.size(); i++)
	{
		window.draw(*derivativeLines[i]);
	}
}


void Light::setPosition(sf::Vector2f pos)
{
	this->x = pos.x;
	this->y = pos.y;
	for (size_t i = 0; i < lines.size(); i++)
	{
		lines[i]->setVertexPosition(0, pos);
		derivativeLines[i * 2]->setVertexPosition(0, pos);
		derivativeLines[i * 2 + 1]->setVertexPosition(0, pos);
	}
}
void Light::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Light::getPosition() {
	return sf::Vector2f(x, y);
}

void Light::update(std::vector<Obstacle> obstacles)
{
	std::sort(lines.begin(), lines.end(), [](LineTest * a, LineTest* b) {
		return a->getAlpha() < b->getAlpha(); });
	for (size_t i = 0; i < lines.size(); i++)
	{
		derivativeLines[i*2]->calcDerivativePosition(0.005, *lines[i], size);
		derivativeLines[i*2+1]->calcDerivativePosition(-0.005, *lines[i], size);
		lines[i]->calcCollision(obstacles);
		derivativeLines[i*2]->calcCollision(obstacles);
		derivativeLines[i*2+1]->calcCollision(obstacles);
		/*float k = 255 * (float)i / (float)lines.size();
		lines[i][0][0].color = sf::Color(k, 255.0f - k, 255.0f - k);
		lines[i][0][1].color = sf::Color(k, 255.0f - k, 255.0f - k);*/

		lines[i]->calcAlpha();
	}
	return;
}



std::vector<LineTest*> Light::getLines() {
	return lines;
}

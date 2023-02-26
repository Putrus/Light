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
			this->lines.push_back(dLine);
			this->lines.push_back(dLine2);
		}
		LineTest* line1 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine1 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine12 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line2 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 1000.0f));
		LineTest* dLine2 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine22 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line3 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(1000.0f, 1000.0f));
		LineTest* dLine3 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine32 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* line4 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(1000.0f, 0.0f));
		LineTest* dLine4 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		LineTest* dLine42 = new LineTest(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f));
		this->lines.push_back(line1);
		this->lines.push_back(dLine1);
		this->lines.push_back(dLine12);
		this->lines.push_back(line2);
		this->lines.push_back(dLine2);
		this->lines.push_back(dLine22);
		this->lines.push_back(line3);
		this->lines.push_back(dLine3);
		this->lines.push_back(dLine32);
		this->lines.push_back(line4);
		this->lines.push_back(dLine4);
		this->lines.push_back(dLine42);
	}
	shape = new sf::VertexArray(sf::TriangleFan, lines.size() + 2);
	shader = new sf::Shader();
	if (!shader->loadFromFile("lightShader.frag", sf::Shader::Fragment))
	{
		std::cout << "Failed to load shader!" << std::endl;
	}
	shader->setUniform("lightPos", sf::Vector2f(0.0f, 0.0f));
	shader->setUniform("radius", 400.f);
	shader->setUniform("brightness", 1.0f);
	shader->setUniform("color", sf::Vector3f(1.0f, 1.0f, 1.0f));

}


Light::~Light() {
	delete shape;
	delete shader;
	for (size_t i = 0; i < lines.size(); i++) {
		delete lines[i];
		lines.erase(lines.begin() + i);
	}
}

void Light::draw(sf::RenderWindow& window)
{
	/*for (size_t i = 0; i < lines.size(); i++)
	{
		window.draw(*lines[i]);
	}*/
	window.draw(*shape, shader);
}


void Light::setPosition(sf::Vector2f pos)
{
	this->x = pos.x;
	this->y = pos.y;
	for (size_t i = 0; i < lines.size(); i+=3)
	{
		lines[i]->setVertexPosition(0, pos);
		lines[i + 1]->setVertexPosition(0, pos);
		lines[i + 2]->setVertexPosition(0, pos);
	}
	shader->setUniform("lightPos", sf::Vector2f(x, 1000 - y));
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
	for (size_t i = 0; i < lines.size(); i+=3)
	{
		lines[i+1]->calcDerivativePosition(0.01, *lines[i], size);
		lines[i+2]->calcDerivativePosition(-0.01, *lines[i], size);
		lines[i]->calcCollision(obstacles);
		lines[i+1]->calcCollision(obstacles);
		lines[i+2]->calcCollision(obstacles);
		lines[i]->calcAlpha();
		lines[i+1]->calcAlpha();
		lines[i+2]->calcAlpha();
	}
	std::vector<LineTest*> l = lines;
	std::sort(l.begin(), l.end(), [](LineTest* a, LineTest* b) {
		return a->getAlpha() < b->getAlpha(); });
	(*shape)[0].position = getPosition();
	for (size_t i = 0; i < l.size(); i += 3) {
		(*shape)[i + 1].position = l[i]->getVertexPosition(1);
		(*shape)[i + 2].position = l[i + 1]->getVertexPosition(1);
		(*shape)[i + 3].position = l[i + 2]->getVertexPosition(1);
	}
	(*shape)[l.size() + 1].position = l[0]->getVertexPosition(1);
}



std::vector<LineTest*> Light::getLines() {
	return lines;
}


void Light::setBrightness(float brightness) {
	shader->setUniform("brightness", brightness);
}
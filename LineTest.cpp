#include "LineTest.h"


LineTest::LineTest(sf::Vector2f a, sf::Vector2f b) : sf::VertexArray(sf::Lines, 2)
{
	this->operator[](0).position = a;
	this->operator[](1).position = b;
	this->operator[](0).color = sf::Color::Red;
	this->operator[](1).color = sf::Color::Red;
	this->T = 1;
	this->x_a2 = b.x;
	this->y_a2 = b.y;
	this->alpha = 0.0f;
}


void LineTest::setVertexPosition(int vertex, sf::Vector2f pos)
{
	if (vertex == 0 || vertex == 1)
	{
		this->operator[](vertex).position = pos;
		return;
	}
	throw new BadVertexException();
}

void LineTest::setVertexPosition(int vertex, float x, float y)
{
	setVertexPosition(vertex, sf::Vector2f(x, y));
}

sf::Vector2f LineTest::getVertexPosition(int vertex)
{
	if (vertex == 0 || vertex == 1)
	{
		return this->operator[](vertex).position;
	}
	throw new BadVertexException();
}

float LineTest::calcCollision(float x_b, float y_b, float x_b2, float y_b2)
{
	float x_a = getVertexPosition(0).x;
	float y_a = getVertexPosition(0).y;
	if (x_b == x_b2) {
		x_b-=0.01;
	}
	if (y_b == y_b2) {
		y_b -= 0.01;
	}
	float dx_b = x_b2 - x_b;
	float dy_b = y_b2 - y_b;
	
	float dx_a = x_a2 - x_a;
	float dy_a = y_a2 - y_a;

	float T_a = (y_b * dx_b + dy_b * x_a - x_b * dy_b - y_a * dx_b) / (dy_a * dx_b - dy_b * dx_a);

	float T_b = (x_a + dx_a * T_a - x_b) / dx_b;
	
	//std::cout << "T_a: " << T_a << " T_b: " << T_b << std::endl;
	if (T_a > 0 && T_a < 1 && T_b > 0 && T_b < 1)
	{

		x_a = getVertexPosition(0).x + dx_a * T_a;
		y_a = getVertexPosition(0).y + dy_a * T_a;
		setVertexPosition(1, x_a, y_a);
		return T_a;
	}
	x_a = getVertexPosition(0).x + dx_a * 1;
	y_a = getVertexPosition(0).y + dy_a * 1;
	setVertexPosition(1, x_a, y_a);
	return 1;
}

void LineTest::calcCollision(std::vector<Obstacle> obstacles) {
	float dx_a = x_a2 - getVertexPosition(0).x;
	float dy_a = y_a2 - getVertexPosition(0).y;
	float t = std::min(calcCollision(0.0f, 0.0f, 600.0f, 0.0f), 
		std::min(calcCollision(600.0f, 0.0f, 600.0f, 600.0f), 
			std::min(calcCollision(600.0f, 600.0f, 0.0f, 600.0f), 
				calcCollision(0.0f, 600.0f, 0.0f, 0.0f))));
	for (size_t i = 0; i < obstacles.size(); i++) {
		for (size_t j = 0; j < obstacles[i].getVertexCount(); j++) {
			float tmp = calcCollision(obstacles[i][j].position.x, obstacles[i][j].position.y, obstacles[i][(j + 1) % (int)obstacles[i].getVertexCount()].position.x, obstacles[i][(j + 1) % (int)obstacles[i].getVertexCount()].position.y);
			if (tmp < t) {
				t = tmp;
			}
		}
	}
	float x_a = getVertexPosition(0).x + dx_a * t;
	float y_a = getVertexPosition(0).y + dy_a * t;
	setVertexPosition(1, x_a, y_a);

}


void LineTest::calcDerivativePosition(float alpha, LineTest line, float length)
{
	float x_1 = line.getVertexPosition(0).x;
	float y_1 = line.getVertexPosition(0).y;
	float x = line.x_a2 - x_1;
	float y = line.y_a2 - y_1;
	float l = line.getLength();
	float beta = acos(x/l);
	if (y_1 >= line.y_a2)
	{
		setVertexPosition(1, x_1 + length * cos(beta + alpha), y_1 - length * sin(beta + alpha));
	}
	else {
		setVertexPosition(1, x_1 + length * cos(beta - alpha), y_1 + length * sin(beta - alpha));
	}
	x_a2 = getVertexPosition(1).x;
	y_a2 = getVertexPosition(1).y;
}

float LineTest::getLength()
{
	float x = x_a2 - getVertexPosition(0).x;
	float y = y_a2 - getVertexPosition(0).y;
	return sqrt(x * x + y * y);
}

void LineTest::calcAlpha() {

	float a = atan((this->getVertexPosition(0).y - this->getVertexPosition(1).y) / (this->getVertexPosition(0).x - this->getVertexPosition(1).x));
	if (getVertexPosition(1).x > getVertexPosition(0).x) {
		alpha = 3.146 + a;
	}
	else if (getVertexPosition(1).x <= getVertexPosition(0).x && getVertexPosition(1).y >= getVertexPosition(0).y) {
		alpha = 6.292 + a;
	}
	else {
		alpha = a;
	}
	return;
}

float LineTest::getAlpha() {
	return alpha;
}
#include <iostream>
#include <SFML/Graphics.hpp>

#include "LineTest.h"
#include "Obstacle.h"
#include "Light.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	

	sf::Sprite bg;
	sf::Texture texture;
	if (!texture.loadFromFile("Wooden.png"))
   {
		std::cout << "Error!";
		return -1;
	}
	texture.setRepeated(true);
	bg.setTexture(texture);
	bg.setScale(0.3, 0.3);
	bg.setTextureRect(sf::IntRect(0, 0, 8000, 8000));

	std::vector<Obstacle> obstacles;
	Obstacle obstacle(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(150.0f, 100.0f), sf::Vector2f(150.0f, 150.0f), sf::Vector2f(100.0f, 150.0f));
	obstacle.setColor(sf::Color::Red);
	Obstacle obstacle2(sf::Vector2f(300.0f, 300.0f), sf::Vector2f(370.0f, 300.0f), sf::Vector2f(400.0f, 170.0f), sf::Vector2f(40.0f, 250.0f));
	obstacle2.setColor(sf::Color::Blue);
	Obstacle obstacle3(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(560.0f, 210.0f), sf::Vector2f(580.0f, 550.0f), sf::Vector2f(380.0f, 560.0f));
	obstacle3.setColor(sf::Color::Green);
	obstacles.push_back(obstacle);
	obstacles.push_back(obstacle2);
	obstacles.push_back(obstacle3);
	Light* light = new Light(0.0f, 0.0f, 1200.0f, obstacles);
	std::vector<Light*> lights;
	for (int i = 0; i < 9; i++)
   {
		Light* light1 = new Light(0.0f, 0.0f, 1200.0f, obstacles);
		light1->setBrightness(0.4f);
		lights.push_back(light1);
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float mx = sf::Mouse::getPosition(window).x;
		float my = sf::Mouse::getPosition(window).y;
		light->setPosition(mx, my);
		light->update(obstacles);
		for (int i = 0; i < 9; i++)
      {
			lights[i]->setPosition(mx + 5.0f * cos(6.28 * i/9), my - 5.0f * sin(6.28 * i/9));
			lights[i]->update(obstacles);
		}
		window.clear();
		light->draw(window);
		for (int i = 0; i < 9; i++)
      {
			lights[i]->draw(window);
		}
		window.draw(bg, sf::BlendMultiply);
		window.display();
	}

	return 0;
}
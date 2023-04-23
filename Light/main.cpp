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
	Obstacle obstacle(sf::Vector2f(100.f, 100.f), sf::Vector2f(150.f, 100.f), sf::Vector2f(150.f, 150.f), sf::Vector2f(100.f, 150.f));
	obstacle.setColor(sf::Color::Red);
	Obstacle obstacle2(sf::Vector2f(300.f, 300.f), sf::Vector2f(370.f, 300.f), sf::Vector2f(400.f, 170.f), sf::Vector2f(40.f, 250.f));
	obstacle2.setColor(sf::Color::Blue);
	Obstacle obstacle3(sf::Vector2f(400.f, 400.f), sf::Vector2f(560.f, 210.f), sf::Vector2f(580.f, 550.f), sf::Vector2f(380.f, 560.f));
	obstacle3.setColor(sf::Color::Green);
	Obstacle obstacle4(sf::Vector2f(700.f, 700.f), sf::Vector2f(850.f, 800.f), sf::Vector2f(900.f, 900.f), sf::Vector2f(500.f, 900.f));
	obstacle4.setColor(sf::Color::Magenta);
	Obstacle obstacle5(sf::Vector2f(50.f, 700.f), sf::Vector2f(100.f, 680.f), sf::Vector2f(100.f, 750.f), sf::Vector2f(40.f, 800.f));
	obstacle4.setColor(sf::Color::Yellow);
	obstacles.push_back(obstacle);
	obstacles.push_back(obstacle2);
	obstacles.push_back(obstacle3);
	obstacles.push_back(obstacle4);
	obstacles.push_back(obstacle5);
	Light* light = new Light(0.f, 0.f, 1200.f, obstacles);
	std::vector<Light*> lights;
	for (int i = 0; i < 9; i++)
   {
		Light* light1 = new Light(0.f, 0.f, 1200.f, obstacles);
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
			lights[i]->setPosition(mx + 5.f * cos(6.28 * i/9), my - 5.f * sin(6.28 * i/9));
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
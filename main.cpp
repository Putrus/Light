#include <iostream>
#include <SFML/Graphics.hpp>

#include "LineTest.h"
#include "Obstacle.h"
#include "Light.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	
	sf::CircleShape shape(600.f);
	shape.setFillColor(sf::Color::White);
	sf::Sprite bg;
	sf::Texture texture;
	if (!texture.loadFromFile("Wooden.png")) {
		std::cout << "Error!";
		return -1;
	}
	texture.setRepeated(true);
	
	bg.setTexture(texture);
	bg.setScale(0.3, 0.3);
	bg.setTextureRect(sf::IntRect(0, 0, 8000, 8000));
	shape.setOrigin(shape.getGlobalBounds().left + shape.getGlobalBounds().width / 2, shape.getGlobalBounds().top + shape.getGlobalBounds().height / 2);


	sf::Shader shader;
	if (!shader.loadFromFile("myShader.frag",sf::Shader::Fragment))
	{
		std::cout << "Shader error!";
		return -1;
	}
	shader.setUniform("lightPos", sf::Vector2f(0.0f, 0.0f));
	shader.setUniform("radius", 400.f);
	

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
	sf::Vector2f a(5.0f, 3.0f);
	sf::Vector2f b(3.0f, 2.0f);
	sf::Vector2f c = a - b;

	LineTest* dLine = new LineTest(sf::Vector2f(300.0f,300.0f), sf::Vector2f(0.0f,0.0f));
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
		//dLine->setVertexPosition(1, mx, my);
		//dLine->calcAlpha(1);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			
		}
		/*float mx = sf::Mouse::getPosition(window).x;
		float my = sf::Mouse::getPosition(window).y;
		shape.setPosition(mx,my);
		shader.setUniform("lightPos", sf::Vector2f(mx, 600 - my));
		window.draw(shape,&shader);
		window.draw(bg, sf::BlendMultiply);*/
		//dLine->calcCollision(100.0f, 150.0f, 100.0f, 100.0f);
		light->setPosition(mx, my);
		light->update(obstacles);
		shader.setUniform("lightPos", sf::Vector2f(mx, 600 - my));
		sf::VertexArray k(sf::TriangleFan, light->getLines().size()*3 + 2);
		k[0].position = light->getPosition();
		for (int i = 0; i < light->getLines().size(); i++) {
			k[i * 3 + 2].position = light->getLines()[i]->getVertexPosition(1);
				k[i * 3 + 1].position = light->derivativeLines[i * 2]->getVertexPosition(1);
				k[i * 3 + 3].position = light->derivativeLines[i * 2 + 1]->getVertexPosition(1);
		}
		k[light->getLines().size()*3 + 1].position = light->derivativeLines[0]->getVertexPosition(1);
		
		sf::ConvexShape s(light->getLines().size() * 3);
		for (int i = 0; i < light->getLines().size(); i++) {
			s.setPoint(i * 3, light->derivativeLines[i * 2]->getVertexPosition(1));
			s.setPoint(i * 3 + 1, light->getLines()[i]->getVertexPosition(1));
			s.setPoint(i * 3 + 2, light->derivativeLines[i * 2 + 1]->getVertexPosition(1));
		}
		
		window.clear();
		//window.draw(obstacle);
		//window.draw(obstacle2);
		//window.draw(obstacle3);
		//window.draw(*dLine);
		window.draw(k, &shader);
		window.draw(bg, sf::BlendMultiply);
		//window.draw(s);
		//light->draw(window); 
		window.display();
	}

	return 0;
}
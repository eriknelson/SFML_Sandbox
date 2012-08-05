#include "StdAfx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include "RedTile.h"
#include "GreenTile.h"
#include "TileSheet.h"
#include "level.h"

sf::Rect<float> GetViewportRect(sf::View& v);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280,640), "Sandbox!", sf::Style::Fullscreen);
	window.setFramerateLimit(30);

	nelsk::TileSheet sheet("DemoSheet.png", sf::Vector2i(64,64), sf::Vector2i(3,1), 3);
	sheet.LoadTexture();

	//RunnerLevel _level(sf::Vector2i(20,10), "TestLevel.dat", sheet);
	//_level.LoadMap();
	nelsk::Level _level;
	_level.LoadFromFile("Level1.tmx");

	sf::Rect<float> r(500,640,1280,640);
	sf::View v(r);
	_level.SetDrawingBounds(r);
	window.setView(v);
    
	//_level.SetDrawingBounds()

	sf::Vector2f moveVec;
	int moveSpeed = 3;

	sf::Clock _clock;
	float _deltaT;
	float fps;
	// App loop
	while(window.isOpen())
	{
		_deltaT = _clock.restart().asSeconds();
		fps = 1.f / _deltaT;

		sf::Event event;

		// Game input handler
		// Loop event stack
		while(window.pollEvent(event))
		{
			// Close window : exit
			if(event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			moveVec.x = 400 * _deltaT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			moveVec.x = -400 * _deltaT;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			moveVec.y = 400 * _deltaT;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			moveVec.y = -400 *_deltaT;

		//nelsk::DebugConsole::Log(moveVec.x + " " + moveVec.y);
		v.move(moveVec);		
		window.setView(v);

		_level.SetDrawingBounds(GetViewportRect(v));
		window.clear();
		_level.Draw(window);
		
		// Draw sprites to render frame
		window.display();
		moveVec.x = 0; moveVec.y = 0;
	}
	return EXIT_SUCCESS;
}

sf::Rect<float> GetViewportRect(sf::View& v)
{
	return sf::Rect<float>(
		v.getCenter().x - (v.getSize().x / 2),
		v.getCenter().y - (v.getSize().y / 2),
		v.getSize().x,
		v.getSize().y);
}
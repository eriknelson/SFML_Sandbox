#include "StdAfx.h"
#include <SFML/Graphics.hpp>
#include "level.h"
#include "Engine.h"
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

sf::Rect<float> GetViewportRect(sf::View& v)
{
	return sf::Rect<float>(
		v.getCenter().x - (v.getSize().x / 2),
		v.getCenter().y - (v.getSize().y / 2),
		v.getSize().x,
		v.getSize().y);
}


int main()
{
	boost::scoped_ptr<nelsk::Engine> engine(new nelsk::Engine);
	try
	{
		engine->StartGame();
	}
	catch(char* e)
	{
		EZLOGGERVL(axter::log_always) << "Critical Error caught in main: " << e << std::endl;
	}

	return EXIT_SUCCESS;
	//TIGHT_LOGGING;

	//sf::RenderWindow window(sf::VideoMode(1280,640), "Sandbox!");
	//window.setFramerateLimit(30);

	//nelsk::Level _level;
	//_level.LoadFromFile("Level1.tmx");

	//sf::Rect<float> r(500,640,1280,640);
	//sf::View v(r);
	////_level.SetDrawingBounds(r);
	//window.setView(v);
	//sf::Vector2f moveVec;

	//sf::Font myFont;
	//myFont.loadFromFile("36daysag.ttf");
	//sf::Text fpsString("FPS: ", myFont, 12);
	//fpsString.setPosition(10.0,10.0);

	//sf::Clock _clock;
	//float _deltaT;
	//float fps;
	//
	//while(window.isOpen())
	//{
	//	_deltaT = _clock.restart().asSeconds();
	//	fps = 1.f / _deltaT;
	//	std::string fpsConv = boost::lexical_cast<std::string>(fps);
	//	fpsString.setString("FPS: " + fpsConv);

	//	sf::Event event;

	//	while(window.pollEvent(event))
	//	{
	//		if(event.type == sf::Event::Closed)
	//			window.close();
	//	}
	//	
	//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//		moveVec.x = 400 * _deltaT;
	//	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//		moveVec.x = -400 * _deltaT;

	//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//		moveVec.y = 400 * _deltaT;
	//	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//		moveVec.y = -400 *_deltaT;

	//	v.move(moveVec);
	//	fpsString.setPosition(v.getCenter().x, v.getCenter().y);
	//	window.setView(v);

	//	window.clear();
	//	_level.Draw(window);
	//	window.draw(fpsString);
	//	// Draw sprites to render frame
	//	window.display();
	//	moveVec.x = 0; moveVec.y = 0;
}
#include "StdAfx.h"
#include <SFML/Graphics.hpp>
#include "level.h"
#include "Engine.h"
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
		NELSK_LOG_ERROR << "Critical Error caught in main: " << e << std::endl;
	}

	return EXIT_SUCCESS;
}
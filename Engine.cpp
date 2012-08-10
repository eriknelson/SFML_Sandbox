#include "StdAfx.h"
#include "Engine.h"
using namespace nelsk;

Engine::Engine()
{
}


Engine::~Engine()
{
}

bool Engine::Init()
{
	DEBUG_LOGGING_LEVEL;

	window.reset(new sf::RenderWindow(sf::VideoMode(1200,1024,32),"SFML_Sandbox"));

	if(!window)
		return false;
	return true;
}

void Engine::Draw()
{
	window->clear();

	window->display();
}

void Engine::ProcessInput()
{
	sf::Event evt;
	// Loop through all window events
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed)
			window->close();
	}
}

void Engine::Update()
{

}

void Engine::Mainloop()
{
	// Loop until our window is closed
	while(window->isOpen())
	{
		ProcessInput();
		Update();
		Draw();
	}
}

void Engine::StartGame()
{
	if(!Init())
	{
		EZLOGGERVL(axter::log_always) << "CATASTRPHIC: Could not initialize game engine. Exiting.";
		throw "Could not initialize engine";
	}
	Mainloop();
}

TileSheetManager& Engine::GetTileSheetManager() const
{
	return *_tileSheetManager;
}

GameObjectManager& Engine::GetGameObjectManager() const
{
	return *_gameObjectManager;
}

PhysicsManager& Engine::GetPhysicsManager() const
{
	return *_physicsManager;
}

InputManager& Engine::GetInputManager() const
{
	return *_inputManager;
}
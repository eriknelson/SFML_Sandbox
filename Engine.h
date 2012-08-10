#pragma once
#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>
#include "Managers.h"

namespace nelsk
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void StartGame();

		TileSheetManager& GetTileSheetManager() const;
		GameObjectManager& GetGameObjectManager() const;
		PhysicsManager& GetPhysicsManager() const;
		InputManager& GetInputManager() const;

	private:
		boost::scoped_ptr<sf::RenderWindow> window;
		boost::scoped_ptr<TileSheetManager> _tileSheetManager;
		boost::scoped_ptr<GameObjectManager> _gameObjectManager;
		boost::scoped_ptr<PhysicsManager> _physicsManager;
		boost::scoped_ptr<InputManager> _inputManager;

		sf::Sprite _mySprite;

		// Initializes the engine
		bool Init();
		// Main game loop
		void Mainloop();
		// Renders one frame
		void Draw();
		// processes user input
		void ProcessInput();
		// Updates all Engine internals
		void Update();

		
	};
}


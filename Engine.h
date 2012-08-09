#pragma once
#include <SFML/Graphics.hpp>
#include <boost/scoped_ptr.hpp>
#include "TextureManager.h"

namespace nelsk
{
	class Engine
	{
	private:
		boost::scoped_ptr<sf::RenderWindow> window;
		TextureManager _textureManager;
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

	public:
		Engine();
		~Engine();

		void StartGame();
	};
}


#pragma once

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "Managers.h"

namespace nelsk
{
	class Engine;

	class Level
	{
	public:
		Level(boost::weak_ptr<Engine> engine);
		~Level();
		
		virtual void Update()=0;
		virtual void Draw()=0;
		
	private:
		boost::weak_ptr<Engine> _engine;
		TileSheetManager& _tileSheetManager;
		GameObjectManager& _gameObjectManager;
		PhysicsManager& _physicsManager;
		InputManager& _InputManager;
	};
}

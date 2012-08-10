#include "Level.h"
#include "Engine.h"

using namespace nelsk;

Level::Level(boost::weak_ptr<Engine> engine) : 
_tileSheetManager(engine.lock()->GetTileSheetManager()),
	_gameObjectManager(engine.lock()->GetGameObjectManager()),
	_physicsManager(engine.lock()->GetPhysicsManager()),
	_InputManager(engine.lock()->GetInputManager()),
	_engine(engine)
{

}


Level::~Level(void)
{
}

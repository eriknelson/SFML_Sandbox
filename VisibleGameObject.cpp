#include "StdAfx.h"
#include "VisibleGameObject.h"
#include <time.h>
#include <iostream>

using namespace nelsk;

VisibleGameObject::VisibleGameObject( TileSheet& tileSheet, TileIndexRange range, bool isAnimating )
	: _tileSheet(tileSheet), _tileIndexRange(range), _currentTileIndex(_tileIndexRange.firstIndex),
	_isAnimating(isAnimating)
{
	_sprite.setTexture(_tileSheet.GetTexture());
	_sprite.setTextureRect(_tileSheet.GetSubRect(_currentTileIndex));
	_clock.restart();
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow)
{
	renderWindow.draw(_sprite);

	if(_isAnimating)
	{
		if(_clock.getElapsedTime().asSeconds() < .2)
			return;
		else
		{
			_currentTileIndex == _tileIndexRange.lastIndex
				? _currentTileIndex = _tileIndexRange.firstIndex
				: _currentTileIndex++;
			_clock.restart();
		}
	}
}

void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	return _sprite.getPosition();
}

const sf::Sprite& VisibleGameObject::GetSprite() const
{
	return _sprite;
}

float VisibleGameObject::GetSpriteHeight() const
{
	return _sprite.getGlobalBounds().height;
}

float VisibleGameObject::GetSpriteWidth() const
{
	return _sprite.getGlobalBounds().width;
}


#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TileSheet.h"

namespace nelsk
{
	struct TileIndexRange
	{
		TileIndexRange(int first, int last) : firstIndex(first), lastIndex(last) {}
		int firstIndex;
		int lastIndex;
	};

	class VisibleGameObject
	{
	public:
		VisibleGameObject(TileSheet& tileSheet, TileIndexRange range, bool isAnimating);
		~VisibleGameObject(void);

		virtual void Draw(sf::RenderWindow &window);
		virtual void Update(float elapsedTime);

		virtual void SetPosition(float x, float y);
		virtual sf::Vector2f GetPosition() const;

		virtual float GetSpriteWidth() const;
		virtual float GetSpriteHeight() const;

	protected:
		const sf::Sprite& GetSprite() const;
		TileIndexRange GetTileIndexRange() const;
		bool IsAnimating() const;
		void StartAnimating() const;
		void StopAnimating() const;
	private:
		sf::Sprite _sprite;

		// Spritesheet properties for possible animation
		TileSheet& _tileSheet;
		TileIndexRange _tileIndexRange;
		bool _isAnimating;
		int _currentTileIndex;
		sf::Clock _clock;
	};
}
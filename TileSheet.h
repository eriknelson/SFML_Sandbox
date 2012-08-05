#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace nelsk
{
	class TileSheet
	{
	public:
		TileSheet(std::string filename, sf::Vector2i tileDimensionsInPixels,
			sf::Vector2i sheetDimensionsInTiles, int numValidTiles);
		virtual ~TileSheet();
		sf::IntRect GetSubRect(int index) const;
		sf::Texture& GetTexture();
		const sf::Vector2i& GetTileDimensionsInPixels() const;
		const sf::Vector2i& GetSheetDimensionsInTiles() const;
		const int GetNumValidTiles() const;
		bool LoadTexture();
	private:
		bool IsValidIndex(int);
		sf::Vector2i _tileDimensionsInPixels;
		sf::Vector2i _sheetDimensionsInTiles;
		std::string _fileName;
		sf::Texture _texture;
		int _numValidTiles;
	};
}


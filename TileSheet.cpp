#include "StdAfx.h"
#include "TileSheet.h"
#include <iostream>

using namespace nelsk;

TileSheet::TileSheet( std::string filename, sf::Vector2i tileDimensionsInPixels,
	sf::Vector2i sheetDimensionsInTiles, int numValidTiles ) :
	_fileName(filename),
	_tileDimensionsInPixels(tileDimensionsInPixels),
	_sheetDimensionsInTiles(sheetDimensionsInTiles)
{

}


TileSheet::~TileSheet(void)
{
}

bool TileSheet::LoadTexture()
{
	if(_texture.loadFromFile(_fileName))
	{
		std::cout << "DEBUG: Loading image.\n";
		return true;
	}
	else
	{
		std::cout << "WARN: Texture was not, filled with empty texture.";
		return false;
	}
}

sf::IntRect TileSheet::GetSubRect(int index) const
{
	sf::Vector2i tileCoords, upperLeft, bottomRight;
	tileCoords.x = index % _sheetDimensionsInTiles.x;
	tileCoords.y = index / _sheetDimensionsInTiles.x;
	upperLeft.x = tileCoords.x * _tileDimensionsInPixels.x;
	upperLeft.y = tileCoords.y * _tileDimensionsInPixels.y;
	return sf::IntRect(
		upperLeft.x, 
		upperLeft.y, 
		_tileDimensionsInPixels.x,
		_tileDimensionsInPixels.y);
}

const sf::Vector2i& TileSheet::GetTileDimensionsInPixels() const 
{
	return _tileDimensionsInPixels;
}

const sf::Vector2i& TileSheet::GetSheetDimensionsInTiles() const
{
	return _sheetDimensionsInTiles;
}

const int TileSheet::GetNumValidTiles() const
{
	return _numValidTiles;
}

bool TileSheet::IsValidIndex(int index)
{
	return (index >= 0 && index < _numValidTiles);
}

sf::Texture& TileSheet::GetTexture()
{
	return _texture;
}

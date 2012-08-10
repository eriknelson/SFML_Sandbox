#include "StdAfx.h"
#include "TileSheetManager.h"

using namespace nelsk;

TileSheetManager::TileSheetManager()
{
}


TileSheetManager::~TileSheetManager()
{
}

bool TileSheetManager::LoadTexture(std::string textureName, std::string fileName)
{
	sf::Texture* pTex = new sf::Texture;
	try
	{
		pTex->loadFromFile(fileName);
	}
	catch(char* e)
	{
		NELSK_LOG_ERROR << "ERROR: Could not load specified texture: " << 
			fileName << std::endl;
		NELSK_LOG_DEBUG << "Exception text: " << e << std::endl;
		return false;
	}
	boost::shared_ptr<sf::Texture> sp(pTex);
	_textureMap[textureName] = sp;
	return true;
}

bool TileSheetManager::LoadTexture(std::string textureName, const sf::Image& image)
{
	sf::Texture* pTex = new sf::Texture();
	try
	{
		pTex->loadFromImage(image);
	}
	catch(char* e)
	{
		NELSK_LOG_ERROR << "ERROR: Could not load specified texture from image: " << 
			textureName << std::endl;
		NELSK_LOG_DEBUG << "Exception text: " << e << std::endl;
	}
	boost::shared_ptr<sf::Texture> sp(pTex);
	_textureMap[textureName] = sp;
	return true;
}

TileSheetManager::TextureMap_td::const_iterator TileSheetManager::find(std::string textureName) const
{
	return _textureMap.find(textureName);
}

TileSheetManager::TextureMap_td::const_iterator TileSheetManager::end() const
{
	return _textureMap.end();
}
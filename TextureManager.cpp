#include "StdAfx.h"
#include "TextureManager.h"

using namespace nelsk;

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

bool TextureManager::LoadTexture(std::string textureName, std::string fileName)
{
	sf::Texture* pTex = new sf::Texture;
	try
	{
		pTex->loadFromFile(fileName);
	}
	catch(char* e)
	{
		EZLOGGERVL(axter::log_always) << "ERROR: Could not load specified texture: " << 
			fileName << std::endl;
		EZLOGGERVL(axter::log_rarely) << "Exception text: " << e << std::endl;
		return false;
	}
	boost::shared_ptr<sf::Texture> sp(pTex);
	_textureMap[textureName] = sp;
	return true;
}

bool TextureManager::LoadTexture(std::string textureName, const sf::Image& image)
{
	sf::Texture* pTex = new sf::Texture();
	try
	{
		pTex->loadFromImage(image);
	}
	catch(char* e)
	{
		EZLOGGERVL(axter::log_always) << "ERROR: Could not load specified texture from image: " << 
			textureName << std::endl;
		EZLOGGERVL(axter::log_rarely) << "Exception text: " << e << std::endl;
	}
	boost::shared_ptr<sf::Texture> sp(pTex);
	_textureMap[textureName] = sp;
	return true;
}

const boost::shared_ptr<sf::Texture> TextureManager::GetTexture(std::string textureName) const
{
	TextureMap_td::const_iterator tmit = _textureMap.find(textureName);
	if(tmit != _textureMap.end())
		return tmit->second;
	else
	{
		EZLOGGERVL(axter::log_often) << "WARNING: Requested texture not found in TextureManager: " <<
			textureName << std::endl;
		return boost::shared_ptr<sf::Texture>();
	}
}
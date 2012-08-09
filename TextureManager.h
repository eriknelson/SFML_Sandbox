#pragma once
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

namespace nelsk
{
	class TextureManager
	{
	private:
		typedef  std::map< std::string, boost::shared_ptr<sf::Texture> > TextureMap_td;
		 TextureMap_td _textureMap;

	public:
		TextureManager();
		~TextureManager();

		bool LoadTexture(const std::string textureName, const std::string fileName);
		bool LoadTexture(const std::string textureName, const sf::Image& image);

		const boost::shared_ptr<sf::Texture> GetTexture(std::string textureName) const;
	};
}


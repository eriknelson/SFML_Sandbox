#pragma once
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

namespace nelsk
{
	class TileSheetManager
	{
	private:
		typedef  std::map< std::string, boost::shared_ptr<sf::Texture> > TextureMap_td;
		TextureMap_td _textureMap;

	public:
		TileSheetManager();
		~TileSheetManager();

		bool LoadTexture(const std::string textureName, const std::string fileName);
		bool LoadTexture(const std::string textureName, const sf::Image& image);

		TextureMap_td::const_iterator find(std::string textureName) const;
		TextureMap_td::const_iterator end() const;
	};
}


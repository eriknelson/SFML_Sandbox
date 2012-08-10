/*********************************************************************
Quinn Schwab
16/08/2010

SFML Tiled Map Loader

The zlib license has been used to make this software fully compatible
with SFML. See http://www.sfml-dev.org/license.php

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.
*********************************************************************
Erik Nelson
08/09/2012

The following source has been altered from its original state.

*********************************************************************/

#include "StdAfx.h"
#include "LevelLoader.h"

#include <iostream>
#include <tinyxml.h>
#include <boost/lexical_cast.hpp>
using namespace nelsk;


int Object::GetPropertyInt(std::string name)
{
    int i;
    i = atoi(properties[name].c_str());

    return i;
}

float Object::GetPropertyFloat(std::string name)
{
    float f;
    f = strtod(properties[name].c_str(), NULL);

    return f;
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}

LevelLoader::LevelLoader()
{

}

LevelLoader::~LevelLoader()
{
    //dtor
}

bool LevelLoader::LoadFromFile(std::string filename)
{
    TiXmlDocument levelFile(filename.c_str());

    if (!levelFile.LoadFile())
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    //Map element. This is the root element for the whole file.
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    //Set up misc map properties.
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    //Tileset stuff
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    //Tileset image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    if (!tilesetImage.loadFromFile(imagepath))//Load the tileset image
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    tilesetImage.createMaskFromColor(sf::Color(255, 0, 255));
    //tilesetImage.setSmooth(false);
	tilesetTexture.loadFromImage(tilesetImage);
	tilesetTexture.setSmooth(false);

    //Columns and rows (of tileset image)
    int columns = tilesetTexture.getSize().x / tileWidth;
    int rows = tilesetTexture.getSize().y / tileHeight;

    std::vector <sf::Rect<int> > subRects;//container of subrects (to divide the tilesheet image up)

    //tiles/subrects are counted from 0, left to right, top to bottom
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::Rect <int> rect;
            rect.top = y * tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;
			rect.height = tileHeight;
            subRects.push_back(rect);
        }
    }

    //Layers
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer(width, height);
        if (layerElement->Attribute("opacity") != NULL)//check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);//convert the (string) opacity element to float
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;//if the attribute doesnt exist, default to full opacity
        }

        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
			
			if(tileGID != 0) // No tile placed
			{
				int subRectToUse = tileGID - firstTileID;//Work out the subrect ID to 'chop up' the tilesheet image.

				int current = (x + y * width) * 4;

				// Define the position of the 4 points of the current tile
				layer.tiles[current + 0].position = sf::Vector2f((x + 0) * tileWidth, (y + 0) * tileHeight);
				layer.tiles[current + 1].position = sf::Vector2f((x + 0) * tileWidth, (y + 1) * tileHeight);
				layer.tiles[current + 2].position = sf::Vector2f((x + 1) * tileWidth, (y + 1) * tileHeight);
				layer.tiles[current + 3].position = sf::Vector2f((x + 1) * tileWidth, (y + 0) * tileHeight);

				// Define the texture coordinates of the 4 points of the current tile
				int tx = subRectToUse;
				int ty = 0;

				layer.tiles[current + 0].texCoords = sf::Vector2f((tx + 0) * tileWidth, (ty + 0) * tileHeight);
				layer.tiles[current + 1].texCoords = sf::Vector2f((tx + 0) * tileWidth, (ty + 1) * tileHeight);
				layer.tiles[current + 2].texCoords = sf::Vector2f((tx + 1) * tileWidth, (ty + 1) * tileHeight);
				layer.tiles[current + 3].texCoords = sf::Vector2f((tx + 1) * tileWidth, (ty + 0) * tileHeight);
				
			}

            tileElement = tileElement->NextSiblingElement("tile");

            //increment x, y
            x++;
            if (x >= width)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
                if (y >= height)
                {
                    y = 0;
                }
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    //Objects
    TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL)//Check that there is at least one object layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)//loop through object layers
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement)//loop through objects
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int width = atoi(objectElement->Attribute("width"));
                int height = atoi(objectElement->Attribute("height"));

                Object object;
                object.name = objectName;
                object.type = objectType;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = x + width;

                if (objectType == "solid")
                {
                    solidObjects.push_back(objectRect);
                }

                object.rect = objectRect;

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object LevelLoader::GetObject(std::string name)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i].name == name)
        {
            return objects[i];
        }
    }
}

void LevelLoader::SetDrawingBounds(sf::Rect<float> bounds)
{
    drawingBounds = bounds;

    //Adjust the rect so that tiles are drawn just off screen, so you don't see them disappearing.
    drawingBounds.top -= tileHeight;
    drawingBounds.left -= tileWidth;
	drawingBounds.width += tileWidth;
	drawingBounds.height += tileHeight;
}

// TODO: Deprecated. Should be moved to level itself
//void LevelLoader::Draw(sf::RenderWindow &window)
//{
//    for (int layer = 0; layer < layers.size(); layer++)
//    {
//		window.draw(layers[layer].tiles,&tilesetTexture);
//    }
//}

#pragma once
#include "TileSheet.h"
#include "tile.h"

namespace nelsk
{
	class RedTile : public Tile
	{
	public:
		RedTile(TileSheet& tileSheet) : Tile(tileSheet, TileIndexRange(1,1), false, true, true){}
	};
}

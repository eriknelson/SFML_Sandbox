#pragma once
#include "TileSheet.h"
#include "Tile.h"

namespace nelsk
{
	class GreenTile : public Tile
	{
	public:
		GreenTile(TileSheet& tileSheet) : Tile(tileSheet, TileIndexRange(0,0), false, false, true){}
	};
}


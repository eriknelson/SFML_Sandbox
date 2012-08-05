#pragma once
#include "TileSheet.h"
#include <string>
#include "VisibleGameObject.h"
#include "TileSheet.h"

namespace nelsk
{
	class Tile : public VisibleGameObject
	{
	public:
		Tile(TileSheet& sheet, TileIndexRange range, bool isAnimating, bool isLethal, bool isSolid)
			: VisibleGameObject(sheet, range, isAnimating),
		_isLethal(isLethal),
		_isSolid(isSolid){}
		virtual ~Tile(){}

		bool IsLethal() const { return _isLethal; }
		bool IsSolid() const { return _isSolid; }

	private:
		bool _isLethal;
		bool _isSolid;
	};
}
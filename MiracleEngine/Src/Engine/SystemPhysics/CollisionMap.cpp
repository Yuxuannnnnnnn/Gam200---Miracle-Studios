#include "PrecompiledHeaders.h"
#include "CollisionMap.h"

CollisionMap::CollisionMap() :
	_startPosition{}, _totalRow{ 0 }, _totalCol{ 0 }, _mapScale{}, _angle{ 0.f }, _maxTiles{ 0 }, _map{}
{}

CollisionMap::~CollisionMap()
{
	_map.clear();
}


void CollisionMap::AddNewMap(unsigned row, unsigned col, Vector2 scale, Vector3 origin, float angle)
{
	_totalRow = row;
	_totalCol = col;
	_mapScale = scale;
	_startPosition = origin;
	_angle = angle;

	_maxTiles = _totalRow * _totalCol;
}

void CollisionMap::AddNewTile(unsigned row, unsigned col, MapTile tile)
{
	_map.insert(TILE((row * _totalCol + col), tile));
}

unsigned CollisionMap::GetTileOnMap(Vector3 position)
{
	Vector3 mapPosition = position - _startPosition;

	mapPosition /= Vector3{ _mapScale._x,_mapScale._y, 1.f };

	mapPosition.Round();

	return (mapPosition._y * _totalCol + mapPosition._x);
}

TileType CollisionMap::GetTileType(unsigned tileId)
{
	if (tileId > _maxTiles)
		return TileType::NONE;

	MAP::iterator it = _map.find(tileId);

	if (it != _map.end())
		return it->second._type;

	return TileType::NONE;
}

size_t CollisionMap::GetTileUId(unsigned tileId)
{
	if (tileId > _maxTiles)
		return 0;

	MAP::iterator it = _map.find(tileId);

	if (it != _map.end())
		return it->second._uId;

	return 0;
}

unsigned CollisionMap::GetNeighborTile(unsigned tileId, TileDirection dir)
{
	int tempId = (int)tileId;

	switch (dir)
	{
	case TileDirection::TOP_LEFT:
		tempId -= (_totalCol + 1);
		break;
	case TileDirection::TOP_CENTER:
		tempId -= _totalCol;
		break;
	case TileDirection::TOP_RIGHT:
		tempId -= (_totalCol - 1);
		break;
	case TileDirection::CENTER_LEFT:
		tempId -= 1;
		break;
	case TileDirection::CENTER_RIGHT:
		tempId += 1;
		break;
	case TileDirection::BOTTOM_LEFT:
		tempId += (_totalCol - 1);
		break;
	case TileDirection::BOTTOM_CENTER:
		tempId += _totalCol;
		break;
	case TileDirection::BOTTOM_RIGHT:
		tempId += (_totalCol + 1);
		break;
	}

	if (tempId < 0 || tempId > _maxTiles)
		return tileId;

	return (unsigned)tempId;
}
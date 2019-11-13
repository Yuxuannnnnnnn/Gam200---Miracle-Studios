#ifndef _COllISION_MAP_H
#define _COllISION_MAP_H

#include "../MathLib/SYMath.h"

#include <unordered_map>
#include <unordered_set>

enum class TileDirection {
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_LEFT,
	CENTER_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,

	TOTAL_DIR
};

enum class TileType {
	NONE = 0,
	HARD_WALL = 1,

	TOTAL_TILE
};

class MapTile {
public:
	TileType _type;
	size_t _uId;

	MapTile() = delete;
	MapTile(TileType type, size_t uId) : 
		_type{ type }, _uId{ uId } {}
};



class CollisionMap
{
private:
	typedef std::unordered_map<unsigned, MapTile> MAP;
	typedef std::pair<unsigned, MapTile> TILE;

	Vector3 _startPosition;

	unsigned _totalRow; 
	unsigned _totalCol;

	Vector2 _mapScale;

	float _angle; // not in use

	unsigned _maxTiles; // maximum tile can be in game, by on map row and column


	// tileId caculated by row * total column + col
public:
	MAP _map;

public:
	CollisionMap();
	~CollisionMap();

	void AddNewMap(unsigned row, unsigned col, Vector2 scale, Vector3 origin = Vec3::Vec3Zero, float angle = 0.f);
	void AddNewTile(unsigned row, unsigned col, MapTile tile);
	//void ChangeExistedTile(unsigned row, unsigned col, ColliderTile type);

	unsigned GetTileOnMap(Vector3 position);

	TileType GetTileType(unsigned tileId);
	size_t GetTileUId(unsigned tileId);

	unsigned GetNeighborTile(unsigned tileId, TileDirection dir);
};

#endif

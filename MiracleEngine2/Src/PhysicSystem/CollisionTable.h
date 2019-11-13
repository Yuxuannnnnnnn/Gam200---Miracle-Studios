#ifndef _COllISION_TABLE_H
#define _COllISION_TABLE_H

#include <unordered_map>
#include <unordered_set>

enum class ColliderTag {
	NONE = 0,
	PLAYER = 1,
	BULLET = 2,
	ENEMY = 3,
	TURRET = 4,
	DESTORYABLE_BUILDING = 5,
	BUILDING = 7,
	BULLET_E = 8,
	PICK_UPS = 9,
	EDGES = 10,

	TOTAL_TAG
};

class CollisionTable
{
	typedef std::unordered_map<ColliderTag, std::unordered_set<ColliderTag>> TABLE;
	typedef std::pair<ColliderTag, std::unordered_set<ColliderTag>> ROW;

public:
	TABLE _table;

	bool CheckCollisionTable(ColliderTag first, ColliderTag second);

	CollisionTable();
	~CollisionTable();
};

#endif

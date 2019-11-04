#ifndef _COllISION_TABLE_H
#define _COllISION_TABLE_H

#include <unordered_map>
#include <unordered_set>

enum class ColliderTag {
	NONE,
	PLAYER,
	BULLET,
	ENEMY,
	TURRET,
	DESTORYABLE_BUILDING,
	BUILDING,

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

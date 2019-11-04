#include "PrecompiledHeaders.h"
#include "CollisionTable.h"

CollisionTable::CollisionTable()
{
	// PLAYER
	std::unordered_set<ColliderTag> row_player { ColliderTag::ENEMY, ColliderTag::BUILDING,ColliderTag::DESTORYABLE_BUILDING };
	_table.insert(ROW(ColliderTag::PLAYER, row_player));

	// BULLET
	std::unordered_set<ColliderTag> row_bullet{ ColliderTag::ENEMY, ColliderTag::BUILDING, ColliderTag::DESTORYABLE_BUILDING };
	_table.insert(ROW(ColliderTag::BULLET, row_bullet));

	// ENEMY
	std::unordered_set<ColliderTag> row_enemy{ ColliderTag::BULLET, ColliderTag::PLAYER, ColliderTag::BUILDING, ColliderTag::DESTORYABLE_BUILDING };
	_table.insert(ROW(ColliderTag::ENEMY, row_enemy));

	// TURRET
	std::unordered_set<ColliderTag> row_turret{ ColliderTag::ENEMY };
	_table.insert(ROW(ColliderTag::TURRET, row_turret));

	// DESTORYABLE_BUILDING
	std::unordered_set<ColliderTag> row_destoryable_building{ ColliderTag::PLAYER, ColliderTag::BULLET, ColliderTag::ENEMY };
	_table.insert(ROW(ColliderTag::DESTORYABLE_BUILDING, row_destoryable_building));

	// BUILDING
	std::unordered_set<ColliderTag> row_building{ ColliderTag::PLAYER, ColliderTag::BULLET, ColliderTag::ENEMY };
	_table.insert(ROW(ColliderTag::BUILDING, row_building));
}

CollisionTable::~CollisionTable()
{
	_table.clear();
}

bool CollisionTable::CheckCollisionTable(ColliderTag first, ColliderTag second)
{
	if (first == ColliderTag::NONE || second == ColliderTag::NONE)
		return true;

	TABLE::iterator it = _table.find(first);

	if (it != _table.end())
	{
		auto it2 = it->second.find(second);

		if (it2 != it->second.end())
			return true;
	}

	return false;
}
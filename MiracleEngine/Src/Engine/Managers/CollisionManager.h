#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <unordered_map>
#include "HelperClasses/Physic/CollisionTable.h"
#include "HelperClasses/Physic/CollisionMap.h"
#include "Components/Collider2D.h"

#include "Interfaces/IManager.h"

class CollisionManager final : public IManager
{
public:
	std::unordered_map < size_t, Collider2D* > _collider2dList;

	CollisionMap _collisionMap;

private:
	CollisionTable _collisionTable;

public:
	CollisionManager() = default;
	~CollisionManager() {}

	CollisionManager(const CollisionManager& rhs) = delete;
	CollisionManager& operator= (const CollisionManager& rhs) = delete;

	void Update(double dt);
	void Draw();

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);

	static void UpdateColliderData(Collider2D* collider);

private:
	// collision
	void UpdateCollision(double dt);
	void UpdateStaticCollision(double dt);
	int CollisionCheckTile(Collider2D* object, unsigned centerTileId, double dt, unsigned dir = 0, unsigned checked = 0);
	void CollisionCheckResponse(Collider2D* collider1, Collider2D* collider2, double dt);

};

#endif

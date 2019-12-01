///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <unordered_map>
#include "CollisionTable.h"
#include "CollisionMap.h"
#include "GameObjectComponents/PhysicsComponents/Collider2D.h"

#include "IContainer.h"

class CollisionManager final : public IContainer
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

	void AddObject(size_t uId);
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

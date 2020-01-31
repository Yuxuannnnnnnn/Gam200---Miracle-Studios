#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "GameObject/Components/Graphic/TransformComponent.h"
#include "CollisionTable.h"
#include "CollisionMap.h"
#include "GameObject/Components/Physic/ICollider2D.h"

class PhysicsSystem final
{
	std::vector<Collider2D*> _allEnableColliders; // frame based
public:
	PhysicsSystem() = default;
	~PhysicsSystem() {}

	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

	void Update(double dt);
	void Draw();


	// changes
	CollisionMap _collisionMap;
	CollisionTable _collisionTable;

	void UpdateVelocity(double dt);
	void ApplyVelocityToObject(double dt);

	void RigidbodyDraw();

	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);

	void CollisionUpdate(double dt);
	void CollisionDraw();

	static void UpdateColliderData(Collider2D* collider);

	void UpdateCollision(double dt);
	void UpdateStaticCollision(double dt);
	int CollisionCheckTile(Collider2D* object, unsigned centerTileId, double dt, unsigned dir = 0, unsigned checked = 0);
	void CollisionCheckResponse(Collider2D* collider1, Collider2D* collider2, double dt);
};

#endif
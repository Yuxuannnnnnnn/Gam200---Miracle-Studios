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
	PhysicsSystem();
	~PhysicsSystem() {}

	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

	void Update(double dt);
	void Draw();

	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);
	static void UpdateColliderData(Collider2D* collider);

public:
	// changes
	CollisionMap _collisionMap;
	CollisionTable _collisionTable;

private:
	void UpdateVelocity(double dt);
	void ApplyVelocityToObject(double dt);

	void CollisionUpdate(double dt);
	void AllColliderDataUpdate();

	void RigidbodyDraw();
	void AllColliderDraw();

	void DrawBoxCollider2D(Collider2D* obj);
	void DraWCircleCollider2D(Collider2D* obj);
	void DrawEdgeCollider2D(Collider2D* obj);
	
	void UpdateCollision(double dt);
	void UpdateStaticCollision(double dt);
	int CollisionCheckTile(Collider2D* object, unsigned centerTileId, double dt, unsigned dir = 0, unsigned checked = 0);
	void CollisionCheckResponse(Collider2D* collider1, Collider2D* collider2, double dt);
};

#endif
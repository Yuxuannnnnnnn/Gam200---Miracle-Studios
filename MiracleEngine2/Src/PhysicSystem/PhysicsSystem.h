///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

class PhysicsSystem final
{
public:
	std::unordered_map < size_t, RigidBody2D* >	_rigidBody2dList;
	std::unordered_map < size_t, Collider2D* > _collider2dList;

	PhysicsSystem() {};
	//Deletes all gameObjects in the list
	~PhysicsSystem() {};

	void Update(double dt);

	//No replication of class object
	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

private:
	void UpdatePhyiscs(double dt);
	void UpdateCollision(double dt);
	void UpdateTransform(double dt);
	void UpdateEvents();

	void UpdatePicking(double dt);
};

#endif

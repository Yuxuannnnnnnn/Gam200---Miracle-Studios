///////////////////////////////////////////////////////////////////////////////////////
//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _LINE_COLLIDER_2D_H
#define _LINE_COLLIDER_2D_H

#include "Collider2D.h"

// namespace MiracleEngine

class EdgeCollider2D : public Collider2D // renderer
{
public:
	Vector3	m_pt0;
	Vector3	m_pt1;
	Vector3	m_normal;

public:
	EdgeCollider2D(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);


	// Constructor
	EdgeCollider2D(TransformComponent* transform = nullptr);
	virtual ~EdgeCollider2D() {}

	// A copy empty shell object
	EdgeCollider2D(const EdgeCollider2D& rhs);
	//No replication of class object
	EdgeCollider2D& operator= (const EdgeCollider2D& rhs) = delete;

	void Draw();
	void Update();

};

//struct Ray
//{
//	Vector3	m_pt0;
//	Vector3	m_dir;
//};


#endif

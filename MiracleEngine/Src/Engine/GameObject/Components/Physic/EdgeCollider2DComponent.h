///////////////////////////////////////////////////////////////////////////////////////
//
//	EdgeCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _EDGE_COLLIDER_2D_H
#define _EDGE_COLLIDER_2D_H

#include "ICollider2D.h"

class EdgeCollider2D : public Collider2D
{
public:
	Vector3 m_origin;
	Vector3	m_pt0;
	Vector3	m_pt1;
	Vector3	m_normal;

public:
	EdgeCollider2D();
	EdgeCollider2D(const EdgeCollider2D& rhs) = default;
	virtual ~EdgeCollider2D() = default;

	EdgeCollider2D& operator= (const EdgeCollider2D& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

};

//struct Ray
//{
//	Vector3	m_pt0;
//	Vector3	m_dir;
//};


#endif

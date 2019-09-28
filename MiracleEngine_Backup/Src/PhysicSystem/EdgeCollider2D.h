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

	EdgeCollider2D();

	EdgeCollider2D(const Vector3& pos, float scale, float dir);


};

struct Ray
{
	Vector3	m_pt0;
	Vector3	m_dir;
};


#endif

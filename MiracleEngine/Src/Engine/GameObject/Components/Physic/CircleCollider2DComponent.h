///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _CIRCLE_COLLIDER_2D_H
#define _CIRCLE_COLLIDER_2D_H

#include "ICollider2D.h"

class CircleCollider2D : public Collider2D
{
public:
	Vector3	mCenPos;
	float	mRadius;

public:
	CircleCollider2D();
	CircleCollider2D(const CircleCollider2D& rhs) = default;
	virtual ~CircleCollider2D() = default;

	CircleCollider2D& operator=(const CircleCollider2D & rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { return; }


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

};

#endif

///////////////////////////////////////////////////////////////////////////////////////
//
//	SYMath.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "SYMath.h"

float Vec3Distance_LinetoPoint(Vector3 P, Vector3 Q, Vector3 R)
{
	Vector3 v = Q - P;
	Vector3 w = R - P;

	float c1 = w * v;

	if (c1 <= 0)
		return R.Distance(P);

	float c2 = v * v;

	if (c2 <= c1)
		return R.Distance(Q);

	float b = c1 / c2;
	Vector3 S = P + Vector3(b * v._x, b * v._y);

	return R.Distance(S);
}

void Vec3Scale(Vector3& pResult, Vector3& pVec0, float s)
{
	pResult = pVec0 * s;
}

void Vec3Add(Vector3& pResult, Vector3& pVec0, Vector3& pVec1)
{
	pResult = pVec0 + pVec1;
}

void Vec3Zero(Vector3& pResult)
{
	pResult = Vector3{ 0.f,0.f,0.f };
}
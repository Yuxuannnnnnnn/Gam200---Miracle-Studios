#include"EdgeCollider2D.h"
EdgeCollider2D::EdgeCollider2D(const Vector3& pos, float scale, float dir)
{
	//Direction vector
	Vector3 directionVec(cosf(dir), sinf(dir));

	//Get line segment normal
	m_normal.x = directionVec.y;
	m_normal.y = -directionVec.x;

	//Get the p0 and p1
	m_pt0 = pos + directionVec * (scale / 2);
	m_pt1 = pos - directionVec * (scale / 2);
}
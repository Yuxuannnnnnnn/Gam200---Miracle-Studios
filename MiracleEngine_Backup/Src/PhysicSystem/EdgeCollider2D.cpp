#include"EdgeCollider2D.h"

EdgeCollider2D::EdgeCollider2D() :
	m_pt0{},
	m_pt1{},
	m_normal{}
{

}

EdgeCollider2D::EdgeCollider2D(const Vector3& pos, float scale, float dir)
{
	//Direction vector
	Vector3 directionVec(cosf(dir), sinf(dir));
	directionVec.Round();

	std::cout << pos << " : " << directionVec << std::endl;

	//Get line segment normal
	m_normal._x = directionVec._y;
	m_normal._y = -directionVec._x;

	//Get the p0 and p1
	m_pt0 = pos + directionVec * (scale / 2);
	m_pt1 = pos - directionVec * (scale / 2);
}
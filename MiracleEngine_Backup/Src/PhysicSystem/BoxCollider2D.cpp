//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "BoxCollider2D.h"

bool TestCircleVsBox(const CircleCollider2D& cc, const BoxCollider2D& aabb)
{
	BoxCollider2D box = aabb;

	if (box.TestBoxVsPoint(cc.mCenPos))
		return true;

	if (distance(aabb.mMinPos, Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), cc.mCenPos) <= cc.mRadius ||
		distance(Vector3(aabb.mMinPos.X(), aabb.mMaxPos.Y()), aabb.mMaxPos, cc.mCenPos) <= cc.mRadius ||
		distance(aabb.mMaxPos, Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), cc.mCenPos) <= cc.mRadius ||
		distance(Vector3(aabb.mMaxPos.X(), aabb.mMinPos.Y()), aabb.mMinPos, cc.mCenPos) <= cc.mRadius)
		return true;

	return false;
}

BoxCollider2D::BoxCollider2D()
{
}

BoxCollider2D::BoxCollider2D(const Vector3& minPos, const Vector3& maxPos) :
	mMinPos(minPos), mMaxPos(maxPos), mCenPos((mMinPos + mMaxPos) / 2.f)
{
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& _bc) :
	mMinPos(_bc.mMinPos), mMaxPos(_bc.mMaxPos), mCenPos(_bc.mCenPos)
{
}

void BoxCollider2D::Move(const Vector3& vec)
{
	mMinPos += vec;
	mMaxPos += vec;
	mCenPos += vec;
}
bool BoxCollider2D::TestBoxVsPoint(const Vector3& pt)
{
	return (pt.X() >= mMinPos.X() && pt.X() <= mMaxPos.X() &&
		pt.Y() >= mMinPos.Y() && pt.Y() <= mMaxPos.Y());
}

bool BoxCollider2D::TestBoxVsBox(const BoxCollider2D& box)
{
	if (mMaxPos.X() < box.mMinPos.X() || mMaxPos.Y() < box.mMinPos.Y() ||
		mMinPos.X() > box.mMaxPos.X() || mMinPos.Y() > box.mMaxPos.Y())
		return false;

	return true;
}
int BoxCollider2D::BoxBox_Intersection(const BoxCollider2D& circleA,				//CircleA data - input
	const Vector3& velA,														//CircleA velocity - input
	const BoxCollider2D& circleB,													//CircleB data - input
	const Vector3& velB,														//CircleA velocity - input
	Vector3& interPtA,														//Intersection point of CircleA at collision time - output
	Vector3& interPtB,														//Intersection point of CircleB at collision time - output
	float& interTime)														//intersection time - output
{
	(void)circleA;
	(void)velA;
	(void)circleB;
	(void)velB;
	(void)interPtA;
	(void)interPtB;
	(void)interTime;

	return 0;
}



int BoxCollider2D::BoxEdge_Intersection(const BoxCollider2D& circle,			//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime,														//Intersection time ti - output
	bool& checkLineEdges)													//The last parameter is new - for Extra Credits: true = check collision with line segment edges
{
	(void)circle;
	(void)ptEnd;
	(void)lineSeg;
	(void)interPt;
	(void)normalAtCollision;
	(void)interTime;
	(void)checkLineEdges;

	return 0;
}

// Extra credits
int BoxCollider2D::CheckMovingBoxToEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
	const BoxCollider2D& circle,													//Circle data - input
	const Vector3& ptEnd,													//End circle position - input
	const EdgeCollider2D& lineSeg,												//Line segment - input
	Vector3& interPt,														//Intersection position of the circle - output 
	Vector3& normalAtCollision,												//Normal vector at collision time - output
	float& interTime)														//Intersection time ti - output
{
	(void)withinBothLines;
	(void)circle;
	(void)ptEnd;
	(void)lineSeg;
	(void)interPt;
	(void)normalAtCollision;
	(void)interTime;

	return 0;
}

int BoxCollider2D::RayBox_Intersection(const Ray& ray,							//A ray containing the data of the moving dot - input
	const BoxCollider2D& circle,													//Static circle data - input
	float& interTime)														//Intersection time - output
{
	(void)ray;
	(void)circle;
	(void)interTime;

	return 0;
}

// RESPONSE FUNCTIONS
void BoxCollider2D::BoxEdge_Response(const Vector3& ptInter,				//Intersection position of the circle - input
	const Vector3& normal,													//Normal vector of reflection on collision time - input
	Vector3& ptEnd,															//Final position of the circle after reflection - output
	Vector3& reflected)														//Normalized reflection vector direction - output
{
	(void)ptInter;
	(void)normal;
	(void)ptEnd;
	(void)reflected;
}

void BoxCollider2D::BoxPillar_Response(const Vector3& normal,					//Normal vector of reflection on collision time - input
	const float& interTime,													//Intersection time - input
	const Vector3& ptStart,													//Starting position of the circle - input
	const Vector3& ptInter,													//Intersection position of the circle - input
	Vector3& ptEnd,															//Final position of the circle after reflection - output
	Vector3& reflectedVectorNormalized)										//Normalized reflection vector - output
{
	(void)normal;
	(void)interTime;
	(void)ptStart;
	(void)ptInter;
	(void)ptEnd;
	(void)reflectedVectorNormalized;
}

// Extra credits
void BoxCollider2D::BoxBox_Response(Vector3& normal,							//Normal vector of reflection on collision time - input
	const float interTime,													//Intersection time - input
	Vector3& velA,															//Velocity of CircleA - input
	const float& massA,														//Mass of CircleA - input
	Vector3& interPtA,														//Intersection position of circle A at collision time - input
	Vector3& velB,															//Velocity of CircleB - input
	const float& massB,														//Mass of CircleB - input
	Vector3& interPtB,														//Intersection position of circle B at collision time - input
	Vector3& reflectedVectorA,												//Non-Normalized reflected vector of Circle A - output
	Vector3& ptEndA,															//Final position of the circle A after reflection - output
	Vector3& reflectedVectorB,												//Non-Normalized reflected vector of Circle B - output
	Vector3& ptEndB)														//Final position of the circle B after reflection - output
{
	(void)normal;
	(void)interTime;
	(void)velA;
	(void)massA;
	(void)interPtA;
	(void)velB;
	(void)massB;
	(void)interPtB;
	(void)reflectedVectorA;
	(void)ptEndA;
	(void)reflectedVectorB;
	(void)ptEndB;
}
#include "PrecompiledHeaders.h"
#include "Collision.h"

bool BoxVsBoxIntersection(BoxCollider2DComponent* boxA, BoxCollider2DComponent* boxB, CollisionData& data)
{
	return false;
}

bool CircleVsCircleIntersection(CircleCollider2DComponent* circleA, CircleCollider2DComponent* circleB, CollisionData& data)
{
	BCircle c{ circleB->_data._center, circleB->_data._radius + circleA->_data._radius };

	Vector3 relVel = data.velA - data.velB;
	Vector3 relVelNormal = relVel.Normalized();

	if (relVel == Vector3::Vec3Zero)
	{
		if (Collision::CollisionCheck(circleA->_data, circleB->_data))
			return 1;

		return 0;
	}

	Vector3 startToCircle;
	startToCircle = c._center - circleA->_data._center;

	float m = startToCircle.Dot(relVelNormal);
	float n = startToCircle.SquaredLength() - (m * m);
	float r = c._radius * c._radius;

	if (m < 0)
	{
		return 0;
	}
	else if (n > r)
	{
		return 0;
	}
	else
	{
		float s = r - n;
		float tiFirst = (m - sqrt(s)) / relVel.Length();
		float tiSecond = (m + sqrt(s)) / relVel.Length();
		float ti = fminf(tiFirst, tiSecond);
		if (0 <= ti && ti <= 1)
		{
			data.interPtA = circleA->_data._center + (data.velA * ti);
			data.interPtB = circleB->_data._center + (data.velB * ti);
			data.interTime = ti;
			return 1;
		}
		return 0;
	}
}

bool CircleVsBoxIntersection(CircleCollider2DComponent* circle, BoxCollider2DComponent* box, CollisionData& data)
{
	return false;
}

bool CircleVsEdgeIntersection(CircleCollider2DComponent* circle, EdgeCollider2DComponent* edge, CollisionData& data)
{
	//Velocity vector and normal
	Vector3 velocity = data.posNextA - circle->_data._center;
	Vector3 velNormal(-velocity._y, velocity._x);

	//N.P0 - N.Bs
	float dist = edge->_data._normalVec.Dot(edge->_data._startPoint - circle->_data._center);

	if (dist > circle->_data._radius)
	{
		BEdge LNS1{};
		Vector3 temp;
		//R*unit N
		temp = edge->_data._normalVec * circle->_data._radius;
		//p0' and p1'
		LNS1._startPoint = edge->_data._startPoint - temp;
		LNS1._endPoint = edge->_data._endPoint - temp;
		LNS1._normalVec = edge->_data._normalVec;

		//BsP0'
		temp = LNS1._startPoint -  circle->_data._center;
		float tempf = temp.Dot(velNormal);
		//BsP1'
		temp = LNS1._endPoint -  circle->_data._center;
		tempf *= temp.Dot(velNormal);
		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs - R / N.V )
			data.interTime = (edge->_data._normalVec.Dot(edge->_data._startPoint)
				- edge->_data._normalVec.Dot( circle->_data._center) - circle->_data._radius) /
				(edge->_data._normalVec.Dot(velocity));

			if (0 <= data.interTime && data.interTime <= 1)
			{
				data.interPtA =  circle->_data._center + velocity * data.interTime;
				data.normal = -LNS1._normalVec;
				return 1;
			}
			return 0;
		}
		else
			return 0;
	}
	else if (dist < -circle->_data._radius)
	{
		BEdge LNS2{};
		Vector3 temp;
		//R* unit N
		temp = edge->_data._normalVec * circle->_data._radius;
		//P0' and P1'
		LNS2._startPoint = edge->_data._startPoint + temp;
		LNS2._endPoint = edge->_data._endPoint + temp;
		LNS2._normalVec = edge->_data._normalVec;

		//BsP0'
		temp = LNS2._startPoint -  circle->_data._center;
		float tempf = temp.Dot(velNormal);
		//BsP1'
		temp = LNS2._endPoint -  circle->_data._center;
		tempf *= temp.Dot(velNormal);
		if (tempf < 0)
		{

			//Ti = ( N.P0 - N.Bs + R / N.V )
			data.interTime = (edge->_data._normalVec.Dot(edge->_data._startPoint)
				- edge->_data._normalVec.Dot( circle->_data._center) + circle->_data._radius) /
				(edge->_data._normalVec.Dot(velocity));

			if (0 <= data.interTime && data.interTime <= 1)
			{
				data.interPtA =  circle->_data._center + velocity * data.interTime;
				data.normal = LNS2._normalVec;
				return 1;
			}
			return 0;
		}
		else
			return 0;
	}
	else
		return 0;

	return 0;
}

bool BoxVsEdgeIntersection(BoxCollider2DComponent* box, EdgeCollider2DComponent* edge, CollisionData& data)
{
	return false;
}

void BoxVsBoxResponse(CollisionData& data)
{

}

void CircleVsCircleResponse(CollisionData& data)
{
	float p = data.normal.Dot(((data.velA - data.velB) * 2 / (data.massA + data.massB)));

	data.reflectedVecA = data.velA - data.normal * p * data.massB;
	data.reflectedVecB = data.velB + data.normal * p * data.massA;

	float velLengthA;
	velLengthA = data.reflectedVecA.Length();
	float velLengthB;
	velLengthB = data.reflectedVecB.Length();

	Vector3 relVelNormalA = data.reflectedVecA;
	relVelNormalA.Normalize();
	Vector3 relVelNormalB = data.reflectedVecB;
	relVelNormalB.Normalize();

	//Calculate point after reflection
	data.posNextA = data.interPtA + relVelNormalA * (velLengthA * (1.f - data.interTime));
	data.posNextB = data.interPtB + relVelNormalB * (velLengthB * (1.f - data.interTime));


	//Calculation normalized reflection vector
	data.reflectedVecA = data.posNextA - data.interPtA;
	data.reflectedVecA.Normalize();
	data.reflectedVecB = data.posNextB - data.interPtB;
	data.reflectedVecB.Normalize();
}

void CircleVsBoxResponse(CollisionData& data)
{

}

void CircleVsEdgeResponse(CollisionData& data)
{
	//Assuming that the normal passed in is already normalized
	Vector3 penetrateVec;
	penetrateVec = data.posNextA - data.interPtA;

	//Calculate projected vector
	Vector3 projectedVec;
	float projectedDist = 2 * (penetrateVec.Dot(data.normal));
	projectedVec = data.normal * projectedDist;

	//Calculate point after reflection
	data.posNextA = data.interPtA + penetrateVec - projectedVec;

	//Calculation normalized reflection vector
	Vector3 reflectVec;
	reflectVec = data.posNextA - data.interPtA;
	data.reflectedVecA = reflectVec;
	data.reflectedVecA.Normalize();
}

void BoxVsEdgeResponse(CollisionData& data)
{

}
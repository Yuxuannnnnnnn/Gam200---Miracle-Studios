//
//	BoxCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "BoxCollider2D.h"
//#include "GraphicsSystem/DebugRenderer.h"

void BoxCollider2D::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);
}

void BoxCollider2D::Inspect()
{
	IComponentSystem::Inspect();
}

BoxCollider2D::BoxCollider2D(GameObject* parent, size_t uId, IComponentSystem* component) :
	Collider2D(parent, uId, component),
	mMinPos{},
	mMaxPos{},
	mCorner{ {},{},{},{} },
	mAxis{ {},{} },
	mOrigin{},
	mAngle{ 0.f },
	mOnce{ false }
{
	if (component)
	{
		BoxCollider2D* box2DComponent = dynamic_cast<BoxCollider2D*>(component);
		mMinPos = box2DComponent->mMinPos;
		mMaxPos = box2DComponent->mMaxPos;
		mOrigin = box2DComponent->mOrigin;
		mAngle = box2DComponent->mAngle;

		for (int i = 0; i < 4; i++)
			mCorner[i] = box2DComponent->mCorner[i];

		for (int i = 0; i < 2; i++)
			mAxis[i] = box2DComponent->mAxis[i];
	}
}



BoxCollider2D::BoxCollider2D(TransformComponent* transform) :
	mMinPos{}, 
	mMaxPos{}, 
	mCorner{ {},{},{},{} }, 
	mAxis{ {},{} },
	mOrigin{},
	mAngle{ 0.f }, 
	mOnce{ false },
	Collider2D(transform)
{
	_type = (unsigned)ColliderType::BOX_COLLIDER;

	//Vector3 scale = _transform->GetScale();

	//mOrigin = _transform->GetPos();

	//mAngle = _transform->GetRotate();

	////Get bounding rec
	//Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	////Cal boundingRect minimum point
	//mMinPos = mOrigin - (-boundingBox_offset);

	////boundingRect maximum point
	//mMaxPos = mOrigin - boundingBox_offset;

	//Vector3 X(cos(mAngle), sin(mAngle));
	//Vector3 Y(-sin(mAngle), cos(mAngle));

	//X = X * scale._x / 2;
	//Y = Y * scale._y / 2;

	//mCorner[0] = mOrigin - X - Y;
	//mCorner[1] = mOrigin + X - Y;
	//mCorner[2] = mOrigin + X + Y;
	//mCorner[3] = mOrigin - X + Y;

	//ComputeAxes();
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& rhs) :
	mMinPos{ rhs.mMinPos },
	mMaxPos{ rhs.mMaxPos },
	mCorner{ rhs.mCorner[0],rhs.mCorner[1],rhs.mCorner[2],rhs.mCorner[3] },
	mAxis{ rhs.mAxis[0],rhs.mAxis[1] },
	mOrigin{ rhs.mOrigin },
	mAngle{ rhs.mAngle },
	mOnce{ false },
	Collider2D(rhs)
{
	_type = (unsigned)ColliderType::BOX_COLLIDER;
}

void BoxCollider2D::Draw()
{
	DebugRenderer::GetInstance().DrawLine(mCorner[0]._x, mCorner[0]._y, mCorner[1]._x, mCorner[1]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[1]._x, mCorner[1]._y, mCorner[2]._x, mCorner[2]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[2]._x, mCorner[2]._y, mCorner[3]._x, mCorner[3]._y);
	DebugRenderer::GetInstance().DrawLine(mCorner[3]._x, mCorner[3]._y, mCorner[0]._x, mCorner[0]._y);

	DebugRenderer::GetInstance().DrawLine(mOrigin._x, mOrigin._y, mOrigin._x + mAxis[0]._x * 40.f, mOrigin._y + mAxis[0]._y * 40.f);
	DebugRenderer::GetInstance().DrawLine(mOrigin._x, mOrigin._y, mOrigin._x + mAxis[1]._x * 40.f, mOrigin._y + mAxis[1]._y * 40.f);
}

void BoxCollider2D::Update()
{
	_transform = reinterpret_cast<TransformComponent*>(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT));

	Vector3 scale = _transform->GetScale();

	mOrigin = _transform->GetPos();
	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	//Cal boundingRect minimum point
	mMinPos = mOrigin - (-boundingBox_offset);

	//boundingRect maximum point
	mMaxPos = mOrigin - boundingBox_offset;

	if (!mOnce || mAngle != _transform->GetRotate())
	{
		mAngle = _transform->GetRotate();

		Vector3 X(cos(mAngle), sin(mAngle));
		Vector3 Y(-sin(mAngle), cos(mAngle));

		X = X * scale._x / 2;
		Y = Y * scale._y / 2;

		mCorner[0] = mOrigin - X - Y;
		mCorner[1] = mOrigin + X - Y;
		mCorner[2] = mOrigin + X + Y;
		mCorner[3] = mOrigin - X + Y;

		mOnce = true;
	}
	else
	{
		Vector3 oldCenter = (mCorner[0] + mCorner[1] + mCorner[2] + mCorner[3]) / 4;

		Vector3 translation = mOrigin - oldCenter;

		for (int c = 0; c < 4; ++c) {
			mCorner[c] += translation;
		}
	}

	ComputeAxes();
}

void BoxCollider2D::Update(Vector3 pos, Vector3 scale, float angle)
{
	mOrigin = pos;
	//Get bounding rec
	Vector3 boundingBox_offset = { -0.5f * scale._x, -0.5f * scale._y };

	//Cal boundingRect minimum point
	mMinPos = mOrigin - (-boundingBox_offset);

	//boundingRect maximum point
	mMaxPos = mOrigin - boundingBox_offset;

	Vector3 X(cos(angle), sin(angle));
	Vector3 Y(-sin(angle), cos(angle));

	X = X * scale._x / 2;
	Y = Y * scale._y / 2;

	mCorner[0] = mOrigin - X - Y;
	mCorner[1] = mOrigin + X - Y;
	mCorner[2] = mOrigin + X + Y;
	mCorner[3] = mOrigin - X + Y;

	mOnce = true;

	ComputeAxes();
}


void BoxCollider2D::ComputeAxes() {
	mAxis[0] = mCorner[1] - mCorner[0];
	mAxis[1] = mCorner[3] - mCorner[0];

	// Make the length of each axis 1/edge length so we know any
	// dot product must be less than 1 to fall within the edge.

	mAxis[0].Normalize(); // so call x-axis of box
	mAxis[1].Normalize(); // sp call y-axis of box
}

bool BoxCollider2D::TestAABBVsPoint(const Vector3& pt)
{
	return (pt._x >= mMinPos._x && pt._x <= mMaxPos._x &&
		pt._y >= mMinPos._y && pt._y <= mMaxPos._y);
}

bool BoxCollider2D::TestAABBVsAABB(const BoxCollider2D& aabb)
{
	if (mMaxPos._x < aabb.mMinPos._x || mMaxPos._y < aabb.mMinPos._y ||
		mMinPos._x > aabb.mMaxPos._x || mMinPos._y > aabb.mMaxPos._y)
		return false;

	return true;
}

bool BoxCollider2D::TestOOBBVsPoint(const Vector3& pt) const
{
	int oc = TestOutCode(pt);

	if(oc == (int)OutCode_Type::CENTER)
		return true;

	return false;
}

bool BoxCollider2D::TestOOBBVsOOBB(const BoxCollider2D& oobb) const
{
	return TestOverlaps(oobb) && oobb.TestOverlaps(*this);
}

bool BoxCollider2D::TestOverlaps(const BoxCollider2D& oobb) const {

	double t = oobb.mCorner[0].Dot(mAxis[0]);

	// Find the extent of box 2 on axis a
	double tMin = t;
	double tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = oobb.mCorner[c].Dot(mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)mOrigin._x + 1.0) || (tMax < mOrigin._x)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}

	t = oobb.mCorner[0].Dot(mAxis[1]);

	// Find the extent of box 2 on axis a
	tMin = t;
	tMax = t;

	for (int c = 1; c < 4; ++c) {
		t = oobb.mCorner[c].Dot(mAxis[1]);

		if (t < tMin) {
			tMin = t;
		}
		else if (t > tMax) {
			tMax = t;
		}
	}
	// See if [tMin, tMax] intersects [0, 1]
	if ((tMin > (double)mOrigin._y + 1.0) || (tMax < mOrigin._y)) {
		// There was no intersection along this dimension;
		// the boxes cannot possibly overlap.
		return false;
	}
	// There was no dimension along which there is no intersection.
	// Therefore the boxes overlap.
	return true;
}

bool BoxCollider2D::TestBoxVsPoint(const Vector3& pt)
{
	if (mAngle)
		return TestOOBBVsPoint(pt);

	return TestAABBVsPoint(pt);
}

bool BoxCollider2D::TestBoxVsBox(const BoxCollider2D& box)
{
	if (mAngle)
		TestOOBBVsOOBB(box);

	return TestAABBVsAABB(box);
}

int BoxCollider2D::TestOutCode(const Vector3& pt) const
{
	outcode code = 0;

	Vector3 relVel = mOrigin - pt;

	float top = (mOrigin - mCorner[2]).AbsDot(mAxis[0]);
	float right = (mOrigin - mCorner[2]).AbsDot(mAxis[1]);
	float down = -top;
	float left = -right;

	float axis0 = relVel.Dot(mAxis[0]);
	float axis1 = relVel.Dot(mAxis[1]);

	if (axis0 > top)
		code |= TOP;
	else if (axis0 < down)
		code |= BOTTOM;

	if (axis1 > right)
		code |= RIGHT;
	else if (axis1 < left)
		code |= LEFT;

	return (int)code;
}


bool TestCircleVsBox(const CircleCollider2D& circle, const BoxCollider2D& box)
{
	if (box.mAngle)
		return TestCircleVsOOBB(circle, box);

	return TestCircleVsAABB(circle, box);
}

bool TestCircleVsAABB(const CircleCollider2D& circle, const BoxCollider2D& aabb)
{
	BoxCollider2D box = aabb;

	if (box.TestAABBVsPoint(circle.mCenPos))
		return true;

	if (Vec3Distance_LinetoPoint(aabb.mMinPos, Vector3(aabb.mMinPos._x, aabb.mMaxPos._y), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMinPos._x, aabb.mMaxPos._y), aabb.mMaxPos, circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(aabb.mMaxPos, Vector3(aabb.mMaxPos._x, aabb.mMinPos._y), circle.mCenPos) <= circle.mRadius ||
		Vec3Distance_LinetoPoint(Vector3(aabb.mMaxPos._x, aabb.mMinPos._y), aabb.mMinPos, circle.mCenPos) <= circle.mRadius)
		return true;

	return false;
}

bool TestCircleVsOOBB(const CircleCollider2D& circle, const BoxCollider2D& oobb)
{
	return oobb.TestOOBBVsPoint(circle.mCenPos);
}

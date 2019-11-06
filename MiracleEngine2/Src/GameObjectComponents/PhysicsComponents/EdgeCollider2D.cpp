#include "PrecompiledHeaders.h"
#include"EdgeCollider2D.h"
//#include "GraphicsSystem/DebugRenderer.h"



void EdgeCollider2D::SerialiseComponent(Serialiser& document)
{
	Collider2D::SerialiseComponent(document);

}

void EdgeCollider2D::Inspect()
{
	IComponentSystem::Inspect();
}

EdgeCollider2D::EdgeCollider2D(GameObject* parent, size_t uId, IComponentSystem* component) :
	Collider2D(parent, uId, component),
	m_pt0{},
	m_pt1{},
	m_normal{}
{
	if (component)
	{
		EdgeCollider2D* edge2DComponent = dynamic_cast<EdgeCollider2D*>(component);
		m_pt0 = edge2DComponent->m_pt0;
		m_pt1 = edge2DComponent->m_pt1;
		m_normal = edge2DComponent->m_normal;
	}
}
 

EdgeCollider2D::EdgeCollider2D(TransformComponent* transform) :
	m_pt0{},
	m_pt1{},
	m_normal{},
	Collider2D(transform)
{
	_type = (unsigned)ColliderType::LINE_COLLIDER;
	//float dir = _transform->GetRotate();
	//Vector3 pos = _transform->GetPos();
	//Vector3 scale = _transform->GetScale();

	////Direction vector
	//Vector3 directionVec(cosf(dir), sinf(dir));
	//directionVec.Round();

	////Get line segment normal
	//m_normal._x = directionVec._y;
	//m_normal._y = -directionVec._x;

	////Get the p0 and p1
	//m_pt0 = pos + directionVec * (scale / 2);;
	//m_pt1 = pos - directionVec * (scale / 2);;
}

EdgeCollider2D::EdgeCollider2D(const EdgeCollider2D& rhs) :
	m_pt0{ rhs .m_pt0 },
	m_pt1{ rhs.m_pt1 },
	m_normal{ rhs.m_normal },
	Collider2D(rhs)
{
	_type = (unsigned)ColliderType::LINE_COLLIDER;
}

void EdgeCollider2D::Draw()
{
	DebugRenderer::GetInstance().DrawLine(m_pt0._x, m_pt0._y, m_pt1._x, m_pt1._y);
}

void EdgeCollider2D::Update()
{
	_transform = reinterpret_cast<TransformComponent*>(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT));

	float dir = _transform->GetRotate();
	Vector3 pos = _transform->GetPos();
	Vector3 scale = _transform->GetScale();

	//Direction vector
	Vector3 directionVec(cosf(dir), sinf(dir));
	directionVec.Round();

	//Get line segment normal
	m_normal._x = directionVec._y;
	m_normal._y = -directionVec._x;

	//Get the p0 and p1
	m_pt0 = pos + directionVec * (scale / 2);
	m_pt1 = pos - directionVec * (scale / 2);
}
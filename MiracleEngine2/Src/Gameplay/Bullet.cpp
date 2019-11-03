#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Bullet::Update(double dt)
{
	if (_lifeTime > 0.0f)
		_lifeTime -= dt;

	if (_lifeTime < 0.0f && _lifeTime != -666.f)
		DestoryThis();


	// move in direction of rotate
	float rotate = reinterpret_cast<TransformComponent*>(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT))->GetRotate();
	float speed = 10.f;


	Mtx33 temp;
	Mtx33Identity(temp);
	Mtx33RotRad(temp, rotate);
	// multiply by speed
	Vector2 dir = { 0, speed };
	Vector2 result = temp * dir;
	// save info into a Vec3
	Vector3 forceVec(result.x, result.y, 0);

	// do SY addfoce
	Vector3 a = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
	a += forceVec;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->SetPos(a);
}

void Bullet::OnCollision2DTrigger(Collider2D* other)
{
	if (other->GetParentPtr()->Get_typeId() == (unsigned)TypeIdGO::ENEMY)
	{
		DestoryThis();
		Enemy* enemy = reinterpret_cast<Enemy*>(other->GetParentPtr()->GetComponent(ComponentId::LOGIC_COMPONENT, ScriptId::ENEMY));
		enemy->_health--;
	}
}
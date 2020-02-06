#include "PrecompiledHeaders.h"
#include "Script/Boss.h"

Boss::Boss()
{

}
Boss* Boss::Clone()
{
	return new Boss(*this);
}
void Boss::Init()
{

}
void Boss::Update(double dt)
{

}

Vector3& Boss::GetDestinationPos()
{

}
Vector3& Boss::GetPosition()
{

}

void Boss::FSM()
{

}

void Boss::OnCollision2DTrigger(Collider2D* other)
{

}
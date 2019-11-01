#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "Player.h"


void Player::Update(double dt)
{
	updateMovement(dt);
}

void Player::updateMovement(double dt)
{
	Vector3 moveResult; // for throwing resultant movement force to player
 //OTHERS
	//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
	//	_InputStyle = INGAME_PAUSE_ESCAPE;
// SCALE ROTATE
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_E))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() += 0.1f;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_Q))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() -= 0.1f;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_I))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale()._y += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_K))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale()._y -= 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_J))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale()._x += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_L))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale()._x -= 1;
	// MOVEMENT
		// get spd
	float spd = 10.f;;
	//spd *= 30.f;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_W))
		moveResult.Y(spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
		moveResult.Y(-spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
		moveResult.X(spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
		moveResult.X(-spd);
	// add force
		// ((RigidBody2D*)(player->GetComponent(TypeIdComponent::RIGIDBODYCOMPONENT)))->AddForce(moveResult);
	// move by Transform eddit (WRONG WAY, waiting for SY to get his RBody up)
	{
		Vector3 a = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos();
		a += moveResult;
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos() = a;
	}
	// MOUSE
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON))
	{
		GetParentPtr()->SetDestory(true);
	}
}
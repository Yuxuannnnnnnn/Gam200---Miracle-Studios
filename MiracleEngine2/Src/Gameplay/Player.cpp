#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"


void Player::SerialiseComponent(Serialiser& document)
{
	//if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
	//{
	//}
}

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
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() += 0.1f;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() -= 0.1f;
	// MOVEMENT
		// get spd
	float spd = 10.f;;
	//spd *= 30.f;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_W))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(50000);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(-5000);
	// MOUSE
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_MBUTTON))
	{
		EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMY]);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_SPACEBAR))
	{
		// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(10000);
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1))
	{
		// spawn bullet
		GameObject* turret = nullptr;
		turret = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::TURRET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)turret->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	}
}
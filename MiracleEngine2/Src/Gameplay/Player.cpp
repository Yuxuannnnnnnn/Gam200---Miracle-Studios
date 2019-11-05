#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"


void Player::Update(double dt)
{
	updateMovement(dt);
}

void Player::updateMovement(double dt)
{
 //OTHERS
	//if (input->KeyHold(KeyCode KEYB_ESCAPE)) // open pause menu
	//	_InputStyle = INGAME_PAUSE_ESCAPE;
// SCALE
	Vector3 scaleVec = ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetScale();
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_LEFT))
		scaleVec._x -= 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_RIGHT))
		scaleVec._x += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_UP))
		scaleVec._y += 1;
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_DOWN))
		scaleVec._y -= 1;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->SetScale(scaleVec);
// MOVEMENT
	float spd = 5.f * 10000; // get spd
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_W))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(0, 1, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_A))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(-1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_D))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(1, 0, 0), spd);
	if (EngineSystems::GetInstance()._inputSystem->KeyHold(KeyCode::KEYB_S))
		((RigidBody2D*)GetSibilingComponent((unsigned)ComponentId::RIGIDBODY_COMPONENT))->AddForce(Vector3(0, -1, 0), spd);
// MOUSE
	Vector3 aimVector = {
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._x - ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos()._x,
		EngineSystems::GetInstance()._inputSystem->GetMousePos()._y - ((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos()._y,
		0 };
	Vector3 compareVec = { 0, 1, 0 };
	float dot = aimVector._x * compareVec._x + aimVector._y * compareVec._y;
	float det = aimVector._x * compareVec._y - aimVector._y * compareVec._x;
	((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate() = -atan2(det, dot);

	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::MOUSE_LBUTTON))
	{	// spawn bullet
		GameObject* bullet = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BULLET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
		((TransformComponent*)bullet->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetRotate(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetRotate());
		((RigidBody2D*)bullet->GetComponent(ComponentId::RIGIDBODY_COMPONENT))->AddForwardForce(70000);
	}
// NUMBERS
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_1))
	{	// spawn BULLET
		GameObject* turret = nullptr;
		turret = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::TURRET]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)turret->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_2))
	{	// spawn WALL
		GameObject* wall = nullptr;
		wall = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
		// set bullet position & rotation as same as 'parent' obj
		((TransformComponent*)wall->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
			((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	}
	if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_3))
	{	// spawn ENEMY
		GameObject* enemy = nullptr;
		enemy = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMY]);
		((TransformComponent*)enemy->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(Vector3(0, 0, 0));
	}
	//if (EngineSystems::GetInstance()._inputSystem->KeyDown(KeyCode::KEYB_2))
	//{	// spawn SPAWNER
	//	GameObject* spawner = nullptr;
	//	spawner = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::SPAWNER]);
	//	// set bullet position & rotation as same as 'parent' obj
	//	((TransformComponent*)spawner->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(
	//		((TransformComponent*)(GetSibilingComponent((unsigned)ComponentId::TRANSFORM_COMPONENT)))->GetPos());
	//}
}
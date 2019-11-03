#include "PrecompiledHeaders.h"
#include "../Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

void Enemy::Update(double dt)
{
	if (_health <= 0)
		DestoryThis();
}
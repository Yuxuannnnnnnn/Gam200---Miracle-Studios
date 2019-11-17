#pragma once
#include "IColliderHandler.h"
#include "Engine/GameObject.h"

struct Coin : public GameObject, public IColliderHandler {

	void OnCollision2DTrigger(Collider2D* other)
	{
		if (other->_type == ColliderType::CIRCLE_COLLIDER)
		{
			std::cout << "Trigger Coin" << std::endl;
		}
	}

};
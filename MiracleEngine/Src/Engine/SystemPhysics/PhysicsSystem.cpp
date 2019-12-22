///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "PhysicsSystem.h"

void PhysicsSystem::Update(double dt)
{
	_engineSystems._rigidbodyManager->UpdateVelocity(dt);
	_engineSystems._collisionManager->Update(dt);
	_engineSystems._rigidbodyManager->ApplyVelocityToObject(dt);


	for (auto it : MyComponentManger._transformComponents)
	{
		if (it.second->GetParentId() < 1000 || it.second->GetParentPtr()->GetDestory())
			continue;

		if (!it.second->GetEnable())
			continue;


		UpdateTransformMartix(it.second);
	}

}



/////////////////////////////////////////////////////

void PhysicsSystem::Draw()
{
	_engineSystems._rigidbodyManager->Draw();
	_engineSystems._collisionManager->Draw();
}


void PhysicsSystem::UpdateTransformMartix(TransformComponent* transform)
{
	// calculate model matrix = TRS

	Mtx44 translate = Mtx44::CreateTranslation(transform->GetPos());
	Mtx44 rotation = Mtx44::CreateRotationZ(-transform->GetRotate());
	Mtx44 model = translate * rotation *  Mtx44::CreateScale(transform->GetScale());

	transform->SetModel(model.m);

	/*glm::mat4 model = translate * rotate * glm::scale(glm::mat4(1.0f),
		glm::vec3(transformComp->GetScale()._x, transformComp->GetScale()._y, 1.0f));*/
}
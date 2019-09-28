#pragma once
#include "Engine.h"
#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MathLib/SYMath.h"

#include "GraphicsSystem/GraphicsSystem.h"
 #include <limits>
 typedef std::numeric_limits< double > dbl;

void Engine::Init()
{
	_graphicSystem = new GraphicsSystem();
	_frameController = new FrameRateController();
	_inputSystem = new InputSystem();
	_physicSystem = new Physics();
	_inputSystem->Init();
	_frameController->Initialize();
	keypressed = false;

	GameObject* newTop =  new GameObject{ Vector3{0,100}, Vector3{100,1} };
	GameObject* newDown = new GameObject{ Vector3{0,-100}, Vector3{100,1} };
	GameObject* newRight = new GameObject{ Vector3{100,0}, Vector3{1,100} };
	GameObject* newLeft = new GameObject{ Vector3{-100,}, Vector3{1,100} };

	Collider2D* topCollider = _physicSystem->CreateEdgeCollider(newTop->_pos, newTop->_scale._x, 0);
	topCollider->_gameObject = newTop;
	Collider2D* downCollider = _physicSystem->CreateEdgeCollider(newDown->_pos, newDown->_scale._x, 0);
	downCollider->_gameObject = newDown;
	Collider2D* rightCollider = _physicSystem->CreateEdgeCollider(newRight->_pos, newRight->_scale._y, PI/2);
	rightCollider->_gameObject = newRight;
	Collider2D* leftCollider = _physicSystem->CreateEdgeCollider(newLeft->_pos, newLeft->_scale._y, PI/2);
	leftCollider->_gameObject = newLeft;

	objList.push_back(newTop);
	objList.push_back(newDown);
	objList.push_back(newRight);
	objList.push_back(newLeft);
}

void Engine::Update()
{
	std::cout.precision(dbl::max_digits10);
	double deltaTime = _frameController->UpdateFrameTime();
	//std::cout << deltaTime << std::endl;
	//std::cout << _frameController->GetFrameRate() << std::endl;

	_graphicSystem->Update();
	_inputSystem->Update();
	_physicSystem->Update(deltaTime);

	if (_inputSystem->KeyDown(KEYB_A) && !keypressed)
	{
		GameObject* ball = new GameObject{ Vector3{0,0}, Vector3{30,30} };

		RigidBody2D* ballBody = _physicSystem->CreateRigidBody2D();
		ballBody->_velocity = Vector3{ 100.f,0,0.f };
		//ballBody->_appliedForce = Vector3{ 0.f,100.f,0.f };
		ballBody->_static = false;
		ballBody->_gameObject = ball;

		Collider2D* ballCollider = _physicSystem->CreateCircleCollider(ball->_pos, ball->_scale._x / 2);

		ballCollider->_gameObject = ball;
		ballCollider->_body = ballBody;
		


		objList.push_back(ball);
		std::cout << "A pressed !" << std::endl;

		keypressed = true;
	}
	else if (!_inputSystem->KeyDown(KEYB_A) && keypressed)
	{
		keypressed = false;
	}
}

void Engine::Exit()
{
	std::vector<GameObject*>::iterator itr = objList.begin();
	while (itr != objList.end())
		delete *itr++;

	delete _graphicSystem;
}

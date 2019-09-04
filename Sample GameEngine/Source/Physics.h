///////////////////////////////////////////////////////////////////////////////////////
///
///	\file Physics.h
///	Basic 2D iterative impulse physics engine.
///	
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

#include "VMath.h"
#include "Engine.h"
#include "Collision.h"
#include "Body.h"
#include "Resolution.h"

namespace Framework
{

	///Message sent when there is a Collsion between two
	///Body Components.
	class MessageCollide : public Message
	{
	public:
		MessageCollide() : Message(Mid::Collide) {};
		Vec2 ContactNormal;
		float Impulse;
		GOC * CollidedWith;
	};

	///	Basic 2D iterative impulse physics engine system.
	/// Provides the Body Component.
	class Physics : public ISystem
	{
	public:
		Physics();
		virtual void Update(float dt);
		virtual std::string GetName(){return "Physics";}
		void SendMessage(Message * m );
		GOC * TestPoint(Vec2 testPosition);
		void Initialize();
	private:
		void IntegrateBodies(float dt);
		void DetectContacts(float dt);
		void PublishResults();
		void DebugDraw();
		void Step(float dt);
		bool DebugDrawingActive;
		float TimeAccumulation;
		CollsionDatabase Collsion;
		ContactSet Contacts;

	public:
		bool AdvanceStep;
		bool StepModeActive;

		typedef ObjectLinkList<Body>::iterator BodyIterator;
		ObjectLinkList<Body> Bodies;

		//Gravity of the world
		Vec2 Gravity;
		//Max velocity for a physics body
		float MaxVelocity;
		float MaxVelocitySq;

		//See Resolution.cpp for use
		//Position correction tolerance
		float PenetrationEpsilon;
		//Position correction resolve percentage
		float PenetrationResolvePercentage;

	};

	//A global pointer to the Physics system, used to access it globally.
	extern Physics* PHYSICS;
}
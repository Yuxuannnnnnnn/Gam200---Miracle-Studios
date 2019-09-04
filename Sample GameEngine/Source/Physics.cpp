///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.cpp
//	
//	Authors: Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "Physics.h"
#include "DebugDraw.h"
#include "Body.h"
#include "ComponentCreator.h"
#include "Core.h"

namespace Framework
{
	Physics * PHYSICS = NULL;

	Physics::Physics()
	{
		ErrorIf(PHYSICS!=NULL,"Physics already initialized");
		PHYSICS = this;
		DebugDrawingActive = false;
		TimeAccumulation = 0.0f;
		Gravity = Vec2(0,-400);
		MaxVelocity = 1000;
		MaxVelocitySq = MaxVelocity*MaxVelocity;
		PenetrationEpsilon = 0.2f;
		PenetrationResolvePercentage = 0.8f;
		StepModeActive = false;
		AdvanceStep = false;
	}

	void Physics::Initialize()
	{
		RegisterComponent(Body);
	}

	void Physics::IntegrateBodies(float dt)
	{
		for(BodyIterator it=Bodies.begin();it!=Bodies.end();++it)
		{
			it->Integrate(dt);
		}
	}

	void Physics::DetectContacts(float dt)
	{
		BodyIterator bodyA = Bodies.begin();
		BodyIterator lastBody = Bodies.last(); //end - 1
		
		//Broad phase should be added this is N^2
		for(;bodyA!=lastBody;++bodyA)
		{
			BodyIterator bodyB = bodyA;
			++bodyB;
			for(;bodyB!=Bodies.end();++bodyB)
			{
				//Do not collide static bodies with other static bodies
				if( !bodyA->IsStatic || !bodyB->IsStatic )
				{
					Collsion.GenerateContacts( (bodyA)->BodyShape , (bodyA)->Position , (bodyB)->BodyShape , (bodyB)->Position , &Contacts );
				}
			}
		}
	}



	void Physics::PublishResults()
	{
		//Commit all physics updates
		for(BodyIterator it=Bodies.begin();it!=Bodies.end();++it)
		{
			(it)->PublishResults();
		}

		//Broadcast physics collision messages AFTER physics
		//has update the bodies
		for(unsigned i=0;i<Contacts.NumberOfContacts;++i)
		{
			BodyContact* contact = &Contacts.contactArray[i];
			MessageCollide messageCollide;
			messageCollide.ContactNormal = contact->ContactNormal;
			messageCollide.Impulse = contact->ContactImpulse;
			messageCollide.CollidedWith = contact->Bodies[1]->GetOwner();
			contact->Bodies[0]->GetOwner()->SendMessage( &messageCollide );
			if( contact->Bodies[1] != NULL )
			{
				messageCollide.ContactNormal = -contact->ContactNormal;
				messageCollide.Impulse = contact->ContactImpulse;
				messageCollide.CollidedWith = contact->Bodies[0]->GetOwner();
				contact->Bodies[1]->GetOwner()->SendMessage( &messageCollide );
			}
		}
	}

	void Physics::Step(float dt)
	{

		IntegrateBodies(dt);

		Contacts.Reset();

		DetectContacts(dt);

		Contacts.ResolveContacts(dt);

		PublishResults();

	}

	void Physics::Update(float dt)
	{
		const float TimeStep = 1.0f / 60.0f;

		if( !StepModeActive )
		{
			TimeAccumulation += dt;
			TimeAccumulation = min( TimeAccumulation , TimeStep *5 );
			if( TimeAccumulation > TimeStep )
			{
				TimeAccumulation-= TimeStep;
				Step( TimeStep );
			}

		}
		else
		{
			TimeAccumulation = 0.0f;
			if( AdvanceStep )
			{
				Step( TimeStep );
				AdvanceStep = false;
			}
		}

		if( DebugDrawingActive )
			DebugDraw();
	
	}

	GOC * Physics::TestPoint(Vec2 testPosition)
	{
		for(BodyIterator it=Bodies.begin();it!=Bodies.end();++it)
		{
			if( it->BodyShape->TestPoint(testPosition) )
				return it->GetOwner();
		}

		return NULL;
	}

	void Physics::DebugDraw()
	{
		for(BodyIterator it=Bodies.begin();it!=Bodies.end();++it)
		{
			it->DebugDraw();
		}
	}

	void Physics::SendMessage(Message * m )
	{
		if( m->MessageId == Mid::ToggleDebugInfo )
		{
			ToggleDebugDisplay * debugM = (ToggleDebugDisplay*)m;
			DebugDrawingActive = debugM->DebugActive;
		}
	};
}

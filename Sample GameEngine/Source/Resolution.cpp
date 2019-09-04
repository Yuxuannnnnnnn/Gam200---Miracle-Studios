///////////////////////////////////////////////////////////////////////////////////////
//
//	Resolution.cpp
//	
//	Authors: Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "Resolution.h"
#include "Body.h"
#include "Physics.h"
#include <algorithm>

namespace Framework
{

	BodyContact * ContactSet::GetNextContact()
	{
		ErrorIf(NumberOfContacts==MaxContacts,"Maximum number of contacts reached. There is too many colliding objects in the simulation.");
		return &contactArray[NumberOfContacts++];
	}

	void ContactSet::Reset()
	{
		NumberOfContacts = 0;
	}

	float BodyContact::CalculateSeparatingVelocity()
	{
		Vec2 relativeVelocity = Bodies[0]->Velocity - Bodies[1]->Velocity;

		//Get the separating velocity by projecting along the contact normal
		SeperatingVelocity = Dot( relativeVelocity ,  ContactNormal );

		return SeperatingVelocity;
	}

	void ResloveContactVelocity(BodyContact& c,float dt)
	{
		//Find the velocity of the two object along the contact normal
		float separatingVelocity = c.CalculateSeparatingVelocity();

		if(separatingVelocity > 0)
		{
			//The objects are no longer moving towards each other
			//or the contact they are stationary
			c.ContactImpulse = 0;
			return;
		}

		//This velocity of this collision has to be resolved.

		//To model inelastic collision the kinetic energy of the bodies 
		//needs to be reduced.
		//This technique uses the combined restitution to determine what percentage
		//of the energy along the collision normal is conserved
		float newSepVelocity = -separatingVelocity * c.Restitution;

		const bool AccelerationBuildUp = true;
		//When an object is resting on the ground it is constantly falling
		//due to gravity. This acceleration need be removed or objects will
		//jitter on the ground.

		if(AccelerationBuildUp)
		{
			// Check the velocity build-up due to acceleration only
			Vec2 accCausedVelocity = c.Bodies[0]->Acceleration - c.Bodies[1]->Acceleration;
			float accCausedSepVelocity = Dot( accCausedVelocity , c.ContactNormal ) * dt;

			// If we've got a closing velocity due to acceleration build-up,
			// remove it from the new separating velocity
			if (accCausedSepVelocity < 0)
			{
				newSepVelocity += c.Restitution * accCausedSepVelocity;

				// Make sure we haven't removed more than was
				// there to remove.
				if (newSepVelocity < 0) newSepVelocity = 0;
			}
		}

		//What is the total change in velocity for the contact?
		float deltaVelocity = newSepVelocity - separatingVelocity;

		//The delta velocity is applied to each object proportional to inverse
		//mass. So the more massive an object is the less of the change
		//in velocity it will receive.
		float totalInverseMass = c.Bodies[0]->InvMass + c.Bodies[1]->InvMass;

		// Calculate the impulse to apply
		float impulse = deltaVelocity / totalInverseMass;

		c.ContactImpulse = impulse;

		// Find the amount of impulse per unit of inverse mass
		Vec2 impulsePerIMass = c.ContactNormal * impulse;

		// Apply impulses: they are applied in the direction of the contact,
		// and in proportion to inverse mass.
		c.Bodies[0]->Velocity = c.Bodies[0]->Velocity + impulsePerIMass * c.Bodies[0]->InvMass;
		// The other body goes in the opposite direction
		c.Bodies[1]->Velocity = c.Bodies[1]->Velocity + impulsePerIMass * -c.Bodies[1]->InvMass;
	}

	void ResolvePenetration(BodyContact& c,float dt)
	{
		// The movement of each object is based on their inverse mass, so
		// total that.
		float totalInverseMass = c.Bodies[0]->InvMass + c.Bodies[1]->InvMass;

		// Find the amount of penetration resolution per unit of inverse mass
		Vec2 movePerIMass = c.ContactNormal * (c.Penetration / totalInverseMass);

		//If stack stability can be increased by not resolving all the penetrations
		//in one step
		movePerIMass *= PHYSICS->PenetrationResolvePercentage;

		// Calculate the the movement amounts
		c.Movement[0] = movePerIMass * c.Bodies[0]->InvMass;
		c.Movement[1] = movePerIMass * -c.Bodies[1]->InvMass;

		// Apply the penetration resolution
		c.Bodies[0]->Position = c.Bodies[0]->Position + c.Movement[0];
		c.Bodies[1]->Position = c.Bodies[1]->Position + c.Movement[1];
	}


	//Resolve Positions
	void ContactSet::ResolvePositions(float dt)
	{
		//Resolving penetrations is a tricky problem with large stacks. The only real way to get 
		//good results is by considering all contacts at once at solving them together. This method basically 
		//just keeps poking the bodies until the penetrations are below the penetration slop epsilon. 
		//Better solutions involve building contact graphs, shock propagation and constraint based
		//solvers.
		unsigned iterationsRun = 0;
		unsigned maxIterations = NumberOfContacts * 5;
		const float positionEpsilon = PHYSICS->PenetrationEpsilon;

		while(iterationsRun < maxIterations)
		{
			// Find biggest penetration greater than
			//the correction epsilon
			float maxPenetration = positionEpsilon;
			unsigned contactIndex = NumberOfContacts;
			for (unsigned i=0; i<NumberOfContacts; i++)
			{
				if (contactArray[i].Penetration > maxPenetration)
				{
					maxPenetration = contactArray[i].Penetration;
					contactIndex = i;
				}
			}
			if (contactIndex == NumberOfContacts) break;

			//Resolve the penetration
			ResolvePenetration(contactArray[contactIndex],dt);

			// Update the penetrations for all related contacts
			Vec2 * movement = contactArray[contactIndex].Movement;
			for (unsigned i = 0; i < NumberOfContacts; i++)
			{
				if (contactArray[i].Bodies[0] == contactArray[contactIndex].Bodies[0])
					contactArray[i].Penetration -= Dot(movement[0], contactArray[i].ContactNormal);
				else if (contactArray[i].Bodies[0] == contactArray[contactIndex].Bodies[1])
					contactArray[i].Penetration -= Dot(movement[1] , contactArray[i].ContactNormal);
				if (contactArray[i].Bodies[1])
				{
					if (contactArray[i].Bodies[1] == contactArray[contactIndex].Bodies[0])
						contactArray[i].Penetration += Dot( movement[0], contactArray[i].ContactNormal);
					else if (contactArray[i].Bodies[1] == contactArray[contactIndex].Bodies[1])
						contactArray[i].Penetration += Dot( movement[1] , contactArray[i].ContactNormal);
				}
			}
			++iterationsRun;
		}
	}

	//Resolve Velocities of all contacts
	void ContactSet::ResolveVelocities(float dt)
	{
		unsigned iterationsRun = 0;
		unsigned maxIterations = NumberOfContacts * 5;
		while(iterationsRun < maxIterations)
		{
			// Find the contact with the largest closing velocity;
			float maxVelocity = FLT_MAX;
			unsigned contactIndex = NumberOfContacts;
			for (unsigned i = 0; i < NumberOfContacts; i++)
			{
				float sepVel = contactArray[i].CalculateSeparatingVelocity();
				if (sepVel < 0 && sepVel < maxVelocity )
				{
					maxVelocity = sepVel;
					contactIndex = i;
				}
			}

			// Do we have anything worth resolving?
			if (contactIndex == NumberOfContacts) break;

			// Resolve this contact velocity
			ResloveContactVelocity(contactArray[contactIndex],dt);

			++iterationsRun;
		}
	}

	void ContactSet::ResolveContacts(float dt)
	{
		this->ResolvePositions(dt);
		this->ResolveVelocities(dt);
	}



}
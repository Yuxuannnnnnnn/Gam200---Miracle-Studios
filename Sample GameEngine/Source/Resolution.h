///////////////////////////////////////////////////////////////////////////////////////
///
///	\file Resolution.h
///	Iterative impulse collision resolution system.
///	
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Collision.h"

namespace Framework
{
	///A Set of contacts that need to be resolved.
	class ContactSet
	{
	public:
		BodyContact * GetNextContact();
		void ResolveContacts(float dt);
		void Reset();
	private:
		friend class Physics;
		static const int MaxContacts = 1024;
		BodyContact contactArray[MaxContacts];
		unsigned NumberOfContacts;
		void ResolveVelocities(float dt);
		void ResolvePositions(float dt);
	};

}
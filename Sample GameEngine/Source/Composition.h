///////////////////////////////////////////////////////////////////////////////////////
///
///	\file Composition.h 
/// Defines the GameObjectComposition class. 
///
///	Authors: Chris Peters, Benjamin Ellinger 
///	Copyright 2009, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Message.h"
#include "Serialization.h"
#include "Component.h"

namespace Framework
{

	///Game Object Id Type
	typedef unsigned int GOCId;

	///This class is the foundational object for all dynamic objects in the game world. 
	///The GOC is a piece of logical interactive content and the primary mechanism
	///game systems (Graphics, Physics, Etc.) provide functionality and communicate.
	///A GOC can be anything from physical objects like trees, tanks, players to 
	///to logical objects like teams, triggers, or Ais. 
	///GameObject are formed by composing Component objects into the game 
	///object composition. This is usually done by the GameObjectFactory.
	///A Game Object's Lifetime States
	///- Constructed: The game object is constructed but is not initialized. Components
	///	can be added and component data can be adjusted either by serialization or
	///	code.
	///- Initialized: All components are initialized. This is the GOC's normal state.
	///- Dead: The object still exists but it is on the GameObjectFactory's destroy list 
	///and it's GOCId is no longer valid it will be destroyed at the end of the frame.

	//A vector of components pointers is used to store components.
	typedef std::vector<GameComponent*> ComponentArray;

	class GameObjectComposition
	{
	public:

		//Game object factory is the only class allowed to
		//create and destroy game objects.
		friend class GameObjectFactory;

		///Message interface See Message.h
		///Message will be sent to each component on this composition.
		void SendMessage(Message* message);

		///Get a component on this composition by component's typename. 
		///This will return NULL if the component is not found.
		GameComponent* GetComponent(ComponentTypeId typeId);

		///Type safe way of accessing components.
		template<typename type>
		type* GetComponetType(ComponentTypeId typeId);
		
		///Initialize all the components on the composition.
		///See function for details.
		void Initialize();

		///Correctly destroys an object by adding it to the factories destroy list.
		///Object will be destroy the next time the factory updates.
		void Destroy();

		///Add an component used only for dynamic composition construction.
		void AddComponent(ComponentTypeId typeId, GameComponent * component);

		///Get the game object's Id
		GOCId GetId(){return ObjectId;}
	private:

		//Sorted array of components.
		ComponentArray Components;
		typedef ComponentArray::iterator ComponentIt;

		//A unique id for each object used to safely reference 
		//GOCs.
		GOCId ObjectId;

		//The constructor and destructor are private to prevent a user
		//from creating or deleting an object directly they must use the Destroy function

		//FACTORY ONLY: Use CreateEmptyComposition on factory instead
		GameObjectComposition();
		//FACTORY ONLY: Use Destroy instead, factory will call the destructor correctly
		~GameObjectComposition();
	
	};

	//A Short name for GameObjectComposition
	typedef GameObjectComposition GOC;

	//A more advanced type safe way of accessing components.
	//Interface becomes Transform* transform = object->has(Transform);
	template<typename type>
	type * GameObjectComposition::GetComponetType(ComponentTypeId typeId)
	{
		return static_cast<type*>( GetComponent(typeId) );
	}

#define has(type) GetComponetType<type>( CT_##type )

}

///////////////////////////////////////////////////////////////////////////////////////
///
///	\file GameLogic.h
///	Sample game logic for demo.
///	
///	Authors: Benjamin Ellinger, Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////

#pragma once //Makes sure this header is only included once

#include "Graphics.h"
#include "Physics.h"
#include "Engine.h"

namespace Framework
{

	///Sample Demo Component Movement Controller. Used
	///to move objects around the world not under
	///the influence of physics.
	class Controller : public GameComponent
	{
	public:
		Controller * Next;
		Controller * Prev;
		Controller();
		~Controller();
		virtual void Initialize();
		Transform * transform;
		float Speed;
		void Update(float dt);
		virtual void Serialize(ISerializer& stream);
	};

	///Sample Demo Component Explosive Bomb. Explodes on contact after
	///its fuse has counted down.
	class Bomb : public GameComponent
	{
	public:
		int Fuse;
		int SubSpawnCount;
		int SpawnTime;
		virtual void Initialize();
		virtual void Serialize(ISerializer& stream);
		virtual void SendMessage(Message* m);
	};

	///Sample Demo Game Logic
	class GameLogic : public ISystem
	{
	public:	
		GameLogic();
		~GameLogic();
		void Initialize();
		void Update(float timeslice);
		virtual std::string GetName(){return "GameLogic";}
		virtual void SendMessage(Message *);
		GOC * CreateObjectAt(Vec2& position,float rotation,const std::string& file);
		void LoadLevelFile(const std::string& file);
		unsigned GrabbedObjectId;
		Vec2 WorldMousePosition;
	public:
		ObjectLinkList<Controller> Controllers;
	};

	//A global pointer to our game so that it can be accessed from anywhere.
	extern GameLogic* LOGIC;
}



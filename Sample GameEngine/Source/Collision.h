///////////////////////////////////////////////////////////////////////////////////////
///
///	\file Collision.h
///	Provides shapes that are used by Body Component for collision detection.
///	
///	Authors:  Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

#include "VMath.h"
#include "Engine.h"

namespace Framework
{
	class Body;
	
	///Data for a contact between two bodies.
	///Used to resolve world collisions.
	struct BodyContact
	{
		Body* Bodies[2];
		Vec2 Movement[2];
		Vec2 ContactNormal;
		float Penetration;
		float Restitution;
		float FrictionCof;

		float SeperatingVelocity;
		float ContactImpulse;
		float CalculateSeparatingVelocity();
	};

	///Base Shape class
	class Shape
	{
	public:
		enum ShapeId
		{
			SidCircle,
			SidBox,
			SidNumberOfShapes
		};
		ShapeId Id;
		Body * body;
		Shape( ShapeId pid ) : Id(pid) {};
		virtual void Draw()=0;
		virtual bool TestPoint(Vec2)=0;
	};

	///Circle shape.
	class ShapeCircle : public Shape
	{	
	public:
		ShapeCircle() : Shape(SidCircle){};
		float Radius;
		virtual void Draw();
		virtual bool TestPoint(Vec2);
	};

	///Axis Aligned Box Shape
	class ShapeAAB : public Shape
	{
	public:
		ShapeAAB() : Shape(SidBox){};
		Vec2 Extents;
		virtual void Draw();
		virtual bool TestPoint(Vec2);
	};

	class ContactSet;
	typedef bool (*CollisionTest)(Shape*a,Vec2 at,Shape*b,Vec2 bt,ContactSet*c);

	///The collision database provides collision detection between shape types.
	class CollsionDatabase
	{
	public:	
		CollsionDatabase();
		CollisionTest CollsionRegistry[Shape::SidNumberOfShapes][Shape::SidNumberOfShapes];
		bool GenerateContacts(Shape* shapeA,Vec2 poistionA,Shape* shapeB,Vec2 poistionB,ContactSet*c);
		void RegisterCollsionTest(Shape::ShapeId a , Shape::ShapeId b, CollisionTest test);
	};

}
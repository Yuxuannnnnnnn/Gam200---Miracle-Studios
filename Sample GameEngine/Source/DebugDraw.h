///////////////////////////////////////////////////////////////////////////////////////
///
///	\file DebugDraw.h
///	Defines the debug drawer.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////

#pragma once //Makes sure this header is only included once
#include "VMath.h"

namespace Framework
{
	///Global object that provides debug drawing functionality. This enables any system
	///to draw to the screen in a immediate mode method without a dependency on
	///graphics or having to be called in the render loop.
	class Drawer
	{
	public:
		///Set the color of the lines being drawn.
		void SetColor(Vec4 color);
		///Move the draw position.
		void MoveTo(Vec2 newPos);
		///Draw a line between the current position and the provided position.
		void LineTo(Vec2 newPos);
		///Draw a circle using line segments.
		void DrawCircle(Vec2 center, float radius);
		///Draw an axis aligned box.
		void DrawBox(Vec2 center, float size);
		///Draw a line between two points.
		void DrawSegment(Vec2 start, Vec2 end);
		static Drawer Instance;
	private:
		friend class Graphics;
		void Flush();
		struct LineSet
		{
			Vec4 Color;
			unsigned Segments;
		};

		struct LineSegment
		{
			Vec3 A;
			Vec3 B;
		};

		Vec2 WritePosition;
		Vec4 Color;
		unsigned SegmentsDrawn;
		std::vector< LineSet > Sets;
		std::vector< LineSegment > LineSegments;
		void Clear();
	};
}
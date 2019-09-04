///////////////////////////////////////////////////////////////////////////////
///
///	 \file Sprite.h 
///  Defines the Sprite Component.
///
///	 Authors: Chris Peters
///  Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Composition.h"
#include "VMath.h"

namespace Framework
{
	class Transform;

	/// A two-dimensional hardware accelerated sprite class using textures.
	/// Has color, size, and a sprite texture name.
	/// Depends on Transform.
	class Sprite : public GameComponent
	{
	public:	
		//Linked list Nodes
		Sprite * Next;
		Sprite * Prev;
		Sprite();
		~Sprite();
		virtual void Serialize(ISerializer& stream);	
		virtual void Initialize();
		//The height and width of the sprite, in pixels, 
		//which usually matches the texture size.
		Vec2 Size;
		//What texture to use for this sprite
		IDirect3DTexture9*pTexture;
		//What Transform to use for this sprite
		Transform * transform;
		//Name of the sprite asset texture
		std::string SpriteName;
		//Blend color of this sprite
		Vec4 Color;
		//Draw the sprite to the screen
		void Draw(IDirect3DDevice9*pDevice,ID3DXEffect* shader);
	};
}
///////////////////////////////////////////////////////////////////////////////
///
///	\file Graphics.h
/// Defines grahics system.
///	
///	Authors: Benjamin Ellinger, Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

#include "Engine.h"
#include "Sprite.h"

namespace Framework
{	
	//Forward Declaration of Graphics Objects
	class Camera;

	enum PixelShaders
	{
		Basic = 0,
		DebugShader,
		NumberOfShaders
	};

	///A two-dimensional hardware accelerated non fixed function 
	///sprite based graphics system.
	///Provides Sprite and Camera GameComponents.
	class Graphics : public ISystem
	{
	public:
		///Update by rendering the scene
		void Update(float dt);
		virtual std::string GetName(){return "Graphics";}
		//Initialize the Direct3D system.
		Graphics();
		~Graphics();
		//Get a texture asset. Will return null if texture is not loaded
		IDirect3DTexture9* GetTexture(std::string);
		Vec2 ScreenToWorldSpace(Vec2);
		void SetWindwProperties(HWND hWnd,int screenWidth,int screenHeight);
	private:
		void Initialize();
		//Create a vertex buffer for our sprites.
		bool InitGeometry();	
		//Load all the textures for our game.
		void LoadAssets();		
		//Load an individual texture.
		void LoadTexture(const std::string& filename);
		//Set up the default world, view, and projection matrices
		void SetupMatrices();
		//Load a effect file
		bool LoadEffect(int index,const std::string& filename);
		//Draw Debug Data
		void DrawDebugInfo();
		//Draw the world
		void DrawWorld();
		//TODO: Need to handle device lost / device reset
		void DeviceLost();
		void DeviceReset();

	public:
		//The active camera
		Camera*				CurrentCamera;
		HWND HWnd;
		int ScreenWidth;
		int ScreenHeight;

		//Direct3D
		IDirect3D9*				pD3D;
		//Direct3D Device
		IDirect3DDevice9*		pDevice;

		//The quad vertex buffer
		IDirect3DVertexBuffer9*	pQuadVertexBuffer;

		//Stored texture assets
		typedef std::map<std::string,IDirect3DTexture9*> TextureMap;
		TextureMap	Textures;

		//An array for our pixel shaders.
		ID3DXEffect* Shaders[NumberOfShaders];		
		
		//World Projection and view matrices
		Mat4 ProjMatrix;
		Mat4 ViewMatrix;
		Mat4 ViewProjMatrix;

		//Stored copy of the DirectX Presentation Parameters
		D3DPRESENT_PARAMETERS PresentParameters;
		Vec2 SurfaceSize;
		ObjectLinkList<Sprite> SpriteList;
	};

	//A global pointer to the Graphics system, used to access it anywhere.
	extern Graphics* GRAPHICS;
}

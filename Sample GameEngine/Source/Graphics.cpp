///////////////////////////////////////////////////////////////////////////////////////
//
//	Graphics.cpp
//	
//	Authors: Benjamin Ellinger, Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "VertexTypes.h"
#include "FilePath.h"
#include "Camera.h"
#include "ComponentCreator.h"

namespace Framework
{
	//Our global pointer to Graphics.
	Graphics* GRAPHICS = NULL;


	//Set everything to default values.
	Graphics::Graphics()
	{
		pD3D = NULL;
		pDevice = NULL;
		pQuadVertexBuffer = NULL;
		ZeroMemory(Shaders, sizeof(Shaders));

		ErrorIf(GRAPHICS!=NULL,"Graphics already initialized.");
		GRAPHICS = this;
	}

	void Graphics::SetWindwProperties(HWND hWnd,int screenWidth,int screenHeight)
	{
		HWnd = hWnd;
		ScreenWidth = screenWidth;
		ScreenHeight = screenHeight;
	}

	//Initializes Direct3D
	void Graphics::Initialize()
	{
		//Create the D3D object (the parameter is there to make sure the app was built correctly).
		pD3D = Direct3DCreate9(D3D_SDK_VERSION);

		D3DDISPLAYMODE displayMode;
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

		//Set up the structure used to create the D3DDevice.
		ZeroMemory(&PresentParameters, sizeof(PresentParameters));

		D3DPRESENT_PARAMETERS& pp = PresentParameters;
		pp.Windowed = true;						//You can't just set this to FALSE--you'll need to change other stuff as well.
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//Picks the best way to handle back buffers for you, but it means you have draw a full screen every time.
		pp.BackBufferFormat = D3DFMT_UNKNOWN;	//This is for windowed apps, full screen will need to be explicit.
		pp.PresentationInterval  = D3DPRESENT_INTERVAL_DEFAULT;
		pp.BackBufferWidth = ScreenWidth;
		pp.BackBufferHeight = ScreenHeight;

		//Create the D3DDevice
    // IF THIS CALL FAILS:
    //   The most common cause is you are trying to run this on a machine that
    //   does not support hardware vertex processing. At DigiPen, this probably means
    //   your machine does not have a graphics card. Get one, switch machines, or 
    //   alternatively replace the D3DCREATE_HARDWARE_VERTEXPROCESSING constant below 
    //   with D3DCREATE_SOFTWARE_VERTEXPROCESSING.
		DXVerify(pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//The graphics adapter to be used.
									  D3DDEVTYPE_HAL,		//Type of graphics device: Hardware acceleration or software
									  HWnd,					//Window Handle for the device.
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,	//Device behavior: vertex processing (software, mixed, hardware), double precision, etc.
									  &pp,				//The presentation parameters created above.
 									  &pDevice));			//A pointer to the new device.

		//Set our render states (culling, lighting, shading, zbuffers, etc.).
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);			//Turn off culling
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					//Turn off D3D lighting
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//Turn on alpha blending.
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//Use the texture's alpha channel.
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//Use the inverse of the texture's alpha channel.

		SurfaceSize = Vec2((float)ScreenWidth, (float)ScreenHeight);


		RegisterComponent(Sprite);
		RegisterComponent(Camera);

		//FACTORY->AddComponentCreator("Sprite", new ComponentCreatorType<Sprite>() );
		//FACTORY->AddComponentCreator("CameraView", new ComponentCreatorType<CameraView>

		//Load all of our assets (textures and shaders)
		GRAPHICS->LoadAssets();



	}

	//Release Direct3D and do any needed cleanup.
	Graphics::~Graphics()
	{
		//Release all the shaders.
		for (int i = 0; i < NumberOfShaders; i++)
		{
			if (Shaders[i] != NULL) Shaders[i]->Release();
			Shaders[i] = NULL;
		}

		//Release all the texture in the texture
		for( TextureMap::iterator it = Textures.begin();it!=Textures.end();++it)
			it->second->Release();
		
		//Release the vertex buffer.
		SafeRelease(pQuadVertexBuffer);
		//Release the device.
		SafeRelease(pDevice);
		//Release the Direct3D object.
		SafeRelease(pD3D);

	}

	//Render the array of sprites.
	void Graphics::Update(float dt)
	{
		//Clear the backbuffer and fill it with the background color.
		//The first parameter is the number of rectangles you are going to clear--0 means clear the whole thing.
		//The second parameter is the array of rectangle to clear--just set it to NULL.
		//The third parameter says what to clear (in this case, the render target, but could be a zbuffer or stencil buffer).
		//The fourth parameter is the color to fill the target with.
		//The fifth and last parameters are the values to fill the zbuffer and stencil buffer with (if necessary).
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 0.0f, 0);

		//Begin the scene
		if (SUCCEEDED(pDevice->BeginScene()))
		{
			DrawWorld();

			DrawDebugInfo();

			//End the scene
			pDevice->EndScene();
		}
		
		//Present the backbuffer contents to the display.
		//The parameters are: source rect, dest rect, dest window (NULL meaning the default window), and dirty region.
		pDevice->Present(NULL, NULL, NULL, NULL);
	}


	void Graphics::DrawWorld()
	{
		//Setup the world, view, and projection matrices
		SetupMatrices();

		//TODO: Draw background

		//Iterate through the link list of sprite and draw them all
		//TODO: Need Visibility to cull off screen sprites
		ObjectLinkList<Sprite>::iterator it = SpriteList.begin();
		for(;it!=SpriteList.end();++it)
			it->Draw(pDevice, Shaders[Basic]);

	}

	void Graphics::DrawDebugInfo()
	{
		Drawer::Instance.Flush();

		std::vector<Drawer::LineSegment>& Lines = Drawer::Instance.LineSegments;
		std::vector<Drawer::LineSet>& Sets = Drawer::Instance.Sets;
		pDevice->SetFVF(LINE_FVF);

		//Each set is collection of lines that are in the same style (color)
		//so they can be draw together
		unsigned index = 0;
		for( unsigned set=0;set<Sets.size();++set)
		{
			//Draw all the lines in the set
			unsigned numberOfSegments = Sets[set].Segments;
			Vec4 lineColor = Sets[set].Color;
			
			Mat4 worldViewProj = ViewMatrix * ProjMatrix;

			Shaders[DebugShader]->SetMatrix("WorldViewProj", &worldViewProj);
			Shaders[DebugShader]->SetVector("color", &lineColor);
			
			UINT numberOfPasses = 0;
			Shaders[DebugShader]->Begin(&numberOfPasses, 0);
			for(UINT pass=0;pass<numberOfPasses;++pass)
			{
				Shaders[DebugShader]->BeginPass(pass);
				pDevice->DrawPrimitiveUP(D3DPT_LINELIST, numberOfSegments , &Lines[index] , sizeof(Drawer::LineSegment) / 2);
				index+=numberOfSegments;
				Shaders[DebugShader]->EndPass();
			}
			Shaders[DebugShader]->End();
		}

		//Clear all the lines they must be submitted again each frame
		Drawer::Instance.Clear();
	}

	//Set up the world, view, and projection transform matrices.
	void Graphics::SetupMatrices()
	{
		//Set the position of the camera.
		float cameraX = CurrentCamera->transform->Position.x;
		float cameraY = CurrentCamera->transform->Position.y;
		float cameraH = -10.0f;

		//The eye point is the location of the viewer (center of the screen, 10 units away).
		Vec3 eyePoint( cameraX, cameraY, cameraH );
		//The look-at point is where the viewer is looking (center of the screen).
		Vec3 lookAtPoint( cameraX, cameraY, 0.0f );
		//The up vector defines which way is up (the y-direction).
		Vec3 upVector( 0.0f, 1.0f, 0.0f );
		//Create a left-handed view matrix.
		Mat4 matView;
		D3DXMatrixLookAtLH(&matView, &eyePoint, &lookAtPoint, &upVector);
		//Store the view matrix
		ViewMatrix = matView;
		//Create an orthogonal left-handed projection matrix.
		//This will transform everything to the view port with no perspective.
		//The near and far clipping plains are still needed, but not as important.
		Mat4 matProj;
		D3DXMatrixOrthoLH(&matProj, SurfaceSize.x , SurfaceSize.y , 1.0f, 100.0f);
		//Store the projection matrix;
		ProjMatrix = matProj;

		//Store the view projection matrix
		ViewProjMatrix = ViewMatrix * ProjMatrix;
	}

	Vec2 Graphics::ScreenToWorldSpace(Vec2 screenPosition)
	{
		//Convert to normalized screen space 0 to 1
		screenPosition.x /= SurfaceSize.x;
		screenPosition.y /= SurfaceSize.y;

		//Convert to projected space -1 to 1
		screenPosition *= 2.0f;
		screenPosition -= Vec2(1,1);
		screenPosition.y *= -1;

		//Unproject the point by applying the inverse
		//of the ViewProjection matrix
		Mat4 inverseViewProjection;
		float det;
		D3DXMatrixInverse(&inverseViewProjection,&det,&ViewProjMatrix);
		Vec4 worldSpacePosition;
		D3DXVec2Transform(&worldSpacePosition,&screenPosition,&inverseViewProjection);
		return Vec2(worldSpacePosition.x,worldSpacePosition.y);
	}

	//Load all the textures we need.
	void Graphics::LoadAssets()
	{
		//Create the vertex buffer used for sprites
		InitGeometry();

		//Load the textures
		LoadTexture("Assets/Circle.png");
		LoadTexture("Assets/Square.png");
		LoadTexture("Assets/CircleOutline.png");
		LoadTexture("Assets/SquareOutline.png");

		//Load the shaders
		LoadEffect(Basic,"Shaders/Basic.fx");
		LoadEffect(DebugShader,"Shaders/Debug.fx");
		
	}

	//Load a specific texture file and add it to the asset texture map
	void Graphics::LoadTexture(const std::string& filename)
	{
		IDirect3DTexture9* newTexture = NULL;
		FilePath texturefile(filename);

		//Use D3DX to load the texture
		if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, texturefile.FullPath.c_str() , &newTexture)))
			Textures[texturefile.FileName.c_str()] = newTexture;
		else
		{
			ErrorIf(false,"Failed to load texture %s in %s",texturefile.FileName.c_str(),texturefile.FullDirectory.c_str());
		}
	}

	IDirect3DTexture9* Graphics::GetTexture(std::string texture)
	{
		TextureMap::iterator it = Textures.find(texture);
		if( it!= Textures.end())
			return it->second;
		else
			return NULL;
	}

	bool Graphics::LoadEffect(int index,const std::string& filename)
	{
		HRESULT hr;
		LPD3DXBUFFER pBufferErrors = NULL;

		//Set up the shader flags
		#ifdef _DEBUG
			DWORD shaderFlags  = D3DXSHADER_DEBUG;
		#else
			DWORD shaderFlags  = D3DXSHADER_OPTIMIZATION_LEVEL3;//Max speed shaders
		#endif

		//Compile the shaders at load time. 
		hr = D3DXCreateEffectFromFile( pDevice, 
			filename.c_str(),//The shader file to to load
			NULL, //Optional NULL-terminated array of preprocessor macro definitions
			NULL, //Not using include interface
			shaderFlags, //Shader Flags
			NULL, //No shader pool
			&Shaders[index], 
			&pBufferErrors );

		if( FAILED(hr) )
		{
			//If the shader failed to load signal an error
			if( pBufferErrors )
			{
				LPVOID pCompilErrors = pBufferErrors->GetBufferPointer();
				ErrorIf( FAILED(hr) , "Fx Compile Error: %s", (const char*)pCompilErrors );
			}
			else
			{
				ErrorIf( FAILED(hr) , "Failed to load shader: %s" , filename.c_str());
			}
			return false;
		}
		return true;
	}

	//Create the vertex buffer that is used for our sprites.
	bool Graphics::InitGeometry()
	{
		//Create the vertex buffer.
		if (FAILED(pDevice->CreateVertexBuffer(4*sizeof(Vertex2D),	//Size of the vertex buffer in bytes.
												 D3DUSAGE_WRITEONLY,					//Gives usage hints to Direct3D.
												 VERTEX2D_FVF,		//The flexible vertex format for this buffer.
												 D3DPOOL_MANAGED,	//Where the buffer will be placed in memory (in this case, let Direct3D decide).
												 &pQuadVertexBuffer,	//The new vertex buffer.
												 NULL)))			//An unused, reserved parameter.
			return false;

		Vertex2D* pVertices;
		//Lock the vertex buffer so that we can set the vertices.
		//The first parameter is the offset in to the buffer to lock.
		//The second parameter is the amount to lock (0 means lock the whole buffer).
		//The third parameter is a pointer to the actual vertex data.
		//The last parameter is the type of lock (discard all data, read only, etc.).
		if (FAILED(pQuadVertexBuffer->Lock(0, 0, (void**)&pVertices, 0)))
			return false;

		//Set the four vertices, each of which is the corner of a square.
		//The square is 1 unit long on each side, and centered on 0,0.
		//The order of the vertices is important.
		//The tu and tv values are the x and y coordinates to map the texture to.
		//They range from 0.0 to 1.0, which 1.0 being the height or width of the texture.
		pVertices[0].Position = Vec3(-0.5f, -0.5f, 0.0f);
		pVertices[0].tu       = 0.0f;
		pVertices[0].tv       = 1.0f;
		pVertices[1].Position = Vec3(-0.5f, 0.5f, 0.0f);
		pVertices[1].tu       = 0.0f;
		pVertices[1].tv       = 0.0f;
		pVertices[2].Position = Vec3( 0.5f, -0.5f, 0.0f);
		pVertices[2].tu       = 1.0f;
		pVertices[2].tv       = 1.0f;
		pVertices[3].Position = Vec3( 0.5f, 0.5f, 0.0f);
		pVertices[3].tu       = 1.0f;
		pVertices[3].tv       = 0.0f;

		//Unlock the vertex buffer so we can actually use it.
		pQuadVertexBuffer->Unlock();

		return true;
	}
}

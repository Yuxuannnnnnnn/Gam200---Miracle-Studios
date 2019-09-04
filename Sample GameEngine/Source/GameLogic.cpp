///////////////////////////////////////////////////////////////////////////////////////
//
//	Game Logic
//	Simple game logic for demo. A good way to approach understand the game sample
//	is to walk through all the code in game logic and follow the execution through
//	the rest of the engine.
//	
//	Authors: Chris Peters, Benjamin Ellinger
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "GameLogic.h"
#include "WindowsSystem.h"
#include "Core.h"
#include "ComponentCreator.h"
#include "Camera.h"
#include "TextSerialization.h"
#include <ctime>

namespace Framework
{
	//Our global pointer to the game.
	GameLogic* LOGIC = NULL;

	void GameLogic::Initialize()
	{
		//Components are explicitly registered in initialize
		RegisterComponent(Transform);
		//This macro expands into FACTORY->AddComponentCreator( "Transform" , new ComponentCreatorType<Transform>()  );

		RegisterComponent(Controller);
		RegisterComponent(Bomb);

		const bool UseLevelFile = true;

		if( UseLevelFile )
		{
			LoadLevelFile("Objects\\TestLevel.txt");
		}
		else
		{
			//The following sections of code show what is looks like to compose the game object
			//in code vs using data driven composition. Normally you will use data driven
			//composition, but there are cases where you might want to do it in code.
			const bool DataDrivenObjects = true;

			//Create the camera
			if(DataDrivenObjects)
			{
				FACTORY->Create( "Objects\\Camera.txt" );
			}
			else
			{
				GOC * camera = FACTORY->CreateEmptyComposition();
				camera->AddComponent( CT_Transform, new Transform() );
				Controller * controller = new Controller();
				controller->Speed = 20.0f;
				camera->AddComponent( CT_Controller , controller );
				camera->AddComponent( CT_Camera , new Camera() );
				camera->Initialize();
			}

			//Create the ground
			if(DataDrivenObjects)
			{
				FACTORY->Create( "Objects\\Ground.txt" );
			}
			else
			{
				GOC * gameObject = FACTORY->CreateEmptyComposition();
				Transform * transform = new Transform();
				transform->Position = Vec2(0,-300);;
				gameObject->AddComponent(CT_Transform , transform );
				Body * body = new Body();
				body->Mass = 0.0f;
				body->Restitution = 0.3f;
				body->Friction = 0.3f;
				ShapeAAB * box = new ShapeAAB();
				box->Extents = Vec2(300,10);
				body->BodyShape = box;		
				gameObject->AddComponent(CT_Body, body );

				Sprite * sprite = new Sprite();
				sprite->SpriteName = "square";
				sprite->Size = Vec2(600,20);
				sprite->Color = Vec4(1,0,0,1);
				gameObject->AddComponent(CT_Sprite , sprite );

				gameObject->Initialize();
			}

			//Create the two bumper walls
			FACTORY->Create( "Objects\\WallLeft.txt" );
			FACTORY->Create( "Objects\\WallRight.txt" );
			
		}

	}

	GameLogic::GameLogic()
	{	
		//Safe Id reference of the object the user has grabbed
		GrabbedObjectId = 0;

		//Set up the global pointer
		ErrorIf(LOGIC!=NULL,"Logic already initialized");
		LOGIC = this;

	}

	GameLogic::~GameLogic()
	{
	}

	void GameLogic::SendMessage(Message * m )
	{
		switch( m->MessageId )
		{
			// The user has pressed a (letter/number) key, we may respond by creating
			// a specific object based on the key pressed.
			case Mid::CharacterKey:
				{
					// Cast to the derived message type
					MessageCharacterKey * key = (MessageCharacterKey*)m;

					//When different keys are pressed create different objects
					std::string ObjectToCreate;

					if( key->character == '1' )					
						ObjectToCreate = "Objects\\Ball.txt";
					else if( key->character == '2' )
						ObjectToCreate = "Objects\\Box.txt";
					else if( key->character == '3' )
						ObjectToCreate = "Objects\\Bomb.txt";

					if( !ObjectToCreate.empty() )
						CreateObjectAt(WorldMousePosition,0,ObjectToCreate);

					//Enable Physics Debugging
					if( key->character == ' ' )
						PHYSICS->AdvanceStep = true;
					if( key->character == ' ' && IsShiftHeld() )
						PHYSICS->StepModeActive = !PHYSICS->StepModeActive;

					if( key->character == 'd' )
					{
						ToggleDebugDisplay debugMessage( true );
						CORE->BroadcastMessage( &debugMessage );
					}

					if( key->character == 'f' )
					{
						ToggleDebugDisplay debugMessage( false );
						CORE->BroadcastMessage( &debugMessage );
					}
					break;
				}
			case Mid::FileDrop:
				{
					FileDrop * drop = (FileDrop*)m;
					LoadLevelFile(drop->FileName);
					break;
				}
			case Mid::MouseMove:
				{
					//The mouse has moved, update the mouse's world position
					MouseMove * mouseMove = (MouseMove*)m;
					WorldMousePosition = GRAPHICS->ScreenToWorldSpace(mouseMove->MousePosition);
					break;
				}
			case Mid::MouseButton:
				{
					MouseButton * mouse = (MouseButton*)m;
					//Update the world mouse position
					WorldMousePosition = GRAPHICS->ScreenToWorldSpace(mouse->MousePosition);
					
					if(mouse->ButtonIsPressed)
					{
						if( mouse->MouseButtonIndex == MouseButton::LeftMouse )
						{
							//On left click attempt to grad a object at the mouse cursor
							if( GOC * goc = PHYSICS->TestPoint( WorldMousePosition ) )
								GrabbedObjectId = goc->GetId();
						}
						else if( mouse->MouseButtonIndex == MouseButton::RightMouse )
						{
							//On right click destroy the object at the mouse cursor
							GOC * goc = PHYSICS->TestPoint( WorldMousePosition );
							if( goc ) 
								goc->Destroy();
						}
					}
					else
					{
						//If the mouse has been release let go of the grabbed object
						GrabbedObjectId = 0;
					}
					break;
				}
		}

	};

	void GameLogic::Update(float dt)
	{
		ObjectLinkList<Controller>::iterator it = Controllers.begin();
		for(;it!=Controllers.end();++it)
			it->Update(dt);

		if( GOC * grabbedObject = FACTORY->GetObjectWithId(GrabbedObjectId))
		{
			Body * body = grabbedObject->has(Body);
			if( IsShiftHeld() )
			{
				//Hard set or Teleport the object
				body->SetPosition(WorldMousePosition);
				body->SetVelocity(Vec2(0,0));
			}
			else
			{
				//Shove the object around
				body->AddForce( (WorldMousePosition - body->Position) * 50 );
			}
		}
	}
	GOC * GameLogic::CreateObjectAt(Vec2& position,float rotation,const std::string& file)
	{
		//This is an example of using some data out of data file using
		//serialization and then override fields before the object
		//is initialized.

		//Build and serialize the object with data from the file
		GOC * newObject = FACTORY->BuildAndSerialize(file);
		//Get the transform and adjust the position
		Transform * transform = newObject->has(Transform);
		transform->Position = position;
		transform->Rotation = rotation;

		//Initialize the composition
		newObject->Initialize();

		return newObject;
	}

	void GameLogic::LoadLevelFile(const std::string& filename)
	{
		TextSerializer stream;
		bool fileOpened = stream.Open(filename);
		ErrorIf( !fileOpened , "Could not open file %s. File does not exist or is protected." , filename.c_str() );

		std::string objectArchetype;
		Vec2 objectPosition;
		float objectRotation;

		while(stream.IsGood())
		{
			StreamRead(stream,objectArchetype);
			StreamRead(stream,objectPosition);
			StreamRead(stream,objectRotation);
			CreateObjectAt(objectPosition,objectRotation,"Objects\\" + objectArchetype);
		}
	}

	void Bomb::Initialize()
	{
		SpawnTime = timeGetTime();
	}

	void Bomb::Serialize(ISerializer& stream)
	{
		StreamRead(stream,Fuse);
		StreamRead(stream,SubSpawnCount);
	}

	void Bomb::SendMessage(Message* m)
	{
		if( m->MessageId == Mid::Collide )
		{			
			if( (int)timeGetTime() - SpawnTime > Fuse )
			{
				GetOwner()->Destroy();
				if( SubSpawnCount > 0 )
				{			
					Transform * transform = GetOwner()->has(Transform);
					for(int i=-1;i<=1;++i)
					{
						Vec2 dir( sin( float(i)*D3DX_PI*0.3f) , cos( float(i)*D3DX_PI*0.3f) );		
						GOC * a = FACTORY->Create("Objects\\Shrapnel.txt");
						Body * bodyA = a->has(Body);
						bodyA->SetVelocity(dir * 120);
						bodyA->SetPosition(transform->Position);
					}
				}
			}
		}
	};

	Controller::Controller()
	{
		//Set the default speed
		Speed = 50.0f;
	}

	Controller::~Controller()
	{
		LOGIC->Controllers.erase( this );
	}

	void Controller::Initialize()
	{ 
		transform = GetOwner()->has(Transform);
		LOGIC->Controllers.push_back( this );
	}

	void Controller::Update(float dt)
	{
		if( IsUpHeld() )
			transform->Position.y -= Speed * dt;
		if( IsDownHeld() )
			transform->Position.y += Speed * dt;
		if( IsLeftHeld() )
			transform->Position.x += Speed * dt;
		if( IsRightHeld() )
			transform->Position.x -= Speed * dt;
	}

	void Controller::Serialize(ISerializer& stream)
	{
		StreamRead(stream,Speed);
	}

}



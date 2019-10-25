#pragma once


#include <Windows.h>

//Dependencies-----------------------------------------
#include <vector>			// STL
#include <iterator>			// stuff
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <comdef.h>			// For _bstr_t class, to convert const wchar_t* to const char*
#include <functional>		// using for funcPtrs

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying
//------------------------------------------------------

//Source files
#include "WindowsSystem/WindowsSystem.h"

#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphicsSystem/MeshManager.h"
#include "GraphicsSystem/RendererSystem.h"
#include "GraphicsSystem/Elementbuffer.h"
#include "GraphicsSystem/Shader.h"

#include "Tools/FileIO.h"

#include "MathLib/SYMath.h"

#include "Engine/Engine.h"

#include "Inputsystem/InputSystem.h"

#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/GraphicComponent.h"
#include "GameObjectComponents/RigidBodyComponent.h"
#include "GameObjectComponents/TransformComponent.h"
#include "GameObjectComponents/PhysicsComponent.h"
#include "GameObjectComponents/LogicComponent.h"
#include "GameObjectComponents/GameObject.h"
#include "GameObjectComponents/GameObjectFactory.h"

#include "Tools/FrameRateController.h"

#include "LogicSystem/LogicSystem.h"
#include "LogicSystem/Script.h"
#include "LogicSystem/AI.h"
#include "LogicSystem/GameState.h"

#include "PhysicSystem/CollisionComponent/Collider2D.h"
#include "PhysicSystem/PhysicComponent/RigidBody2D.h"

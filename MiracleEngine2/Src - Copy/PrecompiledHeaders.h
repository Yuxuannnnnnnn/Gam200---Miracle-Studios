#pragma once

#ifndef PRECOMPILEHEADER_H
#define PRECOMPILEHEADER_H

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
#include <unordered_map>
#include <memory>

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//
//#include "rapidjson.h"		// J
//#include "document.h"		// S
//#include "writer.h"			// O
//#include "stringbuffer.h"	// N
//#include "error/en.h"		// Json error displaying
//------------------------------------------------------

//Source files
#include "WindowsSystem/WindowsSystem.h"

#include "GraphicsSystem/VertexArray.h"
#include "GraphicsSystem/VertexBuffer.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphicsSystem/Elementbuffer.h"
#include "GraphicsSystem/Shader.h"

#include "Tools/FileIO/FileIO.h"

#include "MathLib/SYMath.h"

#include "Engine/Engine.h"
#include "Engine/EngineSystems.h"

#include "Inputsystem/InputSystem.h"

#include "GameObjectFactory/GameObjectFactory.h"
#include "GameObjectFactory/GameObject.h"

#include "GameObjectComponents/IBase.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/GraphicComponents/GraphicComponent.h"
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"
#include "GameObjectComponents/PhysicsComponents/Collider2D.h"
#include "GameObjectComponents/PhysicsComponents/RigidBody2D.h"
#include "GameObjectComponents/LogicComponents/LogicComponent.h"
#include "GameObjectComponents/LogicComponents/DataComponent.h"
#include "GameObjectComponents/LogicComponents/AiComponent.h"
#include "GameObjectComponents/LogicComponents/IScript.h"
#include "GameObjectComponents/AudioComponent.h"

#include "Tools/DebugTools/FrameRateController.h"

#include "Tools/MemoryManager/IMemoryInfo.h"
#include "Tools/MemoryManager/IResourceInfo.h"
#include "Tools/MemoryManager/MemoryManager.h"
#include "Tools/MemoryManager/ObjectAllocator.h"
#include "Tools/MemoryManager/ResourceManager.h"

#include "LogicSystem/LogicSystem.h"
#include "LogicSystem/AiSystem.h"

#include "GameStateManager/GameStateManager.h"

#include "Gameplay/Player.h"

#endif
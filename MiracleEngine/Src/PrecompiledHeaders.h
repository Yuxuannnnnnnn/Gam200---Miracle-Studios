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
#include "Engine.h"
#include "Factory.h"
#include "GlobalContainer.h"

#include "GameObject/ComponentManager.h"
#include "GameObject/Components/PrecompiledComponentHeader.h"

#include "GameObject/IAllocator.h"
#include "GameObject/IComponent.h"

#include "SystemAnimation/Animation.h"
#include "SystemAnimation/Frame.h"

#include "SystemAudio/Sound.h"
#include "SystemAudio/SoundEnum.h"

#include "SystemGraphics/BasicRenderer.h"
#include "SystemGraphics/BatchRenderer.h"
#include "SystemGraphics/BufferLayout.h"
#include "SystemGraphics/DebugBatchRenderer.h"
#include "SystemGraphics/DebugRenderer.h"
#include "SystemGraphics/Elementbuffer.h"
#include "SystemGraphics/FontRenderer.h"
#include "SystemGraphics/FrameBuffer.h"
#include "SystemGraphics/InstancedRenderer.h"
#include "SystemGraphics/QuadMesh.h"
#include "SystemGraphics/Shader.h"
#include "SystemGraphics/Texture2D.h"
#include "SystemGraphics/UIMesh.h"
#include "SystemGraphics/UIRenderer.h"
#include "SystemGraphics/VertexArray.h"
#include "SystemGraphics/VertexBuffer.h"

#include "SystemInput/KeyCode.h"

#include "SystemPhysics/Collision.h"
#include "SystemPhysics/CollisionMap.h"
#include "SystemPhysics/CollisionTable.h"
#include "SystemPhysics/IForce.h"

#include "SystemWindows/Console.h"
#include "SystemWindows/ScreenSize.h"
#include "SystemWindows/Window.h"
#include "SystemWindows/WindowsSystem.h"

#include "Tools/EventHandler/EventHandler.h"
#include "Tools/EventHandler/IColliderHandler.h"
#include "Tools/EventHandler/IMouseHandler.h"
#include "Tools/FileIO/DeSerialiser.h"
#include "Tools/FileIO/FileIO.h"
#include "Tools/FileIO/JsonHeader.h"
#include "Tools/FileIO/Serialiser.h"
#include "Tools/ISingleton.h"
#include "Tools/MathLib/Math.h"
#include "Tools/MathLib/Matrix3x3.h"
#include "Tools/MathLib/Matrix4x4.h"
#include "Tools/MathLib/Vector2.h"
#include "Tools/MathLib/Vector3.h"
#include "Tools/Memory/IMemoryInfo.h"
#include "Tools/Memory/MemoryManager.h"
#include "Tools/Memory/ObjectAllocator.h"
#include "Tools/Resource/IResourceInfo.h"
#include "Tools/Resource/ResourceManager.h"
#include "Tools/Time/FrameRateController.h"
#include "Tools/Resource/ResourceSystem.h"

#endif
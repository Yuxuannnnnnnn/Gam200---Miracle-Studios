#pragma once

#ifndef _PRECOMPILEHEADER_H
#define _PRECOMPILEHEADER_H

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
#include "GlobalContainer.h"
#include "Factory.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "PrecompiledComponentHeaders.h"

#include "Managers/ButtonManager.h"
#include "Managers/CameraManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/RigidBodyManager.h"
#include "Managers/TransformManager.h"
#include "Managers/AnimationManager.h"
#include "Managers/AudioManager.h"
#include "Managers/FontManager.h"

#include "Systems/AnimationSystem.h"
#include "Systems/AudioSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/LogicSystem.h"
#include "Systems/PhysicsSystem.h"

#include "HelperClasses/Animation/Animation.h"
#include "HelperClasses/Animation/Frame.h"

#include "HelperClasses/Audio/Sound.h"
#include "HelperClasses/Audio/SoundEnum.h"
#include "HelperClasses/Audio/SoundManager.h"

#include "HelperClasses/Camera/Camera.h"

#include "HelperClasses/Graphic/AnimatedMesh.h"
#include "HelperClasses/Graphic/BasicRenderer.h"
#include "HelperClasses/Graphic/BatchRenderer.h"
#include "HelperClasses/Graphic/BufferLayout.h"
#include "HelperClasses/Graphic/Elementbuffer.h"
#include "HelperClasses/Graphic/FontRenderer.h"
#include "HelperClasses/Graphic/FragmentShader.h"
#include "HelperClasses/Graphic/FrameBuffer.h"
#include "HelperClasses/Graphic/InstancedRenderer.h"
#include "HelperClasses/Graphic/QuadMesh.h"
#include "HelperClasses/Graphic/Renderer.h"
#include "HelperClasses/Graphic/RenderLayer.h"
#include "HelperClasses/Graphic/RenderObject.h"
#include "HelperClasses/Graphic/Shader.h"
#include "HelperClasses/Graphic/Texture2D.h"
#include "HelperClasses/Graphic/TextureManager.h"
#include "HelperClasses/Graphic/UIManager.h"
#include "HelperClasses/Graphic/UIMesh.h"
#include "HelperClasses/Graphic/UIRenderer.h"
#include "HelperClasses/Graphic/VertexArray.h"
#include "HelperClasses/Graphic/VertexBuffer.h"
#include "HelperClasses/Graphic/VertexShader.h"
#include "HelperClasses/Graphic/DebugBatchRenderer.h"
#include "HelperClasses/Graphic/DebugRenderer.h"

#include "HelperClasses/Input/KeyCode.h"
//#include "HelperClasses/Input/keydef.h"

#include "HelperClasses/Logic/AiSystem.h"
#include "HelperClasses/Logic/LuaScriptTest.h"

#include "HelperClasses/Physic/Collision.h"
#include "HelperClasses/Physic/CollisionMap.h"
#include "HelperClasses/Physic/CollisionTable.h"

#include "Editor/AssetsImguiWindow.h"
#include "Editor/HierarchyImguiWindow.h"
#include "Editor/IBaseImguiWindow.h"
#include "Editor/ImguiSystem.h"
#include "Editor/ImGuizmoManager.h"
#include "Editor/InspectionImguiWindow.h"
#include "Editor/PreFabImguiWindow.h"
#include "Editor/TextureImguiWindow.h"

#include "Tools/Debug/PerformanceUsage.h"

#include "Tools/EventHandler/EventHandler.h"

#include "Tools/FileIO/DeSerialiser.h"
#include "Tools/FileIO/FileIO.h"
#include "Tools/FileIO/JsonHeader.h"
#include "Tools/FileIO/Serialiser.h"

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

#include "PrecompiledScriptType.h"

#endif
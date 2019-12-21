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

#include "Editor/AssetsImguiWindow.h"
#include "Editor/HierarchyImguiWindow.h"
#include "Editor/IBaseImguiWindow.h"
#include "Editor/ImguiSystem.h"
#include "Editor/ImGuizmoManager.h"
#include "Editor/InspectionImguiWindow.h"
#include "Editor/PerformanceUsageWindow.h"
#include "Editor/PreFabImguiWindow.h"
#include "Editor/TextureImguiWindow.h"

#include "GameObject/Components/Graphic/AnimationComponent.h"
#include "GameObject/Components/Graphic/CameraComponent.h"
#include "GameObject/Components/Graphic/FontComponent.h"
#include "GameObject/Components/Graphic/GraphicComponent.h"
#include "GameObject/Components/Graphic/TransformComponent.h"

#include "GameObject/Components/Logic/AiComponent.h"
#include "GameObject/Components/Logic/DataComponent.h"
#include "GameObject/Components/Logic/IScript.h"
#include "GameObject/Components/Logic/LogicComponent.h"
#include "GameObject/Components/Logic/PrecompiledScriptType.h"

#include "GameObject/Components/Physic/BoxCollider2DComponent.h"
#include "GameObject/Components/Physic/CircleCollider2DComponent.h"
#include "GameObject/Components/Physic/EdgeCollider2DComponent.h"
#include "GameObject/Components/Physic/ICollider2D.h"
#include "GameObject/Components/Physic/RigidBody2DComponent.h"

#include "GameObject/Components/AudioComponent.h"
#include "GameObject/Components/ButtonComponent.h"
#include "GameObject/Components/IdentityComponent.h"
#include "GameObject/Components/ImGuizmoComponent.h"
#include "GameObject/Components/PrecompiledComponentHeader.h"
#include "GameObject/Components/TileMapComponent.h"

#include "GameObject/ComponentManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/IAllocator.h"
#include "GameObject/IComponent.h"

#include "SystemAnimation/Animation.h"
#include "SystemAnimation/AnimationSystem.h"
#include "SystemAnimation/Frame.h"

#include "SystemAudio/AudioSystem.h"
#include "SystemAudio/Sound.h"
#include "SystemAudio/SoundEnum.h"
#include "SystemAudio/SoundManager.h"

#include "SystemGraphics/AnimatedMesh.h"
#include "SystemGraphics/BasicRenderer.h"
#include "SystemGraphics/BatchRenderer.h"
#include "SystemGraphics/BufferLayout.h"
#include "SystemGraphics/Camera.h"
#include "SystemGraphics/CameraManager.h"
#include "SystemGraphics/DebugBatchRenderer.h"
#include "SystemGraphics/DebugRenderer.h"
#include "SystemGraphics/Elementbuffer.h"
#include "SystemGraphics/FontRenderer.h"
#include "SystemGraphics/FragmentShader.h"
#include "SystemGraphics/FrameBuffer.h"
#include "SystemGraphics/GraphicsSystem.h"
#include "SystemGraphics/InstancedRenderer.h"
#include "SystemGraphics/QuadMesh.h"
#include "SystemGraphics/Renderer.h"
#include "SystemGraphics/RenderLayer.h"
#include "SystemGraphics/RenderObject.h"
#include "SystemGraphics/Shader.h"
#include "SystemGraphics/Texture2D.h"
#include "SystemGraphics/TextureManager.h"
#include "SystemGraphics/UIManager.h"
#include "SystemGraphics/UIMesh.h"
#include "SystemGraphics/UIRenderer.h"
#include "SystemGraphics/VertexArray.h"
#include "SystemGraphics/VertexBuffer.h"
#include "SystemGraphics/VertexShader.h"

#include "SystemInput/InputSystem.h"
#include "SystemInput/KeyCode.h"

#include "SystemLogic/ScriptSystem/LuaScriptTest.h"
#include "SystemLogic/AiSystem.h"
#include "SystemLogic/LogicSystem.h"

#include "SystemPhysics/ButtonManager.h"
#include "SystemPhysics/Collision.h"
#include "SystemPhysics/CollisionManager.h"
#include "SystemPhysics/CollisionMap.h"
#include "SystemPhysics/CollisionTable.h"
#include "SystemPhysics/IForce.h"
#include "SystemPhysics/PhysicsSystem.h"
#include "SystemPhysics/RigidBodyManager.h"

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


//TODO Delete this
#include "GameObjectFactory.h"
#include "GameObjectPrototype.h"
#include "SceneManager.h"
#include "IContainer.h"
#include "TransformManager.h"
//

#endif
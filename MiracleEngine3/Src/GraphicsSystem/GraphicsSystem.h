#pragma once

#ifndef GRAPHICSYSTEM_H
#define GRAPHICSYSTEM_H

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Elementbuffer.h"
#include "VertexBuffer.h"
#include <string>
#include "VertexArray.h"
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/GraphicComponents/TransformComponent.h"
#include "GameObjectComponents/GraphicComponents/GraphicComponent.h"
#include "GameObjectComponents/GraphicComponents/AnimationComponent.h"
#include "GameObjectComponents/GraphicComponents/FontComponent.h"
#include "Shader.h"
#include "QuadMesh.h"
#include "TextureManager.h"
#include "PlayerMesh.h"
#include "Camera.h"
#include "FontRenderer.h"
#include "../Animation/AnimationSystem.h"
#include "../Animation/Animation.h"
#include "UIMesh.h"

#include <vector>

struct CircularBatterPlatform
{
	CircularBatterPlatform(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};

struct Building1
{
	Building1(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};


struct Building2
{
	Building2(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};

struct Building3
{
	Building3(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};



struct Building4
{
	Building4(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};


struct Crate
{
	Crate(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};






struct RockyTile
{
	RockyTile(glm::vec3 pos, glm::vec3 scale, float rotation)
	{
		_position = pos;
		_scale = scale;
		_rotationAngle = rotation;
	}
	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotationAngle;
};

enum RenderMode
{
	None,
	Instance,
	Font,
	Font2
};
class GraphicsSystem
{
public:
	std::unordered_map < size_t, FontComponent*> _fontList;
	std::unordered_map < size_t, GraphicComponent*> _spriteList;
	std::unordered_map < size_t, AnimationComponent*> _animationList;
	std::unordered_map < size_t, TransformComponent*>  _transformList;

	void Update(double dt);
	void Exit();
	//RenderMode _renderMode = None;
	int num = 0;

	void SetHealthPercentage(float percentage);
	void SetProgressPercentage(float percentage);

	GraphicsSystem(int windowWidth, int windowHeight);
	Camera& GetCamera();
	const TextureManager& GetTextureManager() const;

	void CalculateProjectionMatrix(int windowWidth, int windowHeight);


	void DrawRockyTile(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);

	void DrawCircularBatteryPlatform(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);
	void DrawBuilding1(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);
	void DrawBuilding2(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);

	void DrawBuilding3(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);
	void DrawBuilding4(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);

	void DrawCrate(const glm::vec3& position, const glm::vec3& scale, float rotationAngle = 0.0f);

private:
	void ClearScreen() const;
	void UnitTest();
	
	int _testAnim = 0;
	int _numAnim = 0;
	int _showfont = 0;
	TextureManager _textureManager;
	Shader _shader{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" };
	glm::mat4 _proj;
	
	QuadMesh _quadmesh;
	UIMesh _uimesh;

	Camera _camera;
	//PlayerMesh _playerMesh;
	FontRenderer _fontRenderer;
	AnimationSystem _animationSystem;

	Animation _testAnimation;
	
	float _healthpercentage = 1.0f;
	float _progresspercentage = 1.0f;

	int _windowWidth;
	int _windowHeight;

	std::vector<RockyTile> _rockyTileList;
	std::vector<CircularBatterPlatform> _circularplatformList;
	std::vector<Building1> _building1List;
	std::vector<Building2> _building2List;
	std::vector<Crate> _crateList;
	std::vector<Building3> _building3List;
	std::vector<Building4> _building4List;
};

#define ResizeGraphics EngineSystems::GetInstance()._graphicsSystem->CalculateProjectionMatrix

#endif

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


	GraphicsSystem(int windowWidth, int windowHeight);
	Camera& GetCamera();
	const TextureManager& GetTextureManager() const;

private:
	void ClearScreen() const;
	void UnitTest();
	
	int _testAnim = 0;
	int _numAnim = 0;
	int _showfont = 0;
	TextureManager _textureManager;
	Shader* _shader;
	glm::mat4 _proj;
	
	QuadMesh _quadmesh;
	UIMesh _uimesh;

	Camera _camera;
	//PlayerMesh _playerMesh;
	FontRenderer _fontRenderer;
	AnimationSystem _animationSystem;

	Animation _testAnimation;
	
};

#endif


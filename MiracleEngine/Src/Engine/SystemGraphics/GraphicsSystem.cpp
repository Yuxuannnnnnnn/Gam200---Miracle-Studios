#include "GraphicsSystem.h"
#include "PrecompiledHeaders.h"
#include <algorithm>

bool compare(RenderObject a, RenderObject b)
{
	return a._zvalue < b._zvalue;
}

void GraphicsSystem::Update(double dt)
{
	BeginScene(dt);


	Vector3  pos = MyInputSystem.GetMouseWorldPos();

	std::unordered_map<size_t, IComponent*>& TileMapContainer = GetComponentMap(TileMap);

	for (auto& tileMap : TileMapContainer)
	{
		TileMapComponent* TMCom = (TileMapComponent*)(tileMap.second);
		std::unordered_map < int, Node* > tileNodeMap = TMCom->GetNodeMap();

		if (TMCom->GetTurnOnTileMap())
		{
			//Check Picking Collision for every single tile
			for (auto& tile : tileNodeMap)
			{
				//Draw every Tile                                       // x center                     y center
				DebugRenderer::GetInstance().DrawBox(glm::vec3{ tile.second->GetPosition()._x, tile.second->GetPosition()._y, 0 },
					// x y scale
					glm::vec3{ TMCom->GetTilesize()._x, TMCom->GetTilesize()._y,0 });

				std::cout << tile.second->GetPosition() << ", " << TMCom->GetTilesize() << std::endl;

				TransformComponent* transform = (TransformComponent*)(TMCom->GetSibilingComponent(ComponentId::CT_Transform));

				//Create a picking Box for each tile, position, tilesize and rotation
				BPolygon pickingBox = BPolygon::CreateBoxPolygon(Vec3{ tile.second->GetPosition()._x,tile.second->GetPosition()._y, 1.0f },
					Vec3{ TMCom->GetTilesize()._x, TMCom->GetTilesize()._y },
					transform->GetRotate());

				//If there is collision
				if (Collision::CollisionCheck(pickingBox, pos))
				{
					if (MyInputSystem.KeyDown(MOUSE_RBUTTON))	//If the tile is selcted
					{
						tile.second->SetSolid(!tile.second->GetSolid());
					}
					else										// If just Hovering over the box
					{
						DebugRenderer::GetInstance().FillBox(glm::vec3{ tile.second->GetPosition().GetX(),tile.second->GetPosition().GetY(), 0 }, glm::vec3{ TMCom->GetTilesize()._x, TMCom->GetTilesize()._y, 0 }, glm::vec4{ 1, 0, 0, 0.3f });
					}
				}

				if (tile.second->GetSolid())
				{
					DebugRenderer::GetInstance().FillBox(glm::vec3{ tile.second->GetPosition().GetX(),tile.second->GetPosition().GetY(), 0 }, glm::vec3{ TMCom->GetTilesize()._x, TMCom->GetTilesize()._y, 0 });
				}

			}
		}
	}

	// debug renderer test

	//DebugRenderer::GetInstance().DrawLine(0, 0, 200, 100);
	//DebugRenderer::GetInstance().DrawBox(glm::vec3{ 0,0,0 }, glm::vec3{ 100,100,0 });

   //DebugRenderer::GetInstance().FillBox(glm::vec3{ 0,0,0 }, glm::vec3{ 100,100,0 });
   //DebugRenderer::GetInstance().FillBox(glm::vec3{ 0,0,0 }, glm::vec3{ 100,100,0 }, glm::vec4{ 0, 0, 1, 0.3f });

	//DebugRenderer::GetInstance().DrawBox(glm::vec3{ 100,0,0 }, glm::vec3{ 100,100,0 });
	//DebugRenderer::GetInstance().DrawBox(glm::vec3{ 200,0,0 }, glm::vec3{ 100,100,0 });
	//DebugRenderer::GetInstance().DrawBox(glm::vec3{ 200,100,0 }, glm::vec3{ 100,100,0 });

	//_fontRenderer->Draw();
	// test draw font



	DebugRenderer::GetInstance().BatchDrawDebugLine();

	std::sort(_renderObjects.begin(), _renderObjects.end(), compare);

	glAlphaFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5f);


	glDisable(GL_DITHER);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_DONT_CARE);
	glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
#define GL_MULTISAMPLE_ARB 0x809D
	glDisable(GL_MULTISAMPLE_ARB);

	renderingAnim = RENDERNONE;

	// Render gameobject in world space
	//normal rendering, no alpha
	for (const auto& renderobj : _renderObjects)
	{
		if (renderobj._hasAlpha)
			continue;

		/*if (renderobj._hasAdjustableAlpha &&
			abs(1.0f - renderobj._alpha) > 0.01f)
			continue;*/
		
		// getting shader from current gameobject
		auto shader = MyResourceManager.GetShaderResource(renderobj._currShader);

		int x = 0;
		int y = 0;
		int z = 0;


		//renderobj._pShader->Select();

		
		if (!renderobj._hasCustomShader)
		{
			renderobj._pShader->Select();
		}
		else
		{
			if (shader != nullptr)
				shader->Select();
		}

		if (renderobj._pTexture)
			renderobj._pTexture->Select();
		else
		{
			continue;
		}

		if (renderobj._isAnimated)
		{
			if (renderingAnim != ANIMATED)
			{
				renderobj._pMesh->Select();
				renderingAnim = ANIMATED;
			}

			float u0 = renderobj._uv.u0;
			float v0 = renderobj._uv.v0;
			float u1 = renderobj._uv.u1;
			float v1 = renderobj._uv.v1;
			GLfloat _positions[] =
			{
				-0.5f, -0.5f, 0.0f, u0, v0, // 0     // bottom left
				 0.5f, -0.5f, 0.0f, u1, v0, // 1     // bottom right
				 0.5f,  0.5f, 0.0f, u1, v1, // 2     // top right
				-0.5f,  0.5f, 0.0f, u0, v1  // 3     // top left
			};
			renderobj._pMesh->GetBuffer()->FillDynamicBuffer(_positions, 4 * 5 * sizeof(GLfloat));
		}
		else
		{
			if (renderingAnim != STATIC)
			{
				renderobj._pMesh->Select();
				renderingAnim = STATIC;
			}
		}
		glm::mat4 mvp = _proj * _view * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
		//if (shader != nullptr)
		_shader->SetUniform4f("u_tintcolor", renderobj._tintcolor.r, renderobj._tintcolor.g, renderobj._tintcolor.b, renderobj._tintcolor.a);
		renderobj._pShader->SetUniform1f("u_Alpha", 1.0f);
		/*if (renderobj._alpha < 0.95f)
		{
			glDisable(GL_ALPHA_TEST);
			renderobj._pShader->SetUniform1f("u_Alpha", renderobj._alpha);
		}*/
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	for (const auto& renderobj : _renderObjects)
	{
		if (!(renderobj._hasAlpha))
			continue;

		if (renderobj._hasAdjustableAlpha)
			continue;


		renderobj._pShader->Select();

		if (renderobj._pTexture)
			renderobj._pTexture->Select();
		else
		{
			continue;
		}

		if (renderobj._isAnimated)
		{
			if (renderingAnim != ANIMATED)
			{
				renderobj._pMesh->Select();
				renderingAnim = ANIMATED;
			}

			float u0 = renderobj._uv.u0;
			float v0 = renderobj._uv.v0;
			float u1 = renderobj._uv.u1;
			float v1 = renderobj._uv.v1;
			GLfloat _positions[] =
			{
				-0.5f, -0.5f, 0.0f, u0, v0, // 0     // bottom left
				 0.5f, -0.5f, 0.0f, u1, v0, // 1     // bottom right
				 0.5f,  0.5f, 0.0f, u1, v1, // 2     // top right
				-0.5f,  0.5f, 0.0f, u0, v1  // 3     // top left
			};
			renderobj._pMesh->GetBuffer()->FillDynamicBuffer(_positions, 4 * 5 * sizeof(GLfloat));
		}
		else
		{
			if (renderingAnim != STATIC)
			{
				renderobj._pMesh->Select();
				renderingAnim = STATIC;
			}
		}
		glm::mat4 mvp = _proj * _view * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
		_shader->SetUniform4f("u_tintcolor", renderobj._tintcolor.r, renderobj._tintcolor.g, renderobj._tintcolor.b, renderobj._tintcolor.a);
		renderobj._pShader->SetUniform1f("u_Alpha", 1.0f);
		/*if (renderobj._alpha < 0.95f)
		{
			glDisable(GL_ALPHA_TEST);
			renderobj._pShader->SetUniform1f("u_Alpha", renderobj._alpha);
		}*/
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	for (const auto& renderobj : _renderObjects)
	{
		if (!renderobj._hasAdjustableAlpha)
			continue;
		/*if (renderobj._hasAdjustableAlpha &&
			abs(1.0f - renderobj._alpha) < 0.01f)
			continue;*/


		renderobj._pShader->Select();

		if (renderobj._pTexture)
			renderobj._pTexture->Select();
		else
		{
			continue;
		}

		if (renderobj._isAnimated)
		{
			if (renderingAnim != ANIMATED)
			{
				renderobj._pMesh->Select();
				renderingAnim = ANIMATED;
			}

			float u0 = renderobj._uv.u0;
			float v0 = renderobj._uv.v0;
			float u1 = renderobj._uv.u1;
			float v1 = renderobj._uv.v1;
			GLfloat _positions[] =
			{
				-0.5f, -0.5f, 0.0f, u0, v0, // 0     // bottom left
				 0.5f, -0.5f, 0.0f, u1, v0, // 1     // bottom right
				 0.5f,  0.5f, 0.0f, u1, v1, // 2     // top right
				-0.5f,  0.5f, 0.0f, u0, v1  // 3     // top left
			};
			renderobj._pMesh->GetBuffer()->FillDynamicBuffer(_positions, 4 * 5 * sizeof(GLfloat));
		}
		else
		{
			if (renderingAnim != STATIC)
			{
				renderobj._pMesh->Select();
				renderingAnim = STATIC;
			}
		}
		glm::mat4 mvp = _proj * _view * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);
		_shader->SetUniform4f("u_tintcolor", renderobj._tintcolor.r, renderobj._tintcolor.g, renderobj._tintcolor.b, renderobj._tintcolor.a);
		renderobj._pShader->SetUniform1f("u_Alpha", renderobj._alpha);

		/*if (renderobj._alpha < 0.95f)
		{
			glDisable(GL_ALPHA_TEST);
			renderobj._pShader->SetUniform1f("u_Alpha", renderobj._alpha);
		}*/
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		renderobj._pShader->SetUniform1f("u_Alpha", 1.0f);
	}


	// update UI and font

	// render UI in screen space
	_uiRenderer.Update(GetComponentMap(UI), _proj);


	// loop through every font component
	// check whether is delayed font or not
	for (auto fontpair : GetComponentMap(Font))
	{
		// check if it is enabled
		if (!fontpair.second->GetEnable())
			continue;


		// get the trasnform component from the object
		TransformComponent* transformComp = (TransformComponent*)GetComponentMap(Transform)[fontpair.first];
		FontComponent* fontComp = (FontComponent*)GetComponentMap(Font)[fontpair.first];

		//std::string tmp{ "sector_017.ttf" };

		_fontRenderer = MyResourceManager.GetFontResource(fontComp->GetFontType());
		if (!transformComp)
			continue;

		if (_fontRenderer == nullptr)
			continue;


		// draw the non delayed font
		if (!fontComp->IsDelayedText())
		{
			_fontRenderer->DrawFont(fontComp->GetFontString(), transformComp->GetPos().GetX(),
				transformComp->GetPos().GetY(), fontComp->GetFontColor());
		}
		// draw the delayed font
		else
		{
			// if starting, start delaying
			if (!fontComp->IsStartDisplaying())
			{
				fontComp->SetDelayTime(0.0f);
			}

			// if not start, set delay and font counter to 0
			else
			{
				fontComp->SetCurrentDelayTime(fontComp->GetCurrentDelayTime() - fontComp->GetDelayTime() * dt);

				if (fontComp->GetCurrentDelayTime() < 150.0f)
				{
					fontComp->SetCurrentDelayTime(200.0f);
					fontComp->SetFontCounter(fontComp->GetFontCounter() + 1);
				}

				_fontRenderer->DrawFontDelayed(dt, fontComp->GetFontString(), transformComp->GetPos().GetX(),
					transformComp->GetPos().GetY(), fontComp->GetFontColor(), fontComp->IsStartDisplaying(), fontComp->GetDelayTime(), fontComp->GetFontCounter());

			}
		}
	}




	//DebugRenderer::GetInstance().DrawLine(0.0f, 0.0f, 100.0f, 100.0f);

	EndScene();

	//DebugRenderer::GetInstance().DrawCircle(0.0f, 0.0f, 100.0f);
	glDisable(GL_ALPHA_TEST);
}

void GraphicsSystem::BeginScene(double dt)
{
	_view = glm::make_mat4(Mtx44::CreateTranspose(MyCameraSystem.GetCamMatrix()).m);
	UpdateRenderObjectList(dt);
	ClearSreen();
}

void GraphicsSystem::EndScene()
{
	_renderObjects.clear();
}

void GraphicsSystem::Init()
{
	// temp
	std::string temp = "DefaultShader";
	std::string temp2 = "sector_017.ttf";

	_shader = MyResourceManager.GetShaderResource(temp);
	_fontRenderer = MyResourceManager.GetFontResource(temp2);
}

void GraphicsSystem::LoadResource()
{
	// temp
	std::string temp = "DefaultShader";
	std::string temp2 = "sector_017";

#ifdef LEVELEDITOR
	MyResourceManager.AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } });
	//MyResourceManager.AddNewFontResource({ temp2,"Resources/Fonts/sector_017.ttf" });
#endif // LEVELEDITOR

	_shader = MyResourceManager.GetShaderResource(temp);
	_fontRenderer = MyResourceManager.GetFontResource(temp2);
}

GraphicsSystem::GraphicsSystem()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

GraphicsSystem::~GraphicsSystem()
{
}


void GraphicsSystem::ResizeGraphics(float width, float height)
{
	_proj = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -150.0f, 150.0f);
	glViewport(0, 0, width, height);
}

void GraphicsSystem::ClearSreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void GraphicsSystem::UpdateRenderObjectList(double dt)
{

	// update 
	Vec3 CameraPos = MyCameraSystem.GetCameraPos();
	float cameraZoom = MyCameraSystem.GetCameraZoom();
	BPolygon viewBox = BPolygon::CreateBoxPolygon(Vec3{ -CameraPos._x, -CameraPos._y,1.f },
		Vec3{ MyWindowsSystem.getWindow().GetWindowWidth() / cameraZoom ,MyWindowsSystem.getWindow().GetWindowHeight() / cameraZoom },
		0.f);

	for (auto& graphicCompPair : GetComponentMap(Graphic))
	{
		if (graphicCompPair.second->GetParentPtr()->GetDestory() || !graphicCompPair.second->GetEnable())
			continue;

		TransformComponent* transformComp = (TransformComponent*)GetComponentMap(Transform)[graphicCompPair.first];

		if (!transformComp)
			continue;

		BPolygon viewBox2 = BPolygon::CreateBoxPolygon(Vec3{ transformComp->GetPos()._x,transformComp->GetPos()._y,1.f },
			Vec3{ transformComp->GetScale()._x,transformComp->GetScale()._y },
			transformComp->GetRotate());

		if (!Collision::CollisionCheck(viewBox, viewBox2))
			continue;

		GraphicComponent* graphicComp = (GraphicComponent*)graphicCompPair.second;
		TransformComponent* transComp = (TransformComponent*)graphicComp->GetSibilingComponent(ComponentId::CT_Transform);
		AnimationComponent* animComp = (AnimationComponent*)graphicComp->GetSibilingComponent(ComponentId::CT_Animation);


		RenderObject renderobject;
		renderobject._hasCustomShader = graphicComp->HasCustomShader();
		
		renderobject._tintcolor = graphicComp->GetTintColor();
		renderobject._currShader = graphicComp->GetShaderType();

		if (graphicComp->IsFadingOut() && !(MyFactory.GetCurrentScene().compare("truelevel1")))
		{
#ifdef LEVELEDITOR

			if (!MyImguiSystem._editorMode)
#endif
			{
				if (graphicComp->GetAlpha() > 0.001f && dt > 0.0)
				{
					float temp = graphicComp->GetAlpha() - 0.22f * dt;
					graphicComp->SetAlpha(temp);
					renderobject._hasAdjustableAlpha = true;
				}
			}
		}

		if (graphicComp->HasAlpha())
		{
			renderobject._hasAlpha = true;
		}
		else
		{
			renderobject._hasAlpha = false;
		}

		if (graphicComp->HasAdjustableAlpha())
		{
			renderobject._hasAdjustableAlpha = true;
			renderobject._hasAlpha = true;

		}
		else
		{
			renderobject._hasAdjustableAlpha = false;
		}

		renderobject._zvalue = transComp->GetPos().GetZ();

		graphicComp->GetTintColor();
		if (graphicComp->IsFlickering())
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			renderobject._alpha = r;
		}
		else
		{
			renderobject._alpha = graphicComp->GetAlpha();
		}
		// check for if obj have animation

		if (animComp && animComp->IsAnimationPlaying() && animComp->GetEnable())
		{
			// get animation from resource manager
			Animation* currAnim = animComp->GetAnimationResource();
			renderobject._isAnimated = true;
			renderobject._pMesh = &_quadMesh;
			if (currAnim)
			{
				renderobject._uv.u0 = currAnim->GetCurrFrame(animComp->GetCurrFrame())->_u0;
				renderobject._uv.v0 = currAnim->GetCurrFrame(animComp->GetCurrFrame())->_v0;
				renderobject._uv.u1 = currAnim->GetCurrFrame(animComp->GetCurrFrame())->_u1;
				renderobject._uv.v1 = currAnim->GetCurrFrame(animComp->GetCurrFrame())->_v1;
			}
			else
			{
				if (DEBUGOUTPUT)
					std::cout << "WARNING: Some Animation Component is giving a nullptr.\n";
			}

			//anim->testanim->Select();
			////_testAnimation.Select();
			//_textureManager._textureMap[anim->GetFilePath()]->Select();

			renderobject._pTexture = animComp->GetCurrentTexture();


		}
		else
		{

			if (!graphicComp->GetFileName().empty())
			{
				const std::string& fileName = graphicComp->GetFileName();
				renderobject._pTexture = MyResourceManager.GetTexture2DResource(fileName);
			}
			else
			{
				renderobject._pTexture = nullptr;
			}

			renderobject._pMesh = &_staticMesh;
			renderobject._isAnimated = false;
		}

		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetMatrix(graphicComp->GetRenderLayer())).m);


		renderobject._pShader = _shader;



		renderobject._transform = modelTransform;
		renderobject._zvalue = transformComp->GetPos().GetZ();
		_renderObjects.push_back(renderobject);

	}
	for (auto& graphicCompPair : GetComponentMap(Graphic))
	{
		GraphicComponent* graphicComp = (GraphicComponent*)graphicCompPair.second;
		if (!graphicComp->IsInterpolateStarting())
		{
			graphicComp->SetInterpolateTimer(0.0f);
		}
		else
		{
			graphicComp->SetInterpolateTimer(graphicComp->GetInterpolateTimer() + 0.08f * dt);
			graphicComp->StartInterpolate();
		}



	}

	//#ifdef LEVELEDITOR


	//#endif
}


Matrix4x4& GraphicsSystem::GetProjection()
{
	return Matrix4x4{ (const float*)glm::value_ptr(_proj) };
}
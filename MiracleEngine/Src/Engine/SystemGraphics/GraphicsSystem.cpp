#include "GraphicsSystem.h"
#include "PrecompiledHeaders.h"
#include <algorithm>

bool compare(RenderObject a, RenderObject b)
{
	return a._zvalue < b._zvalue;
}

void GraphicsSystem::Update(double dt)
{
	BeginScene();

	std::sort(_renderObjects.begin(), _renderObjects.end(), compare);

	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);*/

	int isdrawingAnimated = 0;

	// Render gameobject in world space
	for (const auto& renderobj : _renderObjects)
	{
		renderobj._pShader->Select();

		if (renderobj._pTexture)
			renderobj._pTexture->Select();
		else
		{
			continue;
		}


		renderobj._pMesh->Select();

		if (renderobj._isAnimated)
		{
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
		glm::mat4 mvp = _proj * _view * renderobj._transform;
		renderobj._pShader->SetUniformMat4f("u_MVP", mvp);

		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_DST_ALPHA);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	// render UI in screen space
	_uiRenderer.Update(GetComponentMap(UI), _proj);

	//DebugRenderer::GetInstance().DrawLine(0.0f, 0.0f, 100.0f, 100.0f);

	EndScene();

	//DebugRenderer::GetInstance().DrawCircle(0.0f, 0.0f, 100.0f);
}

void GraphicsSystem::BeginScene()
{
	_view = glm::make_mat4(Mtx44::CreateTranspose(MyCameraSystem.GetCamMatrix()).m);
	UpdateRenderObjectList();
	ClearSreen();
}

void GraphicsSystem::EndScene()
{
	_renderObjects.clear();
}

GraphicsSystem::GraphicsSystem()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	// temp
	std::string temp = "DefaultShader";

	_shader = MyResourceSystem.GetShaderResource(temp);

	if (!_shader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } }))
	{
		_shader = MyResourceSystem.GetShaderResource(temp);
	}
}

GraphicsSystem::~GraphicsSystem()
{
}


void GraphicsSystem::ResizeGraphics(float width, float height)
{
	_proj = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -30.0f, 30.0f);
	glViewport(0, 0, width, height);
}

void GraphicsSystem::ClearSreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void GraphicsSystem::UpdateRenderObjectList()
{

	// update 
	Vec3 CameraPos = MyCameraSystem.GetCameraPos();
	float cameraZoom = MyCameraSystem.GetCameraZoom();
	BPolygon viewBox = BPolygon::CreateBoxPolygon(Vec3{ -CameraPos._x,-CameraPos._y,1.f },
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

		RenderObject renderobject;

		renderobject._zvalue = transComp->GetPos().GetZ();

		// check for if obj have animation

		if (graphicComp->GetSibilingComponent(ComponentId::CT_Animation))
		{
			AnimationComponent* anim = (AnimationComponent*)graphicComp->GetSibilingComponent(ComponentId::CT_Animation);

			// get animation from resource manager
			Animation* currAnim = MyResourceManager.GetAnimationResource(anim->GetCurrAnim());
			renderobject._isAnimated = true;
			renderobject._pMesh = &_quadMesh;
			if (currAnim)
			{
				renderobject._uv.u0 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_u0;
				renderobject._uv.v0 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_v0;
				renderobject._uv.u1 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_u1;
				renderobject._uv.v1 = currAnim->GetCurrFrame(anim->GetCurrFrame())->_v1;
			}
			else
			{
				if (DEBUGOUTPUT)
					std::cout << "WARNING: Some Animation Component is giving a nullptr.\n";
			}

			//anim->testanim->Select();
			////_testAnimation.Select();
			//_textureManager._textureMap[anim->GetFilePath()]->Select();

		}
		else
		{
			renderobject._pMesh = &_staticMesh;
			renderobject._isAnimated = false;
		}
		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetMatrix()).m);


		renderobject._pShader = _shader;

		if (!graphicComp->GetFileName().empty())
		{
			const std::string& fileName = graphicComp->GetFileName();
			renderobject._pTexture = MyResourceManager.GetTexture2DResource(fileName);
		}
		else
		{
			renderobject._pTexture = nullptr;
		}

		renderobject._transform = modelTransform;
		renderobject._zvalue = transformComp->GetPos().GetZ();
		_renderObjects.push_back(renderobject);

	}

}


Matrix4x4& GraphicsSystem::GetProjection()
{
	return Matrix4x4{ (const float*)glm::value_ptr(_proj) };
}
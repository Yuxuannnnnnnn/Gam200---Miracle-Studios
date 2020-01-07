#include "GraphicsSystem.h"
#include "PrecompiledHeaders.h"

void GraphicsSystem::Update(double dt)
{
	BeginScene();

	_renderer.Update(_renderObjects, _proj * _cameraManager.GetMainCamMatrix());

	EndScene();
}

void GraphicsSystem::BeginScene()
{
	UpdateRenderObjectList();
	ClearSreen();
}

void GraphicsSystem::EndScene()
{
	for (auto& element : _renderObjects)
	{
		element.clear();
	}
}

GraphicsSystem::GraphicsSystem(int windowWidth, int windowHeight)
	: _proj{ glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
			-(float)windowHeight / 2, (float)windowHeight / 2, -30.0f, 30.0f) }
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);


	// temp set view to identity
	//_view = glm::mat4(1.0f);

	for (size_t i = 0; i <= 10; i++)
	{
		_renderObjects.push_back(std::vector<RenderObject>{});
	}

	// temp
	std::string temp = "DefaultShader";

	_shader =MyResourceSystem.GetShaderResource(temp);

	if (!_shader &&MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" } }))
	{
		_shader =MyResourceSystem.GetShaderResource(temp);
	}
}

GraphicsSystem::~GraphicsSystem()
{
}



void GraphicsSystem::ClearSreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GraphicsSystem::UpdateViewMatrix()
{
	_cameraManager.Update();
}

void GraphicsSystem::UpdateRenderObjectList()
{
	// TODO: check if object in screen

	// update 
	std::vector<RenderObject> renderObj;

	BBox viewBox = BBox::CreateBBoxFromData(Vec3::Vec3Zero,
		Vec3{ MyWindowsSystem.getWindow().GetWindowWidth() * 0.75f ,MyWindowsSystem.getWindow().GetWindowHeight() * 0.75f },
		0.f);

	for (auto& graphicCompPair : MyComponentManger._graphicComponents)
	{
		if (graphicCompPair.second->GetParentId() < 1000 || graphicCompPair.second->GetParentPtr()->GetDestory())
			continue;

		GraphicComponent* graphicComp = graphicCompPair.second;
		if (!graphicComp->GetEnable())
			continue;

		size_t objID = graphicCompPair.first;	//Get GameObjectID
		TransformComponent* transformComp = MyComponentManger._transformComponents[objID];

		if (!Collision::DefaultColliderDataCheck(viewBox,
			BBox::CreateBBoxFromData(transformComp->GetPos(), transformComp->GetScale(), transformComp->GetRotate())))
			continue;


		glm::mat4 modelTransform = glm::make_mat4(Mtx44::CreateTranspose(transformComp->GetModel()).m);


		RenderObject renderobject;

		renderobject._pMesh = &_quadMesh;
		renderobject._pShader = _shader;
		renderobject._pTexture = MyResourceManager.GetTexture2DResource(graphicComp->GetFileName());
		renderobject.transform = modelTransform;
		_renderObjects[0].push_back(renderobject);


	}

}

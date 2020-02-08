#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "Tools/Resource/ResourceSystem.h"

#include "Editor/ImguiFunctions.h"


enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	//RenderLayer _renderlayer; Not Used anymore because Z value is computed in Transformcomponent
	
	// has alpha from PNG
	bool _hasAlpha;

	// has alpha adjustable in programming
	bool _hasAdjustableAlpha;

	
	bool _isFadingOut;
	bool _isFlickering;


	float u0, v0;
	float u1, v1;

	int _layer;
	float _alphaVal;
public:
	inline bool HasAlpha() 
	{
		return _hasAlpha; 
	}

	inline bool HasAdjustableAlpha()
	{
		return _hasAdjustableAlpha;
	}

	inline bool IsFadingOut()
	{
		return _isFadingOut;
	}

	inline bool IsFlickering()
	{
		return _isFlickering;
	}

	void EnableAlpha(bool isAlpha)
	{
		_hasAlpha = isAlpha;
	}


	void SetAlpha(float alphaValue);
	float GetAlpha();
	unsigned int GetTextureID() const;               // base on asset file name, get the textureID on OpenGL for imgui
	
	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	const std::string& GetShaderType()
	{
		return _shader;
	}


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		//if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
		//	_typeIdGraphic = document["G.TypeId"].GetInt();

		if (document.HasMember("GraphicsComponent") && document["GraphicsComponent"].IsBool())
			SetEnable(document["GraphicsComponent"].GetBool());

		if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
			_fileName = document["G.FileName"].GetString();


		if (document.HasMember("G.Shader") && document["G.Shader"].IsString())
			_shader = document["G.Shader"].GetString();

		if (document.HasMember("G.Layer") && document["G.Layer"].IsInt())	//Checks if the variable exists in .Json file
		{
			_layer = (document["G.Layer"].GetInt());
		}

		if (document.HasMember("_hasAlpha") && document["_hasAlpha"].IsBool())	//Checks if the variable exists in .Json file
		{
			_hasAlpha = (document["_hasAlpha"].GetBool());
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("GraphicsComponent", value);
		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value);

		value.SetString(rapidjson::StringRef(_shader.c_str()));
		prototypeDoc.AddMember("G.Shader", value);

		value.SetInt(_layer);
		prototypeDoc.AddMember("G.Layer", value);

		value.SetBool(_hasAlpha);
		prototypeDoc.AddMember("_hasAlpha", value);

	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("GraphicsComponent", value, allocator);

		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value, allocator);

		value.SetString(rapidjson::StringRef(_shader.c_str()));
		prototypeDoc.AddMember("G.Shader", value, allocator);

		value.SetInt(_layer);
		prototypeDoc.AddMember("G.Layer", value, allocator);

		value.SetBool(_hasAlpha);
		prototypeDoc.AddMember("_hasAlpha", value, allocator);

	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		GraphicComponent* protoGraphicCom = dynamic_cast<GraphicComponent*>(protoCom);

		if (!protoGraphicCom)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}


		rapidjson::Value enable;
		rapidjson::Value fileName;
		rapidjson::Value shader;
		rapidjson::Value layer;
		rapidjson::Value HasAlpha;

		bool addComponentIntoSceneFile = false;

		if (protoGraphicCom->GetEnable() != this->GetEnable())
		{
			addComponentIntoSceneFile = true;
			enable.SetBool(GetEnable());
		}

		if (protoGraphicCom->_hasAlpha != this->_hasAlpha)
		{
			addComponentIntoSceneFile = true;
			HasAlpha.SetBool(_hasAlpha);
		}

		if (protoGraphicCom->_fileName.compare(_fileName))
		{
			addComponentIntoSceneFile = true;
			fileName.SetString(rapidjson::StringRef(_fileName.c_str()));
		}

		if (protoGraphicCom->_shader.compare(_shader))
		{
			addComponentIntoSceneFile = true;
			shader.SetString(rapidjson::StringRef(_shader.c_str()));
		}		
		
		if (protoGraphicCom->_layer != _layer)
		{
			addComponentIntoSceneFile = true;
			layer.SetInt(_layer);
		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("GraphicsComponent", enable, allocator);
			else
				value.AddMember("GraphicsComponent", protoGraphicCom->GetEnable(), allocator);

			if (!HasAlpha.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("_hasAlpha", HasAlpha, allocator);
			}

			if (!fileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("G.FileName", fileName, allocator);
			}

			if (!shader.IsNull())
			{
				value.AddMember("G.Shader", shader, allocator);
			}

			if (!layer.IsNull())
			{
				value.AddMember("G.Layer", layer, allocator);
			}
		}

	}


	virtual void Inspect() override
	{
		IComponent::Inspect();

		//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));
	
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::InputInt("RenderLayer", &_layer);
	/*	if (_layer > 10)
			_layer = 30;
		else if (_layer < 0)
			_layer = 0;*/

		ImGui::Spacing();
		ImGui::Spacing();

		static auto& graphicList = MyResourceSystem.GetTexture2DList();
		std::vector<const char*> list(graphicList.size());
		//list[0] = "Choose a Texture ";

		int i = 0;
		int select = 0;
		for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
		{
			const char* ptr = graphicPair->first.c_str();


			list[i] = ptr;
			if (!strncmp(ptr, _fileName.c_str(), 20))
			{
				select = i;
			}


			i++;
		}
		
		//	//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
		//
		//	static const char* item_current = list[select];            // Here our selection is a single pointer stored outside the object.
		//	if (ImGui::BeginCombo(" Texture ", item_current, 0)) // The second parameter is the label previewed before opening the combo.
		//	{
		//		for (int n = 0; n < list.size(); n++)
		//		{
		//			bool is_selected = (item_current == list[n]);
		//			if (ImGui::Selectable(list[n], is_selected))
		//			{
		//				item_current = list[n];
		//				_fileName = list[n];
		//			}
		//
		//			//if (is_selected);
		//			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		//
		//		}
		//		ImGui::EndCombo();
		//	}
		//}

		static ComboFilterState s = { select, 0 };

		static char buf[128];
		
		static ImGuiFunctions Function;
		static bool op = false;
		static bool * open = &op;
		
		if (_fileName.empty())
		{
			strncpy(buf, "type text here...", 18 + 1);
		}
		else
		{
			strncpy(buf, _fileName.c_str(), _fileName.size() + 2);
		}

		if (Function.ComboFilter("Texture", buf, IM_ARRAYSIZE(buf), list, list.size(), s, _fileName, open))
		{
			//puts(buf);
		}

		{
			ImGui::Spacing();

			static auto& ShaderList = MyResourceSystem.GetShaderList();
			std::vector<const char*> list;
			list.push_back("Choose a Shader ");
			static const char* name = list[0];


			int i = 1;
			static int select = 0;
			for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
			{
				const char* ptr = shaderPair->first.c_str();
				if (shaderPair->first.find("System") == std::string::npos)
				{
					list.push_back(ptr);
					if (!strncmp(shaderPair->first.c_str(), _shader.c_str(), 20))
					{
						select = i;
					}
				}
				i++;
			}

			if (ImGui::BeginCombo("Shader", list[select], 0)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < list.size(); n++)
				{
					bool is_selected = (name == list[n]);
					if (ImGui::Selectable(list[n], is_selected))
					{
						_shader = list[n];
						select = n;
					}

					//if (is_selected);
					//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

				}
				ImGui::EndCombo();
			}


			ImGui::Spacing();
			std::string string = "Has Alpha ";
			ImGui::Checkbox(string.c_str(), &_hasAlpha);
			//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));

			//AssetsImguiWindow*  window = dynamic_cast<AssetsImguiWindow *>(_engineSystems._imguiSystem->GetWindows()["Assets"]);
			//static auto ShaderList = window->GetVertexShaderFiles();
			//static auto FragmentList = window->GetFragementShaderFiles();
			//ShaderList.insert(FragmentList.begin(), FragmentList.end());

			//ImGui::Spacing();
			//int shaderCount = 1;
			//static std::vector<int> select(_current_ShaderList.size(), 0);


			//if (ImGui::Button("Add Shader"))
			//{
			//	_current_ShaderList.push_back(" ");
			//	select.push_back(0);
			//}
			//
			//for (auto currshader : _current_ShaderList)
			//{
			//	ImGui::Spacing();
			//
			//	auto shader = _shaderList.begin();
			//
			//	std::vector<const char*> list(ShaderList.size() + 1);
			//	list[0] = " Choose a shader ";
			//
			//	int i = 1;
			//	//static int select = 0;
			//	for (auto shaderPair = ShaderList.begin(); shaderPair != ShaderList.end(); shaderPair++)
			//	{
			//		const char* ptr = shaderPair->first.c_str();
			//		list[i] = ptr;
			//		if (shader != _shaderList.end())
			//		{
			//			if (strncmp(shaderPair->first.c_str(), shader->c_str(), 20) && currshader != nullptr)
			//			{
			//				select[shaderCount - 1] = i;
			//			}
			//		}
			//		i++;
			//	}
			//	//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
			//	currshader = list[select[shaderCount - 1]];            // Here our selection is a single pointer stored outside the object.
			//
			//	std::string shaderCountString = " Shader " + std::to_string(shaderCount);
			//	if (ImGui::BeginCombo(shaderCountString.c_str(), currshader, 0)) // The second parameter is the label previewed before opening the combo.
			//	{
			//		for (int n = 0; n < list.size(); n++)
			//		{
			//			bool is_selected = (currshader == list[n]);
			//			if (ImGui::Selectable(list[n], is_selected))
			//			{
			//				currshader = list[n];
			//				select[shaderCount - 1] = n;
			//			}
			//
			//			//if (is_selected);
			//			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
			//
			//		}
			//		ImGui::EndCombo();
			//	}
			//	if (shader != _shaderList.end())
			//	{
			//		shader++;
			//	}
			//	shaderCount++;
			//}



		}


		{
			//ImGui::Spacing();
			//ImGui::InputInt("Shader ID", &_shaderID);
			ImGui::Spacing();
			//ImGui::InputInt("RendeerLayer", &_renderLayer);
			ImGui::Spacing();
		}
	}


	//Constructor
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs) = default;
	GraphicComponent& operator=(const GraphicComponent& rhs) = default;


	void RenderLayerResolver();

	int GetTextureState();
	void SetTextureState(int state)
	{

	}

	int GetRenderLayer()
	{
		return _layer;
	}
	void SetRenderLayer(int state);


	unsigned& GetTypeId();

	GraphicComponent* CloneComponent() { return new GraphicComponent(*this); }
};













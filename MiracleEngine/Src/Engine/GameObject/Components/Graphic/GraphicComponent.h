#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "Tools/Resource/ResourceSystem.h"



/*  Demo: */
/*
	{
		// requisite: hints must be alphabetically sorted beforehand
		const char *hints[] = {
			"AnimGraphNode_CopyBone",
			"ce skipaa",
			"ce skipscreen",
			"ce skipsplash",
			"ce skipsplashscreen",
			"client_unit.cpp",
			"letrograd",
			"level",
			"leveler",
			"MacroCallback.cpp",
			"Miskatonic university",
			"MockAI.h",
			"MockGameplayTasks.h",
			"MovieSceneColorTrack.cpp",
			"r.maxfps",
			"r.maxsteadyfps",
			"reboot",
			"rescale",
			"reset",
			"resource",
			"restart",
			"retrocomputer",
			"retrograd",
			"return",
			"slomo 10",
			"SVisualLoggerLogsList.h",
			"The Black Knight",
		};
		static ComboFilterState s = {0};
		static char buf[128] = "type text here...";
		if( ComboFilter("my combofilter", buf, IM_ARRAYSIZE(buf), hints, IM_ARRAYSIZE(hints), s) ) {
			puts( buf );
		}
	}
*/


struct ComboFilterState
{
	int  activeIdx;         // Index of currently 'active' item by use of up/down keys
	bool selectionChanged;  // Flag to help focus the correct item when selecting active item
};

static bool ComboFilter__DrawPopup(ComboFilterState& state, int START, /*const char** ENTRIES*/   std::vector<const char*> ENTRIES, int ENTRY_COUNT, std::string& _fileName)
{
	using namespace ImGui;
	bool clicked = 0;

	// Grab the position for the popup
	ImVec2 pos = GetItemRectMin(); pos.y += GetItemRectSize().y;
	ImVec2 size = ImVec2(GetItemRectSize().x - 60, GetItemsLineHeightWithSpacing() * 4);

	PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_HorizontalScrollbar |
		ImGuiWindowFlags_NoSavedSettings |
		0; //ImGuiWindowFlags_ShowBorders;

	SetNextWindowFocus();

	SetNextWindowPos(pos);
	SetNextWindowSize(size);
	Begin("##combo_filter", nullptr, flags);

	PushAllowKeyboardFocus(false);

	for (int i = 0; i < ENTRY_COUNT; i++) {
		// Track if we're drawing the active index so we
		// can scroll to it if it has changed
		bool isIndexActive = state.activeIdx == i;

		if (isIndexActive) {
			// Draw the currently 'active' item differently
			// ( used appropriate colors for your own style )
			PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 0, 1));
		}

		PushID(i);
		if (Selectable(ENTRIES[i], isIndexActive)) {
			// And item was clicked, notify the input
			// callback so that it can modify the input buffer
			state.activeIdx = i;
			clicked = 1;

			_fileName = ENTRIES[i];
		}
		if (IsItemFocused() && IsKeyPressed(GetIO().KeyMap[ImGuiKey_Enter])) {
			// Allow ENTER key to select current highlighted item (w/ keyboard navigation)
			state.activeIdx = i;
			clicked = 1;
		}
		PopID();

		if (isIndexActive) {
			if (state.selectionChanged) {
				// Make sure we bring the currently 'active' item into view.
				SetScrollHere();
				state.selectionChanged = false;
			}

			PopStyleColor(1);
		}
	}

	PopAllowKeyboardFocus();
	End();
	PopStyleVar(1);

	return clicked;
}

static bool ComboFilter(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints, int num_hints, ComboFilterState& s, std::string& _filename) {
	struct fuzzy {
		static int score(const char* str1, const char* str2) {
			int score = 0, consecutive = 0, maxerrors = 0;
			while (*str1 && *str2) {
				int is_leading = (*str1 & 64) && !(str1[1] & 64);
				if ((*str1 & ~32) == (*str2 & ~32)) {
					int had_separator = (str1[-1] <= 32);
					int x = had_separator || is_leading ? 10 : consecutive * 5;
					consecutive = 1;
					score += x;
					++str2;
				}
				else {
					int x = -1, y = is_leading * -3;
					consecutive = 0;
					score += x;
					maxerrors += y;
				}
				++str1;
			}
			return score + (maxerrors < -9 ? -9 : maxerrors);
		}
		static int search(const char* str, int num, /*const char* words[] */  std::vector<const char*> words) {
			int scoremax = 0;
			int best = -1;
			for (int i = 0; i < num; ++i) {
				int score = fuzzy::score(words[i], str);
				int record = (score >= scoremax);
				int draw = (score == scoremax);
				if (record) {
					scoremax = score;
					if (!draw) best = i;
					else best = best >= 0 && strlen(words[best]) < strlen(words[i]) ? best : i;
				}
			}
			return best;
		}
	};
	using namespace ImGui;
	bool done = InputText(id, buffer, bufferlen, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
	bool hot = s.activeIdx >= 0 && strcmp(buffer, hints[s.activeIdx]);
	if (hot) {
		int new_idx = fuzzy::search(buffer, num_hints, hints);
		int idx = new_idx >= 0 ? new_idx : s.activeIdx;
		s.selectionChanged = s.activeIdx != idx;
		s.activeIdx = idx;
		if (done || ComboFilter__DrawPopup(s, idx, hints, num_hints ,_filename)) {
			int i = s.activeIdx;
			if (i >= 0) {
				strcpy(buffer, hints[i]);
				done = true;
			}
		}
	}
	return done;
}

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	//RenderLayer _renderlayer; Not Used anymore because Z value is computed in Transformcomponent


	float u0, v0;
	float u1, v1;

public:

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

		if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
			_fileName = document["G.FileName"].GetString();


		if (document.HasMember("G.Shader") && document["G.Shader"].IsString())
			_shader = document["G.Shader"].GetString();


	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("GraphicComponent", rapidjson::Value(true));
		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value);

		value.SetString(rapidjson::StringRef(_shader.c_str()));
		prototypeDoc.AddMember("G.Shader", value);

	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("GraphicComponent", rapidjson::Value(true), allocator);
		//value.SetInt(_typeIdGraphic);
		//prototypeDoc.AddMember("G.TypeId", value);

		value.SetString(rapidjson::StringRef(_fileName.c_str()));
		prototypeDoc.AddMember("G.FileName", value, allocator);

		value.SetString(rapidjson::StringRef(_shader.c_str()));
		prototypeDoc.AddMember("G.Shader", value, allocator);

	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		GraphicComponent* protoGraphicCom = dynamic_cast<GraphicComponent*>(protoCom);

		rapidjson::Value fileName;
		rapidjson::Value shader;
		rapidjson::Value renderlayer;
		bool addComponentIntoSceneFile = false;

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
		


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("GraphicComponent", rapidjson::Value(true), allocator);

			if (!fileName.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("G.FileName", fileName, allocator);
			}

			if (!shader.IsNull())
			{
				value.AddMember("G.Shader", shader, allocator);
			}

			if (!renderlayer.IsNull())
			{
				value.AddMember("G.RenderLayer", renderlayer, allocator);
			}
		}

	}


	virtual void Inspect() override
	{
		IComponent::Inspect();
		
		ImGui::Spacing();
		//ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));


		static auto& graphicList = MyResourceSystem.GetTexture2DList();
		std::vector<const char*> list(graphicList.size());
		//list[0] = "Choose a Texture ";

		int i = 0;
		int select = 0;
		for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
		{
			const char* ptr = graphicPair->first.c_str();


			list[i] = ptr;
			//if (!strncmp(ptr, _fileName.c_str(), 20))
			//{
			//	select = i;
			//}


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

		static ComboFilterState s = { 0 };

		static char buf[128];
		
		if (_fileName.empty())
		{
			strncpy(buf, "type text here...", 18);
		}
		else
		{
			strncpy(buf, _fileName.c_str(), _fileName.size());
		}

		if (ComboFilter("my combofilter", buf, IM_ARRAYSIZE(buf), list, list.size(), s, _fileName)) 
		{
			puts(buf);
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

			if (ImGui::BeginCombo(" ", list[select], 0)) // The second parameter is the label previewed before opening the combo.
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
		return 0;
	}
	void SetRenderLayer(int state);


	unsigned& GetTypeId();

	GraphicComponent* CloneComponent() { return new GraphicComponent(*this); }
};











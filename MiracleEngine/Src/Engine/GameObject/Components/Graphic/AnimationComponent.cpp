#include "PrecompiledHeaders.h"
#include "AnimationComponent.h"

#include "Editor/ImguiFunctions.h"

//void AnimationComponent::SetFilePath(const std::string path)
//{
//	_type = path;
//}
//
//std::string& AnimationComponent::GetFilePath()
//{
//	return _type;
//}






void AnimationComponent::SetCurrentAnim(const std::string& AnimationName)
{
	setCurrentAnimation(AnimationName);
	SetStartFrame();
	ResetCurrTimeDelay();
	SetTimeDelay(AnimationName);

	Animation* animResource = MyResourceManager.GetAnimationResource(_currentAnim);
	SetMaxFrame(animResource->GetMaxFrame());
}



 void AnimationComponent::Inspect()
{
	IComponent::Inspect();


	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 45.0f);
		ImGui::TextUnformatted("Do not have two AnimationNames that are the same, else will result in one of the Animation being deleted");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	ImGui::SameLine(100);
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 45.0f);
		ImGui::TextUnformatted("Press Enter to confirm what you typed into the InputText Box");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	////Inspect list of animations - Add animations - remove animations - each animation with own time Delay

	static std::unordered_map<std::string, Animation*>& animationList = MyResourceSystem.GetAnimationMap();
	std::vector<const char*> AninmationTypeList(animationList.size());
	//list[0] = "Choose a Texture ";


	int a = 0;
	for (auto& animationGraphicPair : animationList)
	{
		const char* ptr = animationGraphicPair.first.c_str();

		AninmationTypeList[a] = ptr;
		a++;
	}


	int i = 0;
	int select = 0;

	std::vector<AnimationName> NameList;
	std::vector<AnimationName> UnchangedNameList;

	for (auto& animation : _animations)
	{
		//NameList.push_back(animation.first);
		//UnchangedNameList.push_back(animation.first);

		ImGui::Spacing();

		if (i < _animations.size())
		{
			for (int j = 0; j < AninmationTypeList.size(); j++)
			{
				if (!strncmp(AninmationTypeList[j], animationFileNameList[animation.first].c_str(), animationFileNameList[animation.first].size()))
				{
					select = j;
				}
			}
		}

		static std::vector<ComboFilterState> s;
		static std::vector<char*> buf;
		static std::vector<ImGuiFunctions*> DropDownBars;
		//static ImGuiFunctions function;
		static std::vector<bool*> openArray;


		//static std::vector< bool *(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints,
		//	int num_hints, ImGuiFunctions::ComboFilterState & s, std::string & _filename)> 


		if (s.size() == i)
		{
			s.push_back(ComboFilterState{ select, 0 });
		}
		if (buf.size() == i)
		{
			buf.push_back(new char[128]);
			strncpy(buf[i], "", 2);
			openArray.push_back(new bool{ true });
		}
		if (DropDownBars.size() == i)
		{
			DropDownBars.push_back(new ImGuiFunctions{});
		}

		if (animationFileNameList[animation.first].empty())
		{
			strncpy(buf[i], "Choose an Animation File here", 31);
		}
		else
		{
			strncpy(buf[i], animationFileNameList[animation.first].c_str(), animationFileNameList[animation.first].size() + 2);
		}


		std::string AnimationType = "AnimationType##" + std::to_string(i);

		if (DropDownBars[i]->ComboFilter(AnimationType.c_str(), buf[i], 128, AninmationTypeList, AninmationTypeList.size(), s[i], animationFileNameList[animation.first], openArray[i], i))
		{
			//puts(buf);
		}


		ImGui::Spacing();
		ImGui::Spacing();

		std::string TimeDelay = "TimeDelay##" + std::to_string(i);
		ImGui::InputFloat(TimeDelay.c_str(), &_animations[animation.first]);


		ImGui::Spacing();
		ImGui::Spacing();

		//AnimationName is not changed in the loop, saved in NameList, ChangedList and UnchangedNameList
		std::string AnimationName = "AnimationName##" + std::to_string(i);
		char AnimName[128] = "\0";
		bool done;
		strncpy(AnimName, animation.first.c_str(), animation.first.length() + 2);
		if (done = ImGui::InputText(AnimationName.c_str(), AnimName, 128, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string length(AnimName);
			if (int i = strncmp(AnimName, animation.first.c_str(), length.length()))
			{
				NameList.push_back(std::string(AnimName));
				UnchangedNameList.push_back(animation.first);
			}
		}


		i++;

		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::SameLine(300);

		std::string Delete = "Delete Animation##" + std::to_string(i);
		if (ImGui::Button(Delete.c_str()))
		{
			animationFileNameList.erase(animation.first);
			_animations.erase(animation.first);
			break;
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
	}


	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Add New Animation"))
	{
		_animations.insert(std::pair<AnimationName, timeDelay>("", 0.0));
		animationFileNameList.insert(std::pair<AnimationName, AnimationFile>("", ""));
	}


	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();


	std::map<AnimationName, AnimationFile> tempNameFileList;
	std::map<AnimationName, timeDelay> tempNameTimeList;	//Each animation has its own timedelay
//AnimationName is changed here, key pair is extracted and changed and inserted back into the maps

	auto& NameFile = animationFileNameList.begin();

	for (auto& NameTime : _animations)
	{
		std::pair< AnimationName, AnimationFile > nameFile;
		std::pair< AnimationName, timeDelay > nameTime;

		nameFile = *NameFile;
		nameTime = NameTime;

		for (int i = 0; i < UnchangedNameList.size(); i++)
		{
			if (!UnchangedNameList[i].compare(nameFile.first))
			{
				nameFile.first = NameList[i];
				nameTime.first = NameList[i];
				break;
			}
		}
		tempNameFileList.insert(nameFile);
		tempNameTimeList.insert(nameTime);

		NameFile++;
	}

	animationFileNameList.clear();
	_animations.clear();

	animationFileNameList = tempNameFileList;
	_animations = tempNameTimeList;






	if (!_animations.empty())
	{
		ImGui::Spacing();
		ImGui::Spacing();
		std::vector<const char*> AnimationNameList(_animations.size());
		//list[0] = "Choose a Texture ";


		int a = 0;
		int select1 = 0;
		for (auto& NameTime : _animations)
		{
			const char* ptr = NameTime.first.c_str();

			AnimationNameList[a] = ptr;
			if (!strncmp(ptr, _startingAnim.c_str(), _startingAnim.length()))
			{
				select1 = a;
			}

			a++;
		}


		char buf[128] = "";
		static ImGuiFunctions function;
		static bool op = true;
		static bool* open = &op;
		static ComboFilterState s{ select1, 0 };

		//static std::vector< bool *(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints,
		//	int num_hints, ImGuiFunctions::ComboFilterState & s, std::string & _filename)> 


		if (_startingAnim.empty())
		{
			strncpy(buf, "Choose an AnimationName here", 30);
		}
		else
		{
			strncpy(buf, _startingAnim.c_str(), _startingAnim.size() + 2);
		}


		std::string StartingAnim = "StartingAnim##" + std::to_string(i);

		if (function.ComboFilter(StartingAnim.c_str(), buf, 128, AnimationNameList, AnimationNameList.size(), s, _startingAnim, open, i))
		{
			//puts(buf);
		}
	}

	////ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
	//ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
	//	ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));


}


AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnim{ "" }, _startingAnim{ "" }, /*_currAnimation{ nullptr },*/ _currFrame{ 0 }, _timeDelay{ 0.5f }, _currentTimeDelay{0.5f}, _maxFrame{6}
{
	if (component)
	{
		AnimationComponent* animationComponent = dynamic_cast<AnimationComponent*>(component);
	}


	// temporary test
	//testanim = new Animation();
	//testanim->load("./Resources/TextFiles/AnimationData/CatAnimation.json");
}



std::string AnimationComponent::ComponentName() const
{
	return std::string("Animation Component");
}




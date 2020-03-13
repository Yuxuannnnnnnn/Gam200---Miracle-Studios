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



bool AnimationComponent::IsAnimationPlaying()
{
	return _animationPlaying;
}


int AnimationComponent::GetCurrentFrame()
{
	return _currFrame;
}

int AnimationComponent::GetMaxFrame()
{
	return _maxFrame;
}

float AnimationComponent::GetTimeDelay()
{
	return _timeDelay;
}

void AnimationComponent::SetTimeDelay(float time)
{
	 _timeDelay = time;
}

bool AnimationComponent::IsPlayingOnce()
{
	return _playOnce;
}

void AnimationComponent::SetPlayingOnce(bool isplayingonce)
{
	_playOnce = isplayingonce;
}

void AnimationComponent::SetCurrentAnim(const std::string& AnimationName)
{
	SetAnimationPlaying(true);
	_currenAnimName = AnimationName;
	setCurrentAnimation(AnimationName);	//Set the _currentAnim .json File
	SetStartFrame();	//Reset the current frame to 0
	ResetCurrTimeDelay();	//Reset currentttimedelay to 0
	SetTimeDelay(AnimationName);	//Set the TimeDelay
	SetAnimationResource();	//Set the Animation*

	if(_currAnimationResource)
		SetMaxFrame(_currAnimationResource->GetMaxFrame());	//Set the Max Frame
}

void AnimationComponent::SetCurrentAnimOnce(const std::string& AnimationName)
{
	SetCurrentAnim(AnimationName);

	_playOnce = true;
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
	std::vector<const char*> AninmationTypeList(animationList.size() + 1);


	int a = 0;
	AninmationTypeList[a] = "Choose an Animation File here";
	a++;
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
				if (!strncmp(AninmationTypeList[j], animationFileNameList[animation.first].c_str(), 
					animationFileNameList[animation.first].size()))
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
			openArray.push_back(new bool{ false });
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
			if(!animation.first.compare(_currenAnimName))
				SetCurrentAnim(animation.first);	//Reset the Animation File of the current animation playing
		}


		ImGui::Spacing();
		ImGui::Spacing();

		std::string TimeDelay = "TimeDelay##" + std::to_string(i);
		if (ImGui::InputFloat(TimeDelay.c_str(), &_animations[animation.first], ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (!animation.first.compare(_currenAnimName))
				SetCurrentAnim(animation.first);	//Reset the TimeDelay
		}


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

		ImGui::SameLine(150);

		std::string Play = "Play Animation##" + std::to_string(i);
		if (ImGui::Button(Play.c_str()))
		{
			MyAnimationWindow.SetAnimationWindow(animation.first, animation.second, animationFileNameList[animation.first]);
		}

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


		ImGui::Checkbox("Play At Creation", &_playAtCreation);

		if(_playAtCreation)
			ImGui::Checkbox("Loop?", &_loop);
	}

	////ImGui::SetCursorPos(ImVec2((MyWindowsSystem.getWindow().GetWindowWidth() - (width / scale)) * 0.5f, (MyWindowsSystem.getWindow().GetWindowHeight() - (height / scale)) * 0.5f));
	//ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
	//	ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));


}


AnimationComponent::AnimationComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _currentAnim{ "" }, _startingAnim{ "" }, _playOnce{ false },/*_currAnimation{ nullptr },*/ _currFrame{ 0 }, _timeDelay{ 0.5f }, _currentTimeDelay{ 0.5f }, _maxFrame{ 6 },
	_playAtCreation{ true }, _loop{ false }
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


void AnimationComponent::SetAnimationPlaying(bool set)
{
	_animationPlaying = set;
}

//Updates currentTimeDelay, as delay reaches 0, change to another frame
//When reaches max frame, frame start from 0 again.
void AnimationComponent::UpdateTimeDelay(float dt)
{
	_currentTimeDelay -= dt;
	if (_currentTimeDelay < 0.0f)
	{
		_currentTimeDelay = _timeDelay;
		_currFrame = _currFrame + 1;

		if (_currFrame > _maxFrame)
			_currFrame = 0;
	}
}


// get current playing animation
std::string& AnimationComponent::GetCurrAnim()
{
	return _currentAnim;
}

Texture2D* AnimationComponent::GetCurrentTexture()
{
	if (!_currentAnim.empty())	//If currentAnimation is not empty
	{
		if(!_currAnimationResource)
			_currAnimationResource = MyResourceManager.GetAnimationResource(_currentAnim);

		return _currAnimationResource->GetSpriteSheet();
	}	
	return nullptr;
}

Animation* AnimationComponent::GetAnimationResource()
{
	return _currAnimationResource;
}

void  AnimationComponent::SetStartFrame()
{
	_currFrame = 0;
}

void  AnimationComponent::SetMaxFrame(int maxFrame)
{
	_maxFrame = maxFrame;
}

void  AnimationComponent::ResetCurrTimeDelay()
{
	_currentTimeDelay = _timeDelay;
}

void  AnimationComponent::SetTimeDelay(std::string AnimationName)
{
	if (_animations.find(AnimationName) != _animations.end())
	{
		_timeDelay = _animations[AnimationName];
		return;
	}

	return;
	throw std::exception{ "Does not have AnimationType" };
}

void  AnimationComponent::setCurrentAnimation(std::string AnimationName)
{
	if (animationFileNameList.find(AnimationName) != animationFileNameList.end())
	{
		_currentAnim = animationFileNameList[AnimationName];
		return;
	}

	return;
	throw std::exception{ "Does not have AnimationType" };
}

void  AnimationComponent::SetAnimationResource()
{
	_currAnimationResource = MyResourceManager.GetAnimationResource(_currentAnim);
}

const std::map<AnimationComponent::AnimationName, AnimationComponent::AnimationFile>& AnimationComponent::GetAnimationDataFileList() const
{
	return animationFileNameList;
}

void  AnimationComponent::SerialiseComponent(Serialiser& document)
{
	//if (document.HasMember("Type") && document["Type"].IsString())
	//{
	//	_type = document["Type"].GetString();
	//}

	_animations.clear();
	animationFileNameList.clear();

	if (document.HasMember("AnimationComponent") && document["AnimationComponent"].IsBool())
		SetEnable(document["AnimationComponent"].GetBool());

	if (document.HasMember("AnimationTypes"))
	{
		for (int i = 0; i < document["AnimationTypes"].Size(); i++)
		{
			//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
			//{
			Serialiser datafile(document["AnimationTypes"][i]);

			_animations.insert(std::pair<AnimationName, timeDelay>(datafile["AnimationName"].GetString(), datafile["TimeDelay"].GetFloat()));
			animationFileNameList.insert(std::pair<AnimationName, AnimationFile>(datafile["AnimationName"].GetString(), datafile["AnimationType"].GetString()));
			//}
		}
	}

	if (document.HasMember("PlayAtCreation"))
	{
		_playAtCreation = document["PlayAtCreation"].GetBool();
	}

	if (document.HasMember("PlayInitLoop"))
	{
		_loop = document["PlayInitLoop"].GetBool();
	}

	if (document.HasMember("StartAnim"))
	{
		_startingAnim = document["StartAnim"].GetString();
		//SetCurrentAnim(_startingAnim);
	}

	//_currAnimation = MyResourceManager.GetAnimationResource(_startingAnim);
}


void  AnimationComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	if (!animationFileNameList.empty())
	{
		value.SetBool(GetEnable());
		prototypeDoc.AddMember("AnimationComponent", value);


		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : _animations)
			{
				object.SetObject();
				object.AddMember("AnimationType", rapidjson::StringRef(animationFileNameList[anim.first].c_str()), prototypeDoc.Allocator());
				object.AddMember("TimeDelay", rapidjson::Value(anim.second), prototypeDoc.Allocator());
				object.AddMember("AnimationName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());

				value.PushBack(object, prototypeDoc.Allocator());
			}
			prototypeDoc.AddMember("AnimationTypes", value);
		}

		value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
		prototypeDoc.AddMember("StartAnim", value);


		value.SetBool(_playAtCreation);
		prototypeDoc.AddMember("PlayAtCreation", value);

		value.SetBool(_loop);
		prototypeDoc.AddMember("PlayInitLoop", value);
	}


}


void  AnimationComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;


	if (!animationFileNameList.empty())
	{
		value.SetBool(GetEnable());
		prototypeDoc.AddMember("AnimationComponent", value, allocator);


		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : _animations)
			{
				object.SetObject();
				object.AddMember("AnimationType", rapidjson::StringRef(animationFileNameList[anim.first].c_str()), allocator);
				object.AddMember("TimeDelay", rapidjson::Value(anim.second), allocator);
				object.AddMember("AnimationName", rapidjson::StringRef(anim.first.c_str()), allocator);


				value.PushBack(object, allocator);
			}
			prototypeDoc.AddMember("AnimationTypes", value, allocator);
		}

		value.SetString(rapidjson::StringRef(_startingAnim.c_str()));
		prototypeDoc.AddMember("StartAnim", value, allocator);

		value.SetBool(_playAtCreation);
		prototypeDoc.AddMember("PlayAtCreation", value, allocator);

		value.SetBool(_loop);
		prototypeDoc.AddMember("PlayInitLoop", value, allocator);
	}
}

void  AnimationComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	AnimationComponent* protoAnimCom = dynamic_cast<AnimationComponent*>(protoCom);

	if (!protoAnimCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}


	bool addComponentIntoSceneFile = false;
	rapidjson::Value enable;
	rapidjson::Value animationsList;
	animationsList.SetArray();

	rapidjson::Value playAtCreation;
	rapidjson::Value loop;

	if (protoAnimCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	for (auto& anim : _animations)
	{
		//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
		//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
		//{
		addComponentIntoSceneFile = true;
		rapidjson::Value Obj;
		Obj.SetObject();

		rapidjson::Value strVal;

		strVal.SetString(animationFileNameList[anim.first].c_str(), animationFileNameList[anim.first].length(), allocator);
		Obj.AddMember("AnimationType", strVal, allocator);

		strVal.SetFloat(anim.second);
		Obj.AddMember("TimeDelay", strVal, allocator);

		strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
		Obj.AddMember("AnimationName", strVal, allocator);

		animationsList.PushBack(Obj, allocator);
		//}
	}

	rapidjson::Value startingAnim;

	if (protoAnimCom->_startingAnim.compare(_startingAnim) && !_startingAnim.empty())	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		startingAnim.SetString(_startingAnim.c_str(), _startingAnim.length(), allocator);
	}

	if (protoAnimCom->_playAtCreation != _playAtCreation)
	{
		addComponentIntoSceneFile = true;
		playAtCreation.SetBool(_playAtCreation);
	}

	if (protoAnimCom->_loop != _loop)
	{
		addComponentIntoSceneFile = true;
		loop.SetBool(_loop);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("AnimationComponent", enable, allocator);
		else
			value.AddMember("AnimationComponent", protoAnimCom->GetEnable(), allocator);


		if (!animationsList.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("AnimationTypes", animationsList, allocator);
		}

		if (!startingAnim.IsNull())
		{
			value.AddMember("StartAnim", startingAnim, allocator);
		}

		if (!playAtCreation.IsNull())
		{
			value.AddMember("PlayAtCreation", playAtCreation, allocator);
		}

		if (!loop.IsNull())
		{
			value.AddMember("PlayInitLoop", loop, allocator);
		}
	}
}

void AnimationComponent::Init()
{
	if (_playAtCreation)
	{
		if (_loop)
			SetCurrentAnim(_startingAnim);
		else
			SetCurrentAnimOnce(_startingAnim);
	}
}

void AnimationComponent::LoadResource()
{
#ifdef LEVELEDITOR
	for (auto& it : animationFileNameList)
	{
		if (MyResourceManager.AddNewAnimationResource({ it.second, MyResourceSystem.GetAnimationResourcePath(it.second) }))
		{
			Animation* temp = MyResourceManager.GetAnimationResource(it.second);
			MyResourceManager.AddNewTexture2DResource({ temp->spriteSheetName, MyResourceSystem.GetTexture2DResourcePath(temp->spriteSheetName) });
		}
	}
#endif // LEVELEDITOR
}
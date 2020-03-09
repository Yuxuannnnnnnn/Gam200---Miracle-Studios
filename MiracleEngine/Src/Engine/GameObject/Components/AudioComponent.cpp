#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"


void AudioComponent::PlayBGM(const std::string& soundName)
{
	MyAudioSystem.PlayBGM(std::get<0>(BackgroundSoundList[soundName]), std::get<1>(BackgroundSoundList[soundName]));	//Set fileName
	//MyAudioSystem.setVolumeBGM(std::get<1>(SoundList[soundName]);	//Set Volume
}

void AudioComponent::PlaySFX(const std::string& soundName)
{
	MyAudioSystem.PlaySFX(std::get<0>(SFXList[soundName]), std::get<1>(SFXList[soundName]));	//Set fileName
	//MyAudioSystem.setVolumeSFX(std::get<1>(SoundList[soundName]);	//Set Volume
	//MyAudioSystem.setLoopSFX(std::get<2>(SoundList[soundName]);	//Set number of Loops
}



AudioComponent::AudioComponent()
	:SFXList{},
	BackgroundSoundList{},
	currentBGMName{""},
	currentSFXName{""}
	//_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	//_fileName{ std::string() }
	//_fileTrackLength{ 0 },
	//_lifetimeCurrent{ 0 },
	//_loop{ false },
	//_lifetimeTotal{ 0 }
{
}



AudioComponent::AudioComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId)
	//_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	//_fileName{ std::string() }
	//_fileTrackLength{ 0 },
	//_lifetimeCurrent{ 0 },
	//_loop{ false },
	//_lifetimeTotal{ 0 }
{
	if (component)//Cloning Component
	{
		AudioComponent* audioComponent = dynamic_cast<AudioComponent*>(component);
		//_typeIdAudio = audioComponent->_typeIdAudio;
		//_fileName = audioComponent->_fileName;
		//_fileTrackLength = audioComponent->_fileTrackLength;
		//_lifetimeCurrent = audioComponent->_lifetimeCurrent;
		//_loop = audioComponent->_loop;
	}
}

void AudioComponent::StopBGM()
{
	MyAudioSystem.StopBGM();
}

void AudioComponent::StopSFX()
{
	MyAudioSystem.StopSFX();
}


void AudioComponent::StopAllSound()
{
	MyAudioSystem.StopAllSound();
}


//bool AudioComponent::IsBGM()
//{
//	return _isBGM;
//}
//
//void AudioComponent::SetIsBGM(bool isbgm)
//{
//	_isBGM = isbgm;
//}
//
//unsigned& AudioComponent::GetTypeId()
//{
//	return _typeIdAudio;
//}
//
//std::string& AudioComponent::GetFileName()
//{
//	return _fileName;
//}

std::string AudioComponent::ComponentName() const
{
	return "Audio Component";
}





void AudioComponent::Inspect()
{
	IComponent::Inspect();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	static std::unordered_map<std::string, Sound*>& AudioList = MyResourceSystem.GetSoundMap();
	AudioList.insert(std::pair<std::string, Sound*>("Choose a Sound File here", nullptr));
	std::vector<const char*> AudioTypeList(AudioList.size() + 1);


	//std::map<audioName, std::tuple<fileName, volume, NumOfloops>> SFXList;	//Add SoundEffects
	//
	//std::map<audioName, std::tuple<fileName, volume>> BackgroundSoundList;	//Add BackgroundMusic
	//
	//std::string currentBGM;	//When inspection changes the values, have to inform the audioSystem incase the soundtrack is playing currently
	//std::string currentSFX;
	//std::get<0>(SFXList[soundName]

	int a = 0;
	AudioTypeList[a] = "Choose a Sound File here";
	a++;
	for (auto& audioPair : AudioList)
	{
		const char* ptr = audioPair.first.c_str();

		AudioTypeList[a] = ptr;
		a++;
	}

	{
		int i = 0;
		int select = 0;

		std::vector<audioName> NameList;
		std::vector<audioName> UnchangedNameList;

		for (auto& sfxPairTuple : SFXList)
		{
			//NameList.push_back(animation.first);
			//UnchangedNameList.push_back(animation.first);

			ImGui::Spacing();

			if (i < SFXList.size())
			{
				for (int j = 0; j < AudioTypeList.size(); j++)
				{
					if (!strncmp(AudioTypeList[j], std::get<0>(sfxPairTuple.second).c_str(),
						AudioList.find(AudioTypeList[j])->first.size()))
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

			if (std::get<0>(sfxPairTuple.second).empty())
			{
				strncpy(buf[i], "Choose a Sound File here", 31);
			}
			else
			{
				strncpy(buf[i], std::get<0>(sfxPairTuple.second).c_str(),
					std::get<0>(sfxPairTuple.second).size() + 2);
			}


			std::string SoundFile = "SFX File##" + std::to_string(i);

			if (DropDownBars[i]->ComboFilter(SoundFile.c_str(), buf[i], 128,
				AudioTypeList, AudioTypeList.size(), s[i],
				std::get<0>(sfxPairTuple.second), openArray[i], i))
			{
			}


			ImGui::Spacing();
			ImGui::Spacing();

			std::string VolumeString = "Volume##" + std::to_string(i);
			if (ImGui::SliderFloat(VolumeString.c_str(), &std::get<1>(sfxPairTuple.second), 0, 1))
			{
			}

			ImGui::Spacing();
			ImGui::Spacing();

			std::string NumOfLoopsString = "Num Of Loops##" + std::to_string(i);
			if (ImGui::InputInt(NumOfLoopsString.c_str(), &std::get<2>(sfxPairTuple.second)))
			{
			}


			ImGui::Spacing();
			ImGui::Spacing();

			//AnimationName is not changed in the loop, saved in NameList, ChangedList and UnchangedNameList
			std::string SFXNameString = "SFX Name##" + std::to_string(i);
			char SFXName[128] = "\0";
			bool done;
			strncpy(SFXName, sfxPairTuple.first.c_str(), sfxPairTuple.first.length() + 2);
			if (done = ImGui::InputText(SFXNameString.c_str(), SFXName, 128, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				std::string length(SFXName);
				if (int i = strncmp(SFXName, sfxPairTuple.first.c_str(), length.length()))
				{
					NameList.push_back(std::string(SFXName));
					UnchangedNameList.push_back(sfxPairTuple.first);
				}
			}


			i++;

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::SameLine(200);

			std::string Play = "Play SFX##" + std::to_string(i);
			if (ImGui::Button(Play.c_str()))
			{
				//MyAnimationWindow.SetAnimationWindow(animation.first, animation.second, animationFileNameList[animation.first]);
				MyAudioSystem.PlaySFX(std::get<0>(sfxPairTuple.second), std::get<1>(sfxPairTuple.second));
			}

			ImGui::SameLine(270);

			std::string Stop = "Stop SFX##" + std::to_string(i);
			if (ImGui::Button(Stop.c_str()))
			{
				//MyAnimationWindow.SetAnimationWindow(animation.first, animation.second, animationFileNameList[animation.first]);
				//MyAudioSystem.StopSFXSound(); - Need this function in case background music is running in the background, thus should not stop all music audio from playing
				MyAudioSystem.StopAllSound();
			}

			ImGui::SameLine(340);

			std::string Delete = "Delete SFX##" + std::to_string(i);
			if (ImGui::Button(Delete.c_str()))
			{
				SFXList.erase(sfxPairTuple.first);
				break;
			}

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Separator();
		}


		std::map<audioName, std::tuple<fileName, volume, NumOfloops>> tempNameFileList;
		//SFXName is changed here, key pair is extracted and changed and inserted back into the maps

		for (auto& NamePairTuple : SFXList)
		{
			std::pair<audioName, std::tuple<fileName, volume, NumOfloops> > nameFile;

			nameFile = NamePairTuple;

			for (int i = 0; i < UnchangedNameList.size(); i++)
			{
				if (!UnchangedNameList[i].compare(nameFile.first))
				{
					nameFile.first = NameList[i];
					break;
				}
			}
			tempNameFileList.insert(nameFile);

		}

		SFXList.clear();

		SFXList = tempNameFileList;


	}

	{
		int i = 0;
		int select = 0;

		std::vector<audioName> NameList;
		std::vector<audioName> UnchangedNameList;

		for (auto& sfxPairTuple : BackgroundSoundList)
		{
			//NameList.push_back(animation.first);
			//UnchangedNameList.push_back(animation.first);

			ImGui::Spacing();

			if (i < SFXList.size())
			{
				for (int j = 0; j < AudioTypeList.size(); j++)
				{
					if (!strncmp(AudioTypeList[j], std::get<0>(sfxPairTuple.second).c_str(),
						AudioList.find(AudioTypeList[j])->first.size()))
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

			if (std::get<0>(sfxPairTuple.second).empty())
			{
				strncpy(buf[i], "Choose a Sound File here", 31);
			}
			else
			{
				strncpy(buf[i], std::get<0>(sfxPairTuple.second).c_str(),
					std::get<0>(sfxPairTuple.second).size() + 2);
			}


			std::string SoundFile = "Background Audio File##" + std::to_string(i);

			if (DropDownBars[i]->ComboFilter(SoundFile.c_str(), buf[i], 128,
				AudioTypeList, AudioTypeList.size(), s[i],
				std::get<0>(sfxPairTuple.second), openArray[i], i))
			{
			}


			ImGui::Spacing();
			ImGui::Spacing();

			std::string VolumeString = "Volume##" + std::to_string(i);
			if (ImGui::SliderFloat(VolumeString.c_str(), &std::get<1>(sfxPairTuple.second), 0, 1))
			{
			}


			ImGui::Spacing();
			ImGui::Spacing();

			//AnimationName is not changed in the loop, saved in NameList, ChangedList and UnchangedNameList
			std::string SFXNameString = "Background Audio Name##" + std::to_string(i);
			char SFXName[128] = "\0";
			bool done;
			strncpy(SFXName, sfxPairTuple.first.c_str(), sfxPairTuple.first.length() + 2);
			if (done = ImGui::InputText(SFXNameString.c_str(), SFXName, 128, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				std::string length(SFXName);
				if (int i = strncmp(SFXName, sfxPairTuple.first.c_str(), length.length()))
				{
					NameList.push_back(std::string(SFXName));
					UnchangedNameList.push_back(sfxPairTuple.first);
				}
			}


			i++;

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::SameLine(200);

			std::string Play = "Play BGM##" + std::to_string(i);
			if (ImGui::Button(Play.c_str()))
			{
				MyAudioSystem.PlayBGM(std::get<0>(sfxPairTuple.second), std::get<1>(sfxPairTuple.second));
				//MyAnimationWindow.SetAnimationWindow(animation.first, animation.second, animationFileNameList[animation.first]);
			}

			ImGui::SameLine(270);

			std::string Stop = "Stop BGM##" + std::to_string(i);
			if (ImGui::Button(Stop.c_str()))
			{
				MyAudioSystem.StopAllSound();
				//MyAnimationWindow.SetAnimationWindow(animation.first, animation.second, animationFileNameList[animation.first]);
			}

			ImGui::SameLine(340);

			std::string Delete = "Delete BGM##" + std::to_string(i);
			if (ImGui::Button(Delete.c_str()))
			{
				BackgroundSoundList.erase(sfxPairTuple.first);
				break;
			}

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Separator();
		}


		std::map<audioName, std::tuple<fileName, volume>> tempNameFileList;
		//SFXName is changed here, key pair is extracted and changed and inserted back into the maps

		for (auto& NamePairTuple : BackgroundSoundList)
		{
			std::pair<audioName, std::tuple<fileName, volume> > nameFile;

			nameFile = NamePairTuple;

			for (int i = 0; i < UnchangedNameList.size(); i++)
			{
				if (!UnchangedNameList[i].compare(nameFile.first))
				{
					nameFile.first = NameList[i];
					break;
				}
			}
			tempNameFileList.insert(nameFile);

		}

		BackgroundSoundList.clear();

		BackgroundSoundList = tempNameFileList;
	}

		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::Button("Add New SFX"))
		{
			SFXList.insert(std::pair<audioName, std::tuple<fileName, volume, NumOfloops>>("", { "", 0.0, 0 }));
		}

		ImGui::SameLine(150);

		if (ImGui::Button("Add New Background Audio"))
		{
			BackgroundSoundList.insert(std::pair<audioName, std::tuple<fileName, volume>>("", { "", 0.0}));
		}


		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();










	

	//if (!_animations.empty())
	//{
	//	ImGui::Spacing();
	//	ImGui::Spacing();
	//	std::vector<const char*> AnimationNameList(_animations.size());
	//	//list[0] = "Choose a Texture ";
	//
	//
	//	int a = 0;
	//	int select1 = 0;
	//	for (auto& NameTime : _animations)
	//	{
	//		const char* ptr = NameTime.first.c_str();
	//
	//		AnimationNameList[a] = ptr;
	//		if (!strncmp(ptr, _startingAnim.c_str(), _startingAnim.length()))
	//		{
	//			select1 = a;
	//		}
	//
	//		a++;
	//	}
	//
	//
	//	char buf[128] = "";
	//	static ImGuiFunctions function;
	//	static bool op = true;
	//	static bool* open = &op;
	//	static ComboFilterState s{ select1, 0 };
	//
	//	//static std::vector< bool *(const char* id, char* buffer, int bufferlen, /*const char** hints*/ std::vector<const char*> hints,
	//	//	int num_hints, ImGuiFunctions::ComboFilterState & s, std::string & _filename)> 
	//
	//
	//	if (_startingAnim.empty())
	//	{
	//		strncpy(buf, "Choose an AnimationName here", 30);
	//	}
	//	else
	//	{
	//		strncpy(buf, _startingAnim.c_str(), _startingAnim.size() + 2);
	//	}
	//
	//
	//	std::string StartingAnim = "StartingAnim##" + std::to_string(i);
	//
	//	if (function.ComboFilter(StartingAnim.c_str(), buf, 128, AnimationNameList, AnimationNameList.size(), s, _startingAnim, open, i))
	//	{
	//		//puts(buf);
	//	}
	//}
	



	//std::vector<const char*> list( AudioList.size() + 1);
	//list[0] = "Audio Files ";
	//static const char* name = list[0];
	//
	//int i = 1;
	//static int select;
	//for(auto audioPair = AudioList.begin(); audioPair != AudioList.end(); audioPair++)
	//{
	//	const char* ptr = audioPair->first.c_str();
	//	list[i] = ptr;
	//	if (!strncmp(audioPair->first.c_str(), _fileName.c_str(), 20))
	//	{
	//		select = i;
	//	}
	//	i++;
	//}
	////ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));
	//
	//
	//if (ImGui::BeginCombo(" ", list[select], 0)) // The second parameter is the label previewed before opening the combo.
	//{
	//	for (int n = 0; n < list.size(); n++)
	//	{
	//		bool is_selected = (name == list[n]);
	//		if (ImGui::Selectable(list[n], is_selected)) 
	//		{
	//			_fileName = list[n];
	//			select = n;
	//		}
	//
	//		//if (is_selected);
	//		//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
	//
	//	}
	//	ImGui::EndCombo();
	//}

}
void AudioComponent::SerialiseComponent(Serialiser& document)
{
	//if (document.HasMember("A.TypeId") && document["A.TypeId"].IsInt())
	//	_typeIdAudio = document["A.TypeId"].GetUint();

	/*
	if (document.HasMember("A.FileName") && document["A.FileName"].IsString())
		_fileName = std::string(document["A.FileName"].GetString());

	if (document.HasMember("IsBGM") && document["IsBGM"].IsBool())
		_isBGM = document["IsBGM"].GetBool();
		*/

	SFXList.clear();
	BackgroundSoundList.clear();

	if (document.HasMember("AudioComponent") && document["AudioComponent"].IsBool())
		SetEnable(document["AudioComponent"].GetBool());

	if (document.HasMember("SFXList"))
	{
		for (int i = 0; i < document["SFXList"].Size(); i++)
		{
			//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
			//{
			Serialiser datafile(document["SFXList"][i]);

			SFXList.insert(std::pair<audioName, std::tuple<fileName, volume, NumOfloops>>(datafile["SFXName"].GetString(),
				{ datafile["fileName"].GetString() , datafile["volume"].GetFloat() , datafile["NumOfloops"].GetInt() }));
			//}
		}
	}

	if (document.HasMember("BackgroundSoundList"))
	{
		for (int i = 0; i < document["BackgroundSoundList"].Size(); i++)
		{
			//if (std::find(_animations.begin(), _animations.end(), document["AnimationTypes"][i].GetString()) == _animations.end())
			//{
			Serialiser datafile(document["BackgroundSoundList"][i]);

			BackgroundSoundList.insert(std::pair<audioName, std::tuple<fileName, volume>>(datafile["BGMName"].GetString(),
				{ datafile["fileName"].GetString() , datafile["volume"].GetFloat() }));
			//}
		}
	}
}


void AudioComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("AudioComponent", value);

	if (!SFXList.empty())	//If the object has the component but no sound is added to the list, do not deserialise
	{
		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : SFXList)
			{
				object.SetObject();
				object.AddMember("SFXName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());
				object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), prototypeDoc.Allocator());
				object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), prototypeDoc.Allocator());
				object.AddMember("NumOfloops", rapidjson::Value(std::get<2>(anim.second)), prototypeDoc.Allocator());

				value.PushBack(object, prototypeDoc.Allocator());
			}
			prototypeDoc.AddMember("SFXList", value);
		}
	}

	if (!BackgroundSoundList.empty())	//If the object has the component but no sound is added to the list, do not deserialise the component
	{
		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : BackgroundSoundList)
			{
				object.SetObject();
				object.AddMember("BGMName", rapidjson::StringRef(anim.first.c_str()), prototypeDoc.Allocator());
				object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), prototypeDoc.Allocator());
				object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), prototypeDoc.Allocator());

				value.PushBack(object, prototypeDoc.Allocator());
			}
			prototypeDoc.AddMember("BackgroundSoundList", value);
		}
	}

}

void AudioComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;


	value.SetBool(GetEnable());
	prototypeDoc.AddMember("AudioComponent", value, allocator);

	if (!SFXList.empty())	//If the object has the component but no sound is added to the list, do not deserialise
	{
		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : SFXList)
			{
				object.SetObject();
				object.AddMember("SFXName", rapidjson::StringRef(anim.first.c_str()), allocator);
				object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), allocator);
				object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), allocator);
				object.AddMember("NumOfloops", rapidjson::Value(std::get<2>(anim.second)), allocator);

				value.PushBack(object, allocator);
			}
			prototypeDoc.AddMember("SFXList", value, allocator);
		}
	}

	if (!BackgroundSoundList.empty())	//If the object has the component but no sound is added to the list, do not deserialise the component
	{
		value.SetArray();
		{
			rapidjson::Value object;
			for (auto& anim : BackgroundSoundList)
			{
				object.SetObject();
				object.AddMember("BGMName", rapidjson::StringRef(anim.first.c_str()), allocator);
				object.AddMember("fileName", rapidjson::StringRef(std::get<0>(anim.second).c_str()), allocator);
				object.AddMember("volume", rapidjson::Value(std::get<1>(anim.second)), allocator);

				value.PushBack(object, allocator);
			}
			prototypeDoc.AddMember("BackgroundSoundList", value, allocator);
		}
	}
}

//SceneFile Sent in must be Document[ClonableObjects][objectfile or i]
void AudioComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	AudioComponent* protoAnimCom = dynamic_cast<AudioComponent*>(protoCom);

	if (!protoAnimCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}


	bool addComponentIntoSceneFile = false;
	rapidjson::Value enable;
	rapidjson::Value jsonSFXList;
	jsonSFXList.SetArray();

	rapidjson::Value jsonBackgroundSoundList;
	jsonBackgroundSoundList.SetArray();


	if (protoAnimCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	for (auto& anim : SFXList)
	{
		//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
		//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
		//{
		addComponentIntoSceneFile = true;
		rapidjson::Value Obj;
		Obj.SetObject();

		rapidjson::Value strVal;

		strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
		Obj.AddMember("SFXName", strVal, allocator);

		strVal.SetString(std::get<0>(anim.second).c_str(), std::get<0>(anim.second).length(), allocator);
		Obj.AddMember("fileName", strVal, allocator);

		strVal.SetFloat(std::get<1>(anim.second));
		Obj.AddMember("volume", strVal, allocator);

		strVal.SetInt(std::get<2>(anim.second));
		Obj.AddMember("NumOfloops", strVal, allocator);

		jsonSFXList.PushBack(Obj, allocator);
		//}
	}

	for (auto& anim : BackgroundSoundList)
	{
		//Search Prototype for animation file, if dont have then add. OR if time delay is different then add the pair
		//if (protoAnimCom->_animations.find(anim.first) == protoAnimCom->_animations.end() || protoAnimCom->_animations[anim.first] != anim.second)
		//{
		addComponentIntoSceneFile = true;
		rapidjson::Value Obj;
		Obj.SetObject();

		rapidjson::Value strVal;

		strVal.SetString(anim.first.c_str(), anim.first.length(), allocator);
		Obj.AddMember("BGMName", strVal, allocator);

		strVal.SetString(std::get<0>(anim.second).c_str(), std::get<0>(anim.second).length(), allocator);
		Obj.AddMember("fileName", strVal, allocator);

		strVal.SetFloat(std::get<1>(anim.second));
		Obj.AddMember("volume", strVal, allocator);

		jsonBackgroundSoundList.PushBack(Obj, allocator);
		//}
	}



	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("AudioComponent", enable, allocator);
		else
			value.AddMember("AudioComponent", protoAnimCom->GetEnable(), allocator);


		if (!jsonSFXList.IsNull())	//if rapidjson::value container is not empty
		{
			value.AddMember("SFXList", jsonSFXList, allocator);
		}

		if (!jsonBackgroundSoundList.IsNull())
		{
			value.AddMember("BackgroundSoundList", jsonBackgroundSoundList, allocator);
		}
	}
}

void AudioComponent::Init()
{

}

void AudioComponent::LoadResource()
{
#ifdef LEVELEDITOR
	for (auto& it : SFXList)
		MyResourceManager.AddNewAudioResource({ std::get<0>(it.second), MyResourceSystem.GetSoundResourcePath(std::get<0>(it.second)) });

	for (auto& it : BackgroundSoundList)
		MyResourceManager.AddNewLoopAudioResource({ std::get<0>(it.second), MyResourceSystem.GetLoopSoundResourcePath(std::get<0>(it.second)) });
#endif // LEVELEDITOR
}
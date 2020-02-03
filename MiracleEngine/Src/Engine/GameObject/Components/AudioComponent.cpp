#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"


void AudioComponent::PlayBGM(const std::string& soundName)
{
	MyAudioSystem.PlayBGM(std::get<0>(SoundList[soundName]));	//Set fileName
	//MyAudioSystem.setVolumeBGM(std::get<1>(SoundList[soundName]);	//Set Volume
}

void AudioComponent::PlaySFX(const std::string& soundName)
{
	MyAudioSystem.PlaySFX(std::get<0>(SoundList[soundName]));	//Set fileName
	//MyAudioSystem.setVolumeSFX(std::get<1>(SoundList[soundName]);	//Set Volume
	//MyAudioSystem.setLoopSFX(std::get<2>(SoundList[soundName]);	//Set number of Loops
}



AudioComponent::AudioComponent()
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

	static auto AudioList = MyResourceSystem.GetSoundList();


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

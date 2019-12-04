#pragma once
#include "PrecompiledHeaders.h"
#include "AudioComponent.h"



AudioComponent::AudioComponent() :
	_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	_fileName{ std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false },
	_lifetimeTotal{ 0 }
{
}



AudioComponent::AudioComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId),
	_typeIdAudio{ (unsigned)TypeIdAudio::NONE },
	_fileName{ std::string() },
	_fileTrackLength{ 0 },
	_lifetimeCurrent{ 0 },
	_loop{ false },
	_lifetimeTotal{ 0 }
{
	if (component)//Cloning Component
	{
		AudioComponent* audioComponent = dynamic_cast<AudioComponent*>(component);
		_typeIdAudio = audioComponent->_typeIdAudio;
		_fileName = audioComponent->_fileName;
		_fileTrackLength = audioComponent->_fileTrackLength;
		_lifetimeCurrent = audioComponent->_lifetimeCurrent;
		_loop = audioComponent->_loop;
	}
}

bool AudioComponent::IsBGM()
{
	return _isBGM;
}

void AudioComponent::SetIsBGM(bool isbgm)
{
	_isBGM = isbgm;
}

unsigned& AudioComponent::GetTypeId()
{
	return _typeIdAudio;
}

std::string& AudioComponent::GetFileName()
{
	return _fileName;
}

std::string AudioComponent::ComponentName() const
{
	return "Audio Component";
}


void AudioComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("A.TypeId") && document["A.TypeId"].IsInt())
		_typeIdAudio = document["A.TypeId"].GetUint();

	if (document.HasMember("A.FileName") && document["A.FileName"].IsString())
		_fileName = std::string(document["A.FileName"].GetString());

	if (document.HasMember("IsBGM") && document["IsBGM"].IsBool())
		_isBGM = document["IsBGM"].GetBool();


}

void AudioComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetInt(_typeIdAudio);
	prototypeDoc.AddMember("A.TypeId", value);

	value.SetString(rapidjson::StringRef(_fileName.c_str()));
	prototypeDoc.AddMember("A.FileName", value);

	value.SetBool(_isBGM);
	prototypeDoc.AddMember("IsBGM", value);
}

void AudioComponent::Inspect()
{
	IComponentSystem::Inspect();


	static auto AudioList = ResourceManager::GetInstance().GetSoundList();

	std::vector<const char*> list( AudioList.size() + 1);
	list[0] = "Audio Files ";

	int i = 1;
	static int select;
	for(auto audioPair = AudioList.begin(); audioPair != AudioList.end(); audioPair++)
	{
		const char* ptr = audioPair->first.c_str();
		list[i] = ptr;
		if (strncmp(audioPair->first.c_str(), _fileName.c_str(), 20) && (item_current_fileName== nullptr))
		{
			select = i;
		}
		i++;
	}
	//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));

	item_current_fileName = list[select];            // Here our selection is a single pointer stored outside the object.


	if (ImGui::BeginCombo(" ", item_current_fileName, 0)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < list.size(); n++)
		{
			bool is_selected = (item_current_fileName == list[n]);
			if (ImGui::Selectable(list[n], is_selected))
			{
				item_current_fileName = list[n];
				select = n;
			}

			//if (is_selected);
			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

		}
		ImGui::EndCombo();
	}

}

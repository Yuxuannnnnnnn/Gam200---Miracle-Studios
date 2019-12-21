#pragma once
#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"


// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponentSystem
{
private:
	unsigned _typeIdAudio;
	std::string _fileName;
	bool _isBGM;

	unsigned _fileTrackLength;
	size_t _lifetimeTotal;
	size_t _lifetimeCurrent;
	bool _loop;

private:
	//Level Editor
	const char* item_current_fileName;

public:
	AudioComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	bool IsBGM();
	void SetIsBGM(bool isbgm);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	void SaveComponent()
	{
		_fileName = item_current_fileName;
	}


	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

};


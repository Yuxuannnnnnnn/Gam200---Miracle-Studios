#pragma once
#include "../IComponent.h"


// For both audio componentand graphic component, serialize a string and a typeid
enum class TypeIdAudio {
	NONE = 0,

};

class AudioComponent : public IComponent
{
private:
	unsigned _typeIdAudio;
	std::string _fileName;
	bool _isBGM;

	unsigned _fileTrackLength;
	size_t _lifetimeTotal;
	size_t _lifetimeCurrent;
	bool _loop;


public:
	AudioComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);

	bool IsBGM();
	void SetIsBGM(bool isbgm);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;



	AudioComponent();
	~AudioComponent() = default;

	unsigned& GetTypeId();

	std::string& GetFileName();

};



#ifndef OPTIONSCRIPT_H
#define	OPTIONSCRIPT_H

#include "GameObject/Components/Logic/IScript2.h"

class OptionScript : public IScript2
{
public:
	bool _currFullscreen, _newFullscreen;

	std::vector<Vector3> _allResolution;

	int Index;
	Vector3 _currResolution, _newResolution;
	int _currMasterSound, _newMasterSound,
		_currMusic, _newMusic,
		_currSFX, _newSFX;

	UIComponent * _tickFullscreen, * _textResolution,
		* _textMsound, * _textMus, * _textSfx;

	OptionScript();

	OptionScript* Clone();

	void SetNewFullscreen();
	void IncreaseResolution();
	void DecreaseResolution();
	Vector3 DisplayNewResolution();
	void IncreaseMasterSound();
	void DecreaseMasterSound();
	void IncreaseMusic();
	void DecreaseMusic();
	void IncreaseSFX();
	void DecreaseSFX();

	std::string IntToFileName(int i);

	void ApplySettings();
	void DiscardSettings();


	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect()
	{

	}

	// InUpEx
	void Init();
	void Update(double dt);

};

#endif

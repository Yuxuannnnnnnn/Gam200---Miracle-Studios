
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
	float _currMasterSound, _newMasterSound,
		_currMusic, _newMusic, _adjustedMusic,
		_currSFX, _newSFX, _adjustedSFX;

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


	void ApplySettings();
	void DiscardSettings();







	void SerialiseComponent(Serialiser& document) {}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
	void Inspect() {}
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) {}
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) {}

	// override these functions
	void OnMouseDown();
	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();

	// InUpEx
	void Init();
	void Update(double dt);
	void Exit();

};

#endif

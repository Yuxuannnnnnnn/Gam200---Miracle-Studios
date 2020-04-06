#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef OPTIONSCRIPT_H
#define	OPTIONSCRIPT_H

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

	void SetNewFullscreen()
	{
		_newFullscreen = !_newFullscreen;
	}
	void IncreaseResolution()
	{
		Index++;
		if (Index > _allResolution.size())
			Index = _allResolution.size(); // check if correct
	}
	void DecreaseResolution()
	{
		Index--;
		if (Index < 0)
			Index = 0;
	}
	void DisplayNewResolution()
	{
		// based on index, return the vector3 of the 
	}
	void IncreaseMasterSound()
	{
		_newMasterSound += 0.1f;
		if (_newMasterSound > 1.0f)
			_newMasterSound = 1.0f;
	}
	void DecreaseMasterSound()
	{
		_newMasterSound -= 0.1f;
		if (_newMasterSound < 0.0f)
			_newMasterSound = 0.0f;
	}
	void IncreaseMusic()
	{
		_newMusic += 0.1f;
		if (_newMusic > 1.0f)
			_newMusic = 1.0f;
	}
	void DecreaseMusic()
	{
		_newMusic -= 0.1f;
		if (_newMusic < 0.0f)
			_newMusic = 0.0f;
	}
	void IncreaseSFX()
	{
	_newSFX += 0.1f;
	if (_newSFX > 1.0f)
		_newSFX = 1.0f;
	}
	void DecreaseSFX()
	{
		_newSFX -= 0.1f;
		if (_newSFX < 0.0f)
			_newSFX = 0.0f;
	}


	void ApplySettings()
	{
		// sets all new to current
		_currFullscreen = _newFullscreen;
		_currResolution = _allResolution[Index];
		_currMasterSound = _newMasterSound;
		_currMusic = _newMusic;
		_currSFX = _newSFX;
		// set adjusted Music & SFX
		_adjustedMusic = _newMusc * _newMasterSound;
		_adjustedSFX = _newSFX * _newMasterSound;

	}
	void DiscardSettings()
	{
		// sets all new to current
		_newFullscreen = _currFullscreen;
		_newResolution = _currResolution;
		_newMasterSound = _currMasterSound;
		_newMusic = _currMusic;
		_newSFX = _currSFX;
		//// set adjusted Music & SFX
		//_adjustedMusic = _newMusc * _newMasterSound;
		//_adjustedSFX = _newSFX * _newMasterSound;
	}








	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect()
	{

	}

	// override these functions
	void OnMouseDown();
	void OnMouseEnter();
	void OnMouseOver();
	void OnMouseExit();

	// InUpEx
	void Init();
	void Update();
	void Exit();

};

#endif

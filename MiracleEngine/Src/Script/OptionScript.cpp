#include "PrecompiledHeaders.h"
#include "Script/OptionScript.h"

OptionScript::OptionScript() :
	_currFullscreen{ false }, _newFullscreen{ false },
	Index{ 0 },
	_currMasterSound{ 0.f }, _newMasterSound{ 0.f },
	_currMusic{ 0.f }, _newMusic{ 0.f }, _adjustedMusic{ 0.f },
	_currSFX{ 0.f }, _newSFX{ 0.f }, _adjustedSFX{ 0.f }
{
}

OptionScript* OptionScript::Clone()
{
	return new OptionScript(*this);
}

void OptionScript::SetNewFullscreen()
{
	_newFullscreen = !_newFullscreen;
}
void OptionScript::IncreaseResolution()
{
	Index++;
	if (Index > _allResolution.size())
		Index = _allResolution.size(); // check if correct
}
void OptionScript::DecreaseResolution()
{
	Index--;
	if (Index < 0)
		Index = 0;
}
Vector3 OptionScript::DisplayNewResolution()
{
	// based on index, return the vector3 of the 
	return _allResolution[Index];
}
void OptionScript::IncreaseMasterSound()
{
	_newMasterSound += 0.1f;
	if (_newMasterSound > 1.0f)
		_newMasterSound = 1.0f;
}
void OptionScript::DecreaseMasterSound()
{
	_newMasterSound -= 0.1f;
	if (_newMasterSound < 0.0f)
		_newMasterSound = 0.0f;
}
void OptionScript::IncreaseMusic()
{
	_newMusic += 0.1f;
	if (_newMusic > 1.0f)
		_newMusic = 1.0f;
}
void OptionScript::DecreaseMusic()
{
	_newMusic -= 0.1f;
	if (_newMusic < 0.0f)
		_newMusic = 0.0f;
}
void OptionScript::IncreaseSFX()
{
	_newSFX += 0.1f;
	if (_newSFX > 1.0f)
		_newSFX = 1.0f;
}
void OptionScript::DecreaseSFX()
{
	_newSFX -= 0.1f;
	if (_newSFX < 0.0f)
		_newSFX = 0.0f;
}

void OptionScript::ApplySettings()
{
	// sets all new to current
	_currFullscreen = _newFullscreen;
	_currResolution = _allResolution[Index];
	_currMasterSound = _newMasterSound;
	_currMusic = _newMusic;
	_currSFX = _newSFX;
	// set adjusted Music & SFX
	_adjustedMusic = _newMusic * _newMasterSound;
	_adjustedSFX = _newSFX * _newMasterSound;

}
void OptionScript::DiscardSettings()
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

void OptionScript::OnMouseDown()
{
	;
}

void OptionScript::OnMouseEnter()
{
	;
}
void OptionScript::OnMouseOver()
{
	;
}
void OptionScript::OnMouseExit()
{
	;
}

void OptionScript::Update(double dt)
{

}

void OptionScript::Init()
{
	_allResolution.push_back({ 1920, 1080, 1 });
}
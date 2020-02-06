#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class EntrancePortal : public IScript2
{
	std::string _closePortalFileName;
	std::string _openPortalFileName;

	std::string _nextScene;

	int _progressCount;

	bool _clear;
	GraphicComponent* _graphicComponent;
	IScript2* _playerScript;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	EntrancePortal();
	EntrancePortal* Clone();

	virtual void Init() override;
	void Update(double dt);

	void OpenPortal();

	void OnCollision2DStay(Collider2D* other) override;
};

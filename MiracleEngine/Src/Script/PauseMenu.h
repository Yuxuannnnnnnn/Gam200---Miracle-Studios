#pragma once
#include "GameObject/Components/Logic/IScript2.h"

class PauseMenu : public IScript2
{
private:
	int _numOfObject;
	bool _init;

	std::vector<int> _objectLinkID;
	std::vector<GameObject*> _object;
public:

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void Inspect();

	PauseMenu();
	~PauseMenu();
	PauseMenu* Clone();

	virtual void Init() override;
	void Update(double dt);

	void EnablePauseMenu(bool t = true);
};


#pragma once

class ISystem {

	ISystem() {}
	virtual ~ISystem() {}

public:
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Exit() = 0;
};
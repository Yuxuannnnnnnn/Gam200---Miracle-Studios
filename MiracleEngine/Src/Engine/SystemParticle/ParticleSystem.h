#pragma once
#include "GameObject/Components/ParticleSystemComponent.h"

class ParticleSystem final
{
public:
	ParticleSystem() = default;
	~ParticleSystem() {}

	ParticleSystem(const ParticleSystem& rhs) = delete;
	ParticleSystem& operator= (const ParticleSystem& rhs) = delete;

	void Update(double dt);

	void Draw();
};
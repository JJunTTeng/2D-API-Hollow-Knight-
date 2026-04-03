#pragma once
#include "CComponent.h"

struct Particle
{
	Vec2 pos;
	Vec2 vel;
	float life;
};


class CParticles : public CComponent
{
public:
	void EmitCircle(int count);
	float RandomRange(float min, float max);

	std::vector<Particle*> GetParticle() { return particles; }
	
	virtual void FinalTick()override;
	void Render();
public:
	CParticles();
	~CParticles();

private:
	std::vector<Particle*> particles;
};


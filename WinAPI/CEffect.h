#pragma once
#include "CObj.h"

class CParticles;
class CEffect : public CObj
{
public:
	CEffect();
	~CEffect();

    virtual void Begin()override;
    virtual void Tick() override;
    virtual void Render() override;

private:
	CParticles* m_Particles;

};


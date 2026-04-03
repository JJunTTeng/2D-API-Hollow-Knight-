#include "pch.h"
#include "CEffect.h"

#include "CParticles.h"

CEffect::CEffect()
{

}

CEffect::~CEffect()
{
}

void CEffect::Begin()
{
	m_Particles = (CParticles*)AddComponent(new CParticles);
	m_Particles->EmitCircle(6);
}

void CEffect::Tick()
{
	m_Particles->FinalTick();
}

void CEffect::Render()
{
	m_Particles->Render();
}

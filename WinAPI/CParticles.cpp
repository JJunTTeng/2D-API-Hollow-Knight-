#include "pch.h"
#include "CParticles.h"
#include "CEngine.h"

#include <random>
#include "CTimeMgr.h"
#include "CCamera.h"


CParticles::CParticles()
	:CComponent(COMPONENT_TYPE::PARTICLE)
{
}

CParticles::~CParticles()
{
	Delete_Vector(particles);
}

void CParticles::EmitCircle(int count)
{
	for (int i = 0; i < count; i++)
	{
		Particle* p = new Particle; 

		float angle = RandomRange(0, 360);
		float speed = RandomRange(50, 150);

		p->vel.x = cos(angle) * speed;
		p->vel.y = sin(angle) * speed;

		p->life = 1.0f;
		p->pos = GetOwner()->GetPos();

		particles.push_back(p);
	}

}

void CParticles::FinalTick()
{
	for (Particle* p : particles)
	{
		p->pos += p->vel * DT;
		p->vel *= 0.9f;
		p->life -= DT;
	}

	bool allDead = false;

	for (Particle* p : particles)
	{
		if (p->life <= 0.0f)
			GetOwner()->IsDead();

		if (allDead)
			delete(p);
	}
}

void CParticles::Render()
{
	for (Particle* p : particles)
	{
		HDC dc = CEngine::GetInst()->GetSecondDC();
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(p->pos);
		Vec2 vScale = Vec2(10.0f, 10.0f);

		Ellipse(dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2
			, vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f);
	}
}



//랜덤값 추출 함수
float CParticles::RandomRange(float min, float max)
{
	static std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> dist(min, max);

	return dist(rng);
}


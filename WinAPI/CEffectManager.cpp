#include "pch.h"
#include "CEffectManager.h"

#include "CEffect.h"
#include <random>

#include "CLevelMgr.h"
#include "CLevel.h"

CEffectManager::CEffectManager()
{

}

CEffectManager::~CEffectManager()
{

}

void CEffectManager::SpawnTileHit(Vec2 _pos, float dir)
{
	CLevel* mLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	//검은색 파편
	for (int i = 0; i < 6; i++)
	{
		CEffect* mEfffect = new CEffect;

		mEfffect->SetPos(_pos);
		mEfffect->SetShape(ParticleShape::Rect);
		mEfffect->SetColor(RGB(20, 20, 20));
		mEfffect->SetLifeTime(RandomRange(1.f, 2.28f));
		mEfffect->SetSize(RandomRange(15.f, 30.f), 5.f);

		Vec2 vel;
		vel.x = RandomRange(-120.f, 120.f) + dir * 80.f;
		vel.y = RandomRange(-220.f, -80.f);

		mEfffect->SetVelocity(vel);
		mEfffect->SetAccel(Vec2(0.f, 500.f));
		mEfffect->SetAngularVelocity(RandomRange(-720.f, 720.f));

		
		mLevel->AddObject(mEfffect, LAYER_TYPE::EFFECT);
	}

	// 흰 파편
	for (int i = 0; i < 3; ++i)
	{
		CEffect* mEfffect = new CEffect;

		mEfffect->SetPos(_pos);
		mEfffect->SetShape(ParticleShape::Rect);
		mEfffect->SetColor(RGB(255, 255, 255));
		mEfffect->SetLifeTime(RandomRange(0.08f, 0.18f));
		mEfffect->SetSize(RandomRange(10.f, 20.f), 5.f);

		Vec2 vel;
		vel.x = RandomRange(-90.f, 90.f) + dir * 60.f;
		vel.y = RandomRange(-180.f, -60.f);

		mEfffect->SetVelocity(vel);
		mEfffect->SetAccel(Vec2(0.f, 400.f));
		mEfffect->SetAngularVelocity(RandomRange(-1000.f, 1000.f));

		mLevel->AddObject(mEfffect, LAYER_TYPE::EFFECT);
	}

	// 흰 슬래시
	{
		CEffect* slash = new CEffect;

		slash->SetPos(_pos + Vec2((float)(dir * 8), 0.f));
		slash->SetShape(ParticleShape::Slash);
		slash->SetColor(RGB(255, 255, 255));
		slash->SetLifeTime(0.06f);
		slash->SetSize(80.f, 20.f);
		slash->SetVelocity(Vec2((float)(dir * 30), 0.f));
		slash->SetAccel(Vec2(0.f, 0.f));

		mLevel->AddObject(slash, LAYER_TYPE::EFFECT);
	}

}

float CEffectManager::RandomRange(float min, float max)
{
	float t = (float)rand() / (float)RAND_MAX;
	return min + (max - min) * t;
}


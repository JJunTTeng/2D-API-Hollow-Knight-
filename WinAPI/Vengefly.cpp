#include "pch.h"
#include "Vengefly.h"

#include "CAssetMgr.h"
#include "CFlipbook.h"
#include "CFlipbookPlayer.h"
#include "CTexture.h"

#include "CRigidBody.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CTimeMgr.h"

Vengefly::Vengefly()
	:m_Chase(false)
{
	SetDir(Dir::LEFT);
	LoadFlipbook();
	SetName(L"Vengefly");
	SetScale(Vec2(100, 100));
	SetSpeed(200.0f);
	m_Flipbook->Play((int)Vengefly_STATE::IDLE, 10, true);

	CCollider* mCollider = GetCollider();
	mCollider->SetScale(Vec2(20, 20));
	SetCollider(mCollider);

	tMonInfo m_Info = GetMonInfo();
	m_Info.MaxHP = 3;
	m_Info.CurHP = 3;
	m_Info.damageCooldown = 0.0f;

	SetMonsInfo(m_Info);

}

Vengefly::~Vengefly()
{
}

void Vengefly::Begin()
{
	CMonster::Begin();
}

void Vengefly::Tick()
{
	if (GetCollider() == nullptr || GetCollider()->GetDead() == true)
		return;

	if (GetChasePlayer() == nullptr)
		return;

	SetprevDir(GetDir());
	CMonster::Tick();

	if (fabs(GetChasePlayer()->GetPos().x + GetChasePlayer()->GetPos().y - (GetPos().x + GetPos().y)) <= 100)
		m_Chase = true;

	if (m_Chase == true)
	{
		
		if (GetprevDir() == GetDir() && m_Flipbook->IsFinish())
		{
			if (GetDir() == Dir::LEFT)
			{
				m_Flipbook->Play((int)Vengefly_STATE::CHASE, 10.0f, true);
			}

			if (GetDir() == Dir::RIGHT)
			{
				m_Flipbook->Play((int)Vengefly_STATE::R_CHASE, 10.0f, true);

			}
		}


		//else
		//{
		//	if (GetDir() == Dir::LEFT && m_Flipbook->IsFinish())
		//	{
		//		m_Flipbook->Play((int)Vengefly_STATE::TURN, 10.0f, false);
		//	}

		//	if (GetDir() == Dir::RIGHT)
		//	{
		//		m_Flipbook->Play((int)Vengefly_STATE::R_TURN, 10.0f, false);

		//	}
		//}

		Chase();

	}



	if (m_Flipbook->GetFlipNum() == (int)Vengefly_STATE::R_CHASE)
	{

	}
}

void Vengefly::Render()
{
	//if (m_SponTime <= 5.0f)
	//	return;

	if (m_IsKnockback == false)
		m_Flipbook->Render();

	//CMonster().Render();
	CMonster::Render();
}

void Vengefly::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	CMonster::BeginOverlap(_Collider, _OtherObject, _OtherCollider);
}

void Vengefly::OnHit()
{
	tMonInfo m_Info = GetMonInfo();

	if (m_Info.CurHP <= 0)
	{
		Death();
	}


	SetMonsInfo(m_Info);
}

void Vengefly::Chase()
{	

	Vec2 Dir = GetChasePlayer()->GetPos() - GetPos();
	if (Dir.x > 0.0f)
		SetDir(Dir::RIGHT);

	else
		SetDir(Dir::LEFT);

	Dir.Normalize();


	//if (m_Flipbook->GetFlipNum() == (int)Vengefly_STATE::TURN || (m_Flipbook->GetFlipNum() == (int)Vengefly_STATE::R_TURN))
	//	return;

	SetPlusPos(Dir * GetSpeed() * DT);
}

void Vengefly::Death()
{
	if (GetDir() == Dir::LEFT)
		m_Flipbook->Play((int)Vengefly_STATE::DEATH,15,false);

	else if (GetDir() == Dir::RIGHT)
		m_Flipbook->Play((int)Vengefly_STATE::R_DEATH, 15, false);

	CCollider* mcollider = GetCollider();
	mcollider->IsDead(true);
	SetCollider(mcollider);
}

void Vengefly::LoadFlipbook()
{
	m_Flipbook = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Vengefly", L"Texture\\Enime\\Vengefly\\Vengefly.png");
	//CAssetMgr::GetInst()->CreateFlipbook(L"Vengefly_IDLE", mTexture, Vec2(3, 21), Vec2(117, 137), 3, 5);
	//CAssetMgr::GetInst()->CreateFlipbook(L"Vengefly_Turn", mTexture, Vec2(3, 181), Vec2(117, 151), 3, 2);
	//CAssetMgr::GetInst()->CreateFlipbook(L"Vengefly_Start", mTexture, Vec2(3, 354), Vec2(146, 154), 3, 4);
	//CAssetMgr::GetInst()->CreateFlipbook(L"Vengefly_Chase", mTexture, Vec2(3, 530), Vec2(143, 136), 3, 4);
	//CAssetMgr::GetInst()->CreateFlipbook(L"Vengefly_Death", mTexture, Vec2(3, 688), Vec2(140, 128), 3, 3);

	//R
	//mTexture = CAssetMgr::GetInst()->LoadTexture(L"R_Vengefly", L"Texture\\Enime\\Vengefly\\R_Vengefly.png");
	//CAssetMgr::GetInst()->CreateFlipbook(L"R_Vengefly_IDLE", mTexture, Vec2(3, 21), Vec2(117, 137), 3, 5 , true , true);
	//CAssetMgr::GetInst()->CreateFlipbook(L"R_Vengefly_Turn", mTexture, Vec2(3, 181), Vec2(117, 151), 3, 2, true , true);
	//CAssetMgr::GetInst()->CreateFlipbook(L"R_Vengefly_Start", mTexture, Vec2(3, 354), Vec2(146, 154), 3, 4, true , true);
	//CAssetMgr::GetInst()->CreateFlipbook(L"R_Vengefly_Chase", mTexture, Vec2(3, 530), Vec2(143, 136), 3, 4, true , true);
	//CAssetMgr::GetInst()->CreateFlipbook(L"R_Vengefly_Death", mTexture, Vec2(3, 688), Vec2(140, 128), 3, 3, true , true);


	m_Flipbook->AddFlipbook((int)Vengefly_STATE::IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"Vengefly_IDLE", L"Flipbook\\Vengefly_IDLE.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::TURN, CAssetMgr::GetInst()->LoadFlipbook(L"Vengefly_Turn", L"Flipbook\\Vengefly_Turn.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::START, CAssetMgr::GetInst()->LoadFlipbook(L"Vengefly_Start", L"Flipbook\\Vengefly_Start.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::CHASE, CAssetMgr::GetInst()->LoadFlipbook(L"Vengefly_Chase", L"Flipbook\\Vengefly_Chase.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"Vengefly_Death", L"Flipbook\\Vengefly_Death.flip"));
	//R
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::R_IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"R_Vengefly_IDLE", L"Flipbook\\R_Vengefly_IDLE.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::R_TURN, CAssetMgr::GetInst()->LoadFlipbook(L"R_Vengefly_Turn", L"Flipbook\\R_Vengefly_Turn.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::R_START, CAssetMgr::GetInst()->LoadFlipbook(L"R_Vengefly_Start", L"Flipbook\\R_Vengefly_Start.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::R_CHASE, CAssetMgr::GetInst()->LoadFlipbook(L"R_Vengefly_Chase", L"Flipbook\\R_Vengefly_Chase.flip"));
	m_Flipbook->AddFlipbook((int)Vengefly_STATE::R_DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"R_Vengefly_Death", L"Flipbook\\R_Vengefly_Death.flip"));
}
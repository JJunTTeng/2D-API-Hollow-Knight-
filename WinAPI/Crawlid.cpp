#include "pch.h"
#include "Crawlid.h"
#include "CFlipbook.h"
#include "CFSM.h"
#include "CAssetMgr.h"
#include "CFlipbookPlayer.h"
#include "CCollider.h"
#include "CCollisionMgr.h"
#include "CRigidBody.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CObj.h"

#include "CKeyMgr.h"
#include "Vengefly.h"

Crawlid::Crawlid()
{
	SetDir(Dir::LEFT);
	LoadFlipbook();
	SetName(L"Crawlid");
	SetScale(Vec2(100,100));
	m_Flipbook->Play((int)Crawlid_STATE::WALK, 10, true);

	CCollider* mCollider = GetCollider();
	mCollider->SetScale(Vec2(97, 80));
	SetCollider(mCollider);

	tMonInfo m_Info = GetMonInfo();
	m_Info.MaxHP = 3;
	m_Info.CurHP = 3;
	m_Info.damageCooldown = 0.0f;

	SetMonsInfo(m_Info);


	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	m_RigidBody->SetInitialSpeed(100.f);
	m_RigidBody->SetMaxSpeed(500.f);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(0.0f);
	m_RigidBody->SetGravityAccel(Vec2(0, 5));

}

Crawlid::~Crawlid()
{
}



void Crawlid::Begin()
{
	m_STATE = Crawlid_STATE::WALK;

	SetPos(GetInitPos());
}

void Crawlid::Tick()
{

	SetprevDir(GetDir());
	CMonster::Tick();

	if (m_STATE == Crawlid_STATE::DEATH || m_STATE == Crawlid_STATE::R_DEATH)
	{
		if (m_Flipbook->IsFinish() == true)
		{
			if (m_STATE == Crawlid_STATE::DEATH)
			{
				SetPos(GetPos().x, GetPos().y + 20);
				m_STATE = Crawlid_STATE::DEATHANI;
				m_Flipbook->Play((int)m_STATE, 0.1, true);

			}

			else if (m_STATE == Crawlid_STATE::R_DEATH)
			{
				SetPos(GetPos().x, GetPos().y + 20);
				m_STATE = Crawlid_STATE::R_DEATHANI;
				m_Flipbook->Play((int)m_STATE, 0.1, true);
			}

		}
	}

	if (m_STATE == Crawlid_STATE::R_DEATHANI || m_STATE == Crawlid_STATE::DEATHANI)
	{
		return;
	}
		

	tMonInfo m_Info = GetMonInfo();

	if (m_Info.damageCooldown > 0.0f)
	{
		m_Info.damageCooldown -= DT;
		SetMonsInfo(m_Info);
	}

	m_SponTime += DT;

	if (m_SponTime <= 1.0f)
		return;




	if (GetComponent<CRigidBody>())
	{
		if (GetDir() == Dir::LEFT)
		{
			if (GetPos().x >= GetInitPos().x - 200.0f)
				SetPos(GetPos() + Vec2(-100.0f, 0.0f) * DT);

			else
				SetDir(Dir::RIGHT);

		}

		else
		{
			if (GetDir() == Dir::RIGHT)
			{
				if (GetPos().x  <= GetInitPos().x + 200.0f)
					SetPos(GetPos() + Vec2(100.0f, 0.0f) * DT);

				else
					SetDir(Dir::LEFT);

			}
		}
	}


	if (GetprevDir() != GetDir() && GetprevDir() == Dir::LEFT)
	{
		m_STATE = Crawlid_STATE::TURN;
		m_Flipbook->Play((int)m_STATE, 5, false);

	}

	if (GetprevDir() != GetDir() && GetprevDir() == Dir::RIGHT)
	{
		m_STATE = Crawlid_STATE::R_TURN;
		m_Flipbook->Play((int)m_STATE, 5, false);
	}

	if (m_Flipbook->IsFinish() && m_STATE == Crawlid_STATE::TURN)
	{
		m_STATE = Crawlid_STATE::R_WALK;
		m_Flipbook->Play((int)m_STATE, 10, true);

	}

	if (m_Flipbook->IsFinish() && m_STATE == Crawlid_STATE::R_TURN)
	{
		m_STATE = Crawlid_STATE::WALK;
		m_Flipbook->Play((int)m_STATE, 10, true);

	}



}

void Crawlid::Render()
{
	if (m_SponTime <= 5.0f)
		return;

	if (m_IsKnockback == false)
		m_Flipbook->Render();

	//CMonster().Render();
	CMonster::Render();

}

void Crawlid::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	CMonster::BeginOverlap(_Collider,_OtherObject,_OtherCollider);

	//if (_OtherObject->GetName() == L"Attack_Eft" )
	//{
	//	m_Info.CurHP -= 1;

	//	if (m_Info.CurHP <= 0 && _OtherObject->GetDir() == Dir::RIGHT)
	//		m_STATE = Crawlid_STATE::DEATH;

	//	else if (m_Info.CurHP <= 0 && _OtherObject->GetDir() == Dir::LEFT)
	//		m_STATE = Crawlid_STATE::R_DEATH;

	//	if (_OtherObject->GetDir() == Dir::RIGHT)
	//		m_STATE = Crawlid_STATE::HIT;

	//	else if (_OtherObject->GetDir() == Dir::LEFT)
	//		m_STATE = Crawlid_STATE::R_HIT;
	//}

}

void Crawlid::OnHit()
{
	tMonInfo m_Info = GetMonInfo();

	if (m_Info.CurHP <= 0)
	{
		Death();
	}


	SetMonsInfo(m_Info);


}

void Crawlid::Death()
{
	if(GetDir() == Dir::LEFT) 
		m_STATE = Crawlid_STATE::DEATH;

	else if (GetDir() == Dir::RIGHT)
		m_STATE = Crawlid_STATE::R_DEATH;

	if (m_STATE == Crawlid_STATE::DEATH)
	{
		m_Flipbook->Play((int)m_STATE, 15, false);
		return;
	}

	else if (m_STATE == Crawlid_STATE::R_DEATH)
	{
		m_Flipbook->Play((int)m_STATE, 15, false);
		return;
	}

	CCollider* mcollider = GetCollider();
	mcollider->IsDead(true);
}

void Crawlid::DeathAni()
{
}



void Crawlid::LoadFlipbook()
{
	m_Flipbook = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	//CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid_Death", L"Texture\\Enime\\Crawlid\\Crawlid.png");
	//mFlipbook->CreateFlipbook(L"Crawlid_Death", mTexture, Vec2(0, 234), Vec2(120, 120), 0, 3);

	//mTexture = CAssetMgr::GetInst()->LoadTexture(L"R_Crawlid_death", L"Texture\\Enime\\Crawlid\\Crawlid.png");
	//mFlipbook->CreateFlipbook(L"R_Crawlid_death", mTexture, Vec2(0, 234), Vec2(120, 120), 0, 3,true);

	//CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid_DeathLand", L"Texture\\Enime\\Crawlid\\Crawlid.png");
	//mFlipbook->CreateFlipbook(L"Crawlid_DeathLand", mTexture, Vec2(0, 376), Vec2(131, 90), 0, 2);

	//mTexture = CAssetMgr::GetInst()->LoadTexture(L"R_Crawlid_deathLand", L"Texture\\Enime\\Crawlid\\Crawlid.png");
	//mFlipbook->CreateFlipbook(L"R_Crawlid_deathLand", mTexture, Vec2(0, 376), Vec2(131, 90), 0, 2,true);


	m_Flipbook->AddFlipbook((int)Crawlid_STATE::WALK, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Walk", L"Flipbook\\Crawlid_Walk.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::TURN, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Turn", L"Flipbook\\Crawlid_turn.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Death", L"Flipbook\\Crawlid_death.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::DEATHANI, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_DeathLand", L"Flipbook\\Crawlid_deathLand.flip"));


	//R
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::R_WALK, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_Walk", L"Flipbook\\R_Crawlid_Walk.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::R_TURN, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_turn", L"Flipbook\\R_Crawlid_turn.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::R_DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_DeathLand", L"Flipbook\\R_Crawlid_death.flip"));
	m_Flipbook->AddFlipbook((int)Crawlid_STATE::R_DEATHANI, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_deathLand", L"Flipbook\\R_Crawlid_deathLand.flip"));

}

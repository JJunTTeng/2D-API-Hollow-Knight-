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




Crawlid::Crawlid()
	:m_HITtime(0.0f)
{
	SetDir(Dir::LEFT);
	LoadFlipbook();
	SetName(L"Crawlid");
	SetScale(Vec2(100,100));
	m_Flipbook->Play(WALK, 10, true);
	CCollider* mCollider = new CCollider;
	mCollider->SetScale(Vec2(97, 80));
	AddComponent(mCollider);
	
	m_Info.MaxHP = 3;
	m_Info.CurHP = 3;

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
	SetMonsInfo(m_Info);
	m_STATE = Crawlid_STATE::WALK;

	SetPos(GetInitPos());
}

void Crawlid::Tick()
{
	m_SponTime += DT;

	if (m_SponTime <= 5.0f)
		return;

	if (m_STATE == HIT)
	{
		m_HITtime += DT;

		if (m_HITtime <= 0.5f)
			return;

		else
		{
			m_HITtime = 0.0f;
			m_STATE = WALK;
		}
	}

	if (m_STATE == R_HIT)
	{
		if (m_HITtime <= 0.5f)
			return;

		else
		{
			m_HITtime = 0.0f;
			m_STATE = R_WALK;
		}
	}

	if (m_STATE == DEATH)
	{
		m_Flipbook->Play(m_STATE, 20, false);
		return;
	}

	else if (m_STATE == R_DEATH)
	{
		m_Flipbook->Play(m_STATE, 20, false);
		return;
	}


	CMonster::Tick();
	SetprevDir(GetDir());

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
		m_STATE = TURN;
		m_Flipbook->Play(m_STATE, 5, false);

	}

	if (GetprevDir() != GetDir() && GetprevDir() == Dir::RIGHT)
	{
		m_STATE = R_TURN;
		m_Flipbook->Play(m_STATE, 5, false);
	}

	if (m_Flipbook->IsFinish() && m_STATE == TURN)
	{
		m_STATE = R_WALK;
		m_Flipbook->Play(m_STATE, 10, true);

	}

	if (m_Flipbook->IsFinish() && m_STATE == R_TURN)
	{
		m_STATE = WALK;
		m_Flipbook->Play(m_STATE, 10, true);

	}



}

void Crawlid::Render()
{
	if (m_SponTime <= 5.0f)
		return;
	m_Flipbook->Render();
	//CMonster().Render();
	CMonster::Render();

}

void Crawlid::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Attack_Eft" )
	{
		m_Info.CurHP -= 1;

		if (m_Info.CurHP <= 0 && _OtherObject->GetDir() == Dir::RIGHT)
			m_STATE = Crawlid_STATE::DEATH;

		else if (m_Info.CurHP <= 0 && _OtherObject->GetDir() == Dir::LEFT)
			m_STATE = Crawlid_STATE::R_DEATH;

		if (_OtherObject->GetDir() == Dir::RIGHT)
			m_STATE = Crawlid_STATE::HIT;

		else if (_OtherObject->GetDir() == Dir::LEFT)
			m_STATE = Crawlid_STATE::R_HIT;
	}

}

void Crawlid::LoadFlipbook()
{
	m_Flipbook = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_Flipbook->AddFlipbook(WALK, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Walk", L"Flipbook\\Crawlid_Walk.flip"));
	m_Flipbook->AddFlipbook(TURN, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Turn", L"Flipbook\\Crawlid_turn.flip"));


	m_Flipbook->AddFlipbook(DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Death", L"Flipbook\\Crawlid_death.flip"));



	//R
	m_Flipbook->AddFlipbook(R_WALK, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_Walk", L"Flipbook\\R_Crawlid_Walk.flip"));
	m_Flipbook->AddFlipbook(R_TURN, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_turn", L"Flipbook\\R_Crawlid_turn.flip"));
	m_Flipbook->AddFlipbook(R_DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_death", L"Flipbook\\R_Crawlid_death.flip"));
}

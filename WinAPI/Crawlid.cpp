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




Crawlid::Crawlid()
{
	LoadFlipbook();
	SetName(L"Crawlid");
	SetScale(Vec2(100,100));
	m_Flipbook->Play(WALK, 10, true);
	CCollider* mCollider = new CCollider;
	mCollider->SetScale(Vec2(97, 80));
	AddComponent(mCollider);

	
	Crawlid_Info.MaxHP = 3;
	
	

	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	m_RigidBody->SetInitialSpeed(100.f);
	m_RigidBody->SetMaxSpeed(500.f);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(0.0f);
	m_RigidBody->SetGravityAccel(Vec2(0, 500));
	
}

Crawlid::~Crawlid()
{
}



void Crawlid::Begin()
{

}

void Crawlid::Tick()
{
	CMonster::Tick();

	if (GetprevDir() != GetDir() && GetprevDir() == dir::LEFT)
	{
		m_STATE = TURN;
		m_Flipbook->Play(m_STATE, 5, false);

	}

	if (GetprevDir() != GetDir() && GetprevDir() == dir::RIGHT)
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
	m_Flipbook->Render();
	//CMonster().Render();
	CMonster::Render();

}

void Crawlid::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
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

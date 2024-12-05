#include "pch.h"
#include "Crawlid.h"
#include "CFlipbook.h"
#include "CFSM.h"
#include "CAssetMgr.h"
#include "CFlipbookPlayer.h"
#include "CCollider.h"
#include "CCollisionMgr.h"
#include "CMonsPattern.h"
#include "CRigidBody.h"

enum Crawlid_STATE
{
	WALK,
	TURN,
	DEATH,

	R_WALK,
	R_TURN,
	R_DEATH
};


Crawlid::Crawlid()
{
	LoadFlipbook();
	SetName(L"Crawlid");
	SetScale(Vec2(100,100));
	m_Flipbook->Play(WALK, 10, true);

	CCollider* mCollider = new CCollider;
	mCollider->SetScale(Vec2(30, 30));
	AddComponent(mCollider);

	CRigidBody* mRigidbody;
	//mRigidbody->SetGround(true);
	mRigidbody = (CRigidBody*)AddComponent(new CRigidBody);
	mRigidbody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	mRigidbody->SetInitialSpeed(100.f);
	mRigidbody->SetMaxSpeed(500.f);
	mRigidbody->SetMass(1.f);
	mRigidbody->SetFriction(700.f);
	mRigidbody->SetJumpVelocity(Vec2(0.f, -500.f));
	mRigidbody->SetGravityAccel(Vec2(0, 500));
	
}

Crawlid::~Crawlid()
{
}



void Crawlid::Begin()
{

}

void Crawlid::Tick()
{
}

void Crawlid::Render()
{
	m_Flipbook->Render();
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
	m_Flipbook->AddFlipbook(R_TURN, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_Walk", L"Flipbook\\R_Crawlid_turn.flip"));
	m_Flipbook->AddFlipbook(R_DEATH, CAssetMgr::GetInst()->LoadFlipbook(L"R_Crawlid_Walk", L"Flipbook\\R_Crawlid_death.flip"));
}

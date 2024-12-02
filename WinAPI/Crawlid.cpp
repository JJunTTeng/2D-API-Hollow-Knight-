#include "pch.h"
#include "Crawlid.h"
#include "CFlipbook.h"
#include "CFSM.h"
#include "CAssetMgr.h"
#include "CFlipbookPlayer.h"

enum Crawlid_STATE
{
	WALK,
	TURN,
	DEATH
};


Crawlid::Crawlid()
{
	LoadFlipbook();
	SetScale(Vec2(100,100));
	m_Flipbook->Play(WALK, 10, true);

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

	m_Flipbook->AddFlipbook(WALK, CAssetMgr::GetInst()->LoadFlipbook(L"Crawlid_Walk", L"Flipbook\\Crawlid_Walk"));

}

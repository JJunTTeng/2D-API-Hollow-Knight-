#include "pch.h"
#include "CAttack_Eft.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFlipbookPlayer.h"
#include "CFlipbook.h"



CAttack_Eft::CAttack_Eft()
{
}

CAttack_Eft::~CAttack_Eft()
{
}


void CAttack_Eft::Begin()
{
	FlipbookLoad();
}

void CAttack_Eft::Tick()
{
}

void CAttack_Eft::Render()
{
}

void CAttack_Eft::FlipbookLoad()
{
	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Attack", L"Texture\\Knight\007.SlashEffect\\Attack_Effact.png");
	mFlipbookPlay = new CFlipbookPlayer;
	CFlipbook* mAddFlipbook = new CFlipbook;

	mAddFlipbook->CreateFlipbook(L"Attack", mTexture, Vec2(0, 0), Vec2(157, 114), 0, 6);
	AddComponent(mFlipbookPlay);
	mFlipbookPlay->AddFlipbook((int)m_Player->GetDir(), mAddFlipbook);


}


#include "pch.h"
#include "CAttack_Eft.h"

#include "CTexture.h";
#include "CFlipbookPlayer.h"
#include "CAssetMgr.h"
#include "CFlipbook.h"

#include "CKeyMgr.h";
#include "CCollider.h"

CAttack_Eft::CAttack_Eft()
{
}

CAttack_Eft::~CAttack_Eft()
{


}

void CAttack_Eft::Begin()
{
	AtakLoadImage();
	AddComponent(m_colision);
}

void CAttack_Eft::Tick()
{
	SetPos(mPlayer->GetPos());

	if (KEY_TAP(Z) && mPlayer->GetDir() == Dir::LEFT)
	{
		m_ImagePlayer->Play(Dir::LEFT, 10, false);
	}
}

void CAttack_Eft::Render()
{
	m_ImagePlayer->Render();
}


void CAttack_Eft::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		_OtherObject.Set
	}
}

void CAttack_Eft::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CAttack_Eft::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}




void CAttack_Eft::AtakLoadImage()
{
	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Attack", L"Texture\\Knight\007.SlashEffect\\Attack_Effact.png");
	mFlipBook->CreateFlipbook(L"P_Attack", mTexture, Vec2(0, 0), Vec2(157, 114), 0, 6);

	m_ImagePlayer = new CFlipbookPlayer;
	AddComponent(m_ImagePlayer);
	m_ImagePlayer->AddFlipbook(Dir::LEFT,CAssetMgr::GetInst()->LoadFlipbook(L"P_LAttack", L"Flipbook\\P_Attack"));
}




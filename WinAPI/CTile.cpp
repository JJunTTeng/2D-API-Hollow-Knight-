#include "pch.h"
#include "CTile.h"

#include "CFlipbook.h"
#include "CFlipbookPlayer.h"

#include "CTexture.h"
#include "CAssetMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CAttack_Eft.h"
#include "CTimeMgr.h"

CTile::CTile()
	:m_Size(1.0f)
	, CurHP(3)
	, m_HitTile(0.0f)
{
}

CTile::~CTile()
{

}

void CTile::Begin()
{
	if (GetName() == L"KingLoad")
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad1", L"Texture\\Map\\Tile1.png");
	}

	if (GetName() == L"KingLoad2")
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad2", L"Texture\\Map\\Tile2.png");
	}

	if (GetName() == L"KingLoad3")
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad3", L"Texture\\Map\\Tile3.png");

		CurHP = 10;
	}

	if (GetName() == L"KingLoad4")
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad4", L"Texture\\Map\\Tile4.png");

		
	}

	m_collider = new CCollider;
	m_collider->SetScale(GetScale());
	m_collider->SetOffset(m_collider->GetRightButtomPos());
	(CCollider*)AddComponent(m_collider);

}

void CTile::Tick()
{
	if (m_HitTile > 0.0f)
		m_HitTile -= DT;
}

void CTile::Render()
{
	CAssetMgr::GetInst()->DrawTexture(m_Texture,GetRenderPos(),GetScale());
}

void CTile::OnHit()
{
	if (m_HitTile > 0.0f)
		return;;

	CurHP -= 1;

	if (CurHP <= 0)
		DeleteObject(this);

	m_HitTile = 0.25f;
}


void CTile::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (GetName() == L"KingLoad" && _OtherObject->GetName() == L"Player")
	{
		CPlayer* mPlayer = dynamic_cast<CPlayer*>(_OtherObject);

		Vec2 _dir = _OtherObject->GetPos() - GetPos();
		mPlayer->PApplyKnockback(_dir, 2000.0f);
	}

	if (GetName() == L"KingLoad2" && _OtherObject->GetName() == L"Player")
	{
		SetDead();
	}
}

void CTile::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{

}

void CTile::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

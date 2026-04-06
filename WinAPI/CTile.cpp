#include "pch.h"
#include "CTile.h"

#include "CFlipbook.h"
#include "CFlipbookPlayer.h"

#include "CTexture.h"
#include "CAssetMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CAttack_Eft.h"

CTile::CTile()
	:m_Size(1.0f)
	, CurHP(3)
{
}

CTile::~CTile()
{

}

void CTile::Begin()
{
	if (GetName() == L"KingLoad")
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoadTile1", L"Texture\\Map\\Tile1.png");
	}

	m_collider = new CCollider;
	m_collider->SetScale(GetScale());
	m_collider->SetOffset(m_collider->GetRightButtomPos());
	(CCollider*)AddComponent(m_collider);

}

void CTile::Tick()
{
}

void CTile::Render()
{
	CAssetMgr::GetInst()->DrawTexture(m_Texture,GetRenderPos(),GetScale());
}

void CTile::OnHit()
{
	CurHP -= 1;

	if (CurHP <= 0)
		DeleteObject(this);

	if(CurHP <= 1)
	{
		m_Texture = CAssetMgr::GetInst()->LoadTexture(L"KingLoadTile2", L"Texture\\Map\\Tile2.png");
	}
}


void CTile::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{

}

void CTile::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		CPlayer* mPlayer = dynamic_cast<CPlayer*>(_OtherObject);

		Vec2 _dir = _OtherObject->GetPos() - GetPos();
		mPlayer->PApplyKnockback(_dir, 2000.0f);
	}
}

void CTile::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

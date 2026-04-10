#include "pch.h"
#include "CAttack_Eft.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFlipbookPlayer.h"
#include "CFlipbook.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMonster.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CTile.h"
#include "CEffectManager.h"

#include "CRigidBody.h"

enum PLAYER_ETTACK_STATE
{
	LEFT_SLASHEFFAT,
	RIGHT_SLASHEFFAT,
	UPSLASHEFFAT,
	DOWNSLASHEFFAT,

	HITEFFT
};


CAttack_Eft::CAttack_Eft()
	:m_AttackTime(0.08f)
{

}

CAttack_Eft::~CAttack_Eft()
{

}


void CAttack_Eft::Begin()
{
	//SetName(L"Attack_Eft");

	//m_CAttack = new CCollider;
	//m_CAttack->SetScale(Vec2(120, 100));
	//m_CAttack->IsActive(false);
	//AddComponent(m_CAttack);

	m_FilpbookAttack = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_HitEffect = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	FlipbookLoad();

}

void CAttack_Eft::Tick()
{
	if (m_AttackTime > 0.0f)
		m_AttackTime -= DT;

	if (m_AttackTime <= 0.0f && m_CAttack != nullptr && m_CAttack->GetDead() == false)
	{
		m_CAttack->IsDead(true);
		return;
	}


	if (KEY_TAP(X))
	{
		m_CAttack = new CCollider;
		m_CAttack->SetScale(Vec2(120, 100));
		AddComponent(m_CAttack);

		m_AttackTime = 0.2f;

		Dir pl_Dir = m_Player->GetDir();
		UD pl_UD = m_Player->GetUD();

		m_CAttack->SetOffset(Vec2(0, 0));

		CRigidBody* pRigidbody = m_Player->GetComponent<CRigidBody>();

		if (pl_UD == UD::UP)
			SetPos(Vec2(m_Player->GetPos().x, m_Player->GetPos().y - 80));

	
		else if (pl_UD == UD::DOWN && pRigidbody->IsGround() == false)
		{
			SetPos(Vec2(m_Player->GetPos().x, m_Player->GetPos().y + 80));
		}

		else if (pl_Dir == Dir::LEFT)
		{
			SetPos(Vec2(m_Player->GetPos().x - 80, m_Player->GetPos().y));
			SetDir(Dir::LEFT);
		}

		else if (pl_Dir == Dir::RIGHT)
		{
			SetPos(Vec2(m_Player->GetPos().x + 80, m_Player->GetPos().y));
			SetDir(Dir::RIGHT);
		}

		if (pl_UD == UD::UP)
		{
			m_FilpbookAttack->Play(UPSLASHEFFAT, 30.0f, false);
			return;
		}

		if (pl_UD == UD::DOWN && pRigidbody->IsGround() == false)
		{
			m_FilpbookAttack->Play(DOWNSLASHEFFAT, 30.0f, false);
			return;
		}

		if (pl_Dir == Dir::LEFT)
		{
			m_FilpbookAttack->Play(LEFT_SLASHEFFAT, 30.0f, false);
			return;
		}

		if (pl_Dir == Dir::RIGHT)
		{
			m_FilpbookAttack->Play(RIGHT_SLASHEFFAT, 30.0f, false);
			return;
		}
	}
}
	
void CAttack_Eft::Render()
{
	m_FilpbookAttack->Render();
	m_HitEffect->Render();
}

void CAttack_Eft::FlipbookLoad()
{

	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Attack_Effact", L"Texture\\Knight\\007.SlashEffect\\Attack_Effact.png");
	mFlipbook->CreateFlipbook(L"Attac_Effact", mTexture, Vec2(0, 0), Vec2(157, 114), 0, 6);

	mTexture = CAssetMgr::GetInst()->LoadTexture(L"R_Attack_Effact", L"Texture\\Knight\\007.SlashEffect\\R_Attack_Effact.png");
	mFlipbook->CreateFlipbook(L"R_Attac_Effact", mTexture, Vec2(0, 0), Vec2(157, 114), 0, 6, true);

	mTexture = CAssetMgr::GetInst()->LoadTexture(L"Up_SlashEffect", L"Texture\\Knight\\015.UpSlashEffect\\UpSlashEffect.png");
	mFlipbook->CreateFlipbook(L"Up_SlashEffect", mTexture, Vec2(0, 0), Vec2(170, 189), 0, 6);

	mTexture = CAssetMgr::GetInst()->LoadTexture(L"Down_SlashEffect", L"Texture\\Knight\\016.DownSlashEffect\\DownSlashEffect.png");
	mFlipbook->CreateFlipbook(L"Down_SlashEffect", mTexture, Vec2(0, 0), Vec2(183, 210), 0, 6);


	m_FilpbookAttack->AddFlipbook(LEFT_SLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Attac_Effact", L"Flipbook\\Attac_Effact"));
	m_FilpbookAttack->AddFlipbook(RIGHT_SLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"R_Attac_Effact", L"Flipbook\\R_Attac_Effact"));
	m_FilpbookAttack->AddFlipbook(UPSLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Up_SlashEffect", L"Flipbook\\Up_SlashEffect"));
	m_FilpbookAttack->AddFlipbook(DOWNSLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Down_SlashEffect", L"Flipbook\\Down_SlashEffect"));



	mTexture = CAssetMgr::GetInst()->LoadTexture(L"HitEffect", L"Texture\\Knight\\106.NA Charged Effect\\HitEffect2.png");
	mFlipbook->CreateFlipbook(L"HitEffect", mTexture, Vec2(0, 0), Vec2(317, 295), 0, 2);

	m_HitEffect->AddFlipbook(HITEFFT, CAssetMgr::GetInst()->LoadFlipbook(L"HitEffect", L"Flipbook\\HitEffect"));
	//AttackEffact

	//m_FilpbookAttack->AddFlipbook(DOWNSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_SLASHALT", L"Flipbook\\R_SLASHALT.flip"));

}

void CAttack_Eft::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	CPlayer* mm_Player = dynamic_cast<CPlayer*>(m_Player);

	if (_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER)
	{
		CMonster* mMonster = dynamic_cast<CMonster*>(_OtherObject);

		mMonster->TakeDamage(1.0f);

		Vec2 mDir = mMonster->GetPos() - m_Player->GetPos();
		if(mMonster->GetMonInfo().CurHP > 0.0f)
		mMonster->ApplyKnockback(mDir, 300.0f);

		
		mDir = m_Player->GetPos() - mMonster->GetPos();
		mm_Player->PApplyKnockback(mDir, 300.0f);

		m_HitEffect->Play(HITEFFT, 10.0f, false);
	}

	if (_OtherObject->GetLayerType() == LAYER_TYPE::ATTCK_TILE)
	{
		CTile* mtile = dynamic_cast<CTile*>(_OtherObject);

		mtile->OnHit();
		Vec2 _dir = mm_Player->GetPos() - _OtherObject->GetPos();
		CEffectManager::GetInst()->SpawnTileHit(GetPos(), 0.f);
		mm_Player->PApplyKnockback(_dir, 300.0f);
	}



}


void CAttack_Eft::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{

}

void CAttack_Eft::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{

}
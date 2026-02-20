#include "pch.h"
#include "CAttack_Eft.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFlipbookPlayer.h"
#include "CFlipbook.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

enum PLAYER_ETTACK_STATE
{
	LEFT_SLASHEFFAT,
	RIGHT_SLASHEFFAT,
	UPSLASHEFFAT,
	DOWNSLASHEFFAT
};


CAttack_Eft::CAttack_Eft()
	:m_AttackActive(false)
	, m_AttackTime(0.0f)
{

}

CAttack_Eft::~CAttack_Eft()
{

}


void CAttack_Eft::Begin()
{
	m_CAttack = new CCollider;
	m_CAttack->SetScale(Vec2(100, 50));
	m_CAttack->IsActive(false);
	AddComponent(m_CAttack);

	m_FilpbookAttack = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	FlipbookLoad();

}

void CAttack_Eft::Tick()
{
	Dir pl_Dir = m_Player->GetDir();
	UD pl_UD = m_Player->GetUD();

	if (pl_UD == UD::UP)
		SetPos(Vec2(m_Player->GetPos().x, m_Player->GetPos().y - 70));

	else if (pl_UD == UD::DOWN)
		SetPos(Vec2(m_Player->GetPos().x, m_Player->GetPos().y + 70));

	else if (pl_Dir == Dir::LEFT)
		SetPos(Vec2(m_Player->GetPos().x - 70, m_Player->GetPos().y));

	else if (pl_Dir == Dir::RIGHT)
		SetPos(Vec2(m_Player->GetPos().x + 70, m_Player->GetPos().y));

	if (m_AttackActive == true && m_AttackTime < 0.5f)
	{
		m_AttackTime += DT;
		return;
	}

	if (KEY_TAP(X))
	{
		if (m_AttackTime >= 1.5f)
		{
			m_AttackTime = 0.0f;
			m_AttackActive = false;
			m_CAttack->IsActive(false);
		}

		m_CAttack->IsActive(true);
		m_AttackActive = true;

		Dir pl_Dir = m_Player->GetDir();
		UD pl_UD = m_Player->GetUD();

		if (pl_UD == UD::UP)
		{
			m_FilpbookAttack->Play(UPSLASHEFFAT, 30.0f, false);
			return;
		}

		else if (pl_UD == UD::DOWN)
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
	mFlipbook->CreateFlipbook(L"Down_SlashEffect", mTexture, Vec2(0, 0), Vec2(170, 189), 0, 6);


	m_FilpbookAttack->AddFlipbook(LEFT_SLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Attac_Effact", L"Flipbook\\Attac_Effact"));
	m_FilpbookAttack->AddFlipbook(RIGHT_SLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"R_Attac_Effact", L"Flipbook\\R_Attac_Effact"));
	m_FilpbookAttack->AddFlipbook(UPSLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Up_SlashEffect", L"Flipbook\\Up_SlashEffect"));
	m_FilpbookAttack->AddFlipbook(DOWNSLASHEFFAT, CAssetMgr::GetInst()->LoadFlipbook(L"Down_SlashEffect", L"Flipbook\\Down_SlashEffect"));

	//AttackEffact

	//m_FilpbookAttack->AddFlipbook(DOWNSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_SLASHALT", L"Flipbook\\R_SLASHALT.flip"));

}


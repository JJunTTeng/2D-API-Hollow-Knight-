#include "pch.h"
#include "CFalseKnight.h"

#include "CTexture.h"
#include "CFlipbook.h"
#include "CFlipbookPlayer.h"
#include "CAssetMgr.h"

#include "CRigidBody.h"


CFalseKnight::CFalseKnight()
{
	tMonInfo m_Info = GetMonInfo();
	m_Info.MaxHP = 3;
	m_Info.CurHP = 3;
	m_Info.damageCooldown = 0.0f;

	SetMonsInfo(m_Info);


	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	m_RigidBody->SetInitialSpeed(100.f);
	m_RigidBody->SetMaxSpeed(500.f);
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(0.0f);
	m_RigidBody->SetGravityAccel(Vec2(0, 5));
}

CFalseKnight::~CFalseKnight()
{
}

void CFalseKnight::Begin()
{
	m_BodyState = FALSEKNIGHT_BODY_STATE::IDLE;
}

void CFalseKnight::Tick()
{
	m_BodyFlipbook->Play((int)m_BodyState, 0.1f, true);
}

void CFalseKnight::Render()
{
	m_BodyFlipbook->Render();
}

void CFalseKnight::OnHit()
{
}

void CFalseKnight::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CFalseKnight::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CFalseKnight::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}


void CFalseKnight::LoadFlipbook()
{
	m_BodyFlipbook = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"FalseKnight", L"Texture\\Boss\\False Knight");
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_IDLE",					mTexture, Vec2(3, 22), Vec2(621, 396), 3, 5);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_TURN",					mTexture, Vec2(3, 440), Vec2(548, 392), 3, 2);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_RUN_ANTICIPATE",			mTexture, Vec2(3, 854), Vec2(574, 380), 3, 2);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_RUN",					mTexture, Vec2(3, 1526), Vec2(623, 492), 3, 5);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP_ANTICIPATE",		mTexture, Vec2(3, 1770), Vec2(310, 383), 3, 3);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP",					mTexture, Vec2(3, 2175), Vec2(604, 340), 3, 4);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_LAND",					mTexture, Vec2(3, 2537), Vec2(610, 383), 3, 3);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_ATTACK_ANTICIPATE",		mTexture, Vec2(3, 2942), Vec2(582, 402), Vec2(3,3),5,6);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_ATTACK",					mTexture, Vec2(3, 3771), Vec2(705, 595),3,3);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_ATTACK_RECOVER",			mTexture, Vec2(3, 4388), Vec2(658, 579), 3, 5);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP_ATTACK_ANTICIPATE",	mTexture, Vec2(3, 4989), Vec2(713, 424), Vec2(3,3),4,5);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP_ATTACK_P1",			mTexture, Vec2(3, 5862), Vec2(842, 624), 2, 2);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP_ATTACK_P2",			mTexture, Vec2(3, 6508), Vec2(489, 592), 2, 2);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_JUMP_ATTACK_P3",			mTexture, Vec2(3, 7122), Vec2(618, 398), 2,2);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_STURN(ROLL)",			mTexture, Vec2(3, 7542), Vec2(765, 518),Vec2(3,3),4,5);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_STURN(ROLL END)",		mTexture, Vec2(3, 8603), Vec2(419, 468),3,4);
	CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_STURN(OPEN)",			mTexture, Vec2(3, 9093), Vec2(396, 457), 3, 4);



	mTexture = CAssetMgr::GetInst()->LoadTexture(L"FalseKnight", L"Texture\\Boss\\R_False Knight");
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_IDLE", mTexture, Vec2(3, 22), Vec2(621, 396), 3, 5,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_TURN", mTexture, Vec2(3, 440), Vec2(548, 392), 3, 2,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_RUN_ANTICIPATE", mTexture, Vec2(3, 854), Vec2(574, 380), 3, 2,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_RUN", mTexture, Vec2(3, 1526), Vec2(623, 492), 3, 5,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP_ANTICIPATE", mTexture, Vec2(3, 1770), Vec2(310, 383), 3, 3,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP", mTexture, Vec2(3, 2175), Vec2(604, 340), 3, 4,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_LAND", mTexture, Vec2(3, 2537), Vec2(610, 383), 3, 3,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_ATTACK_ANTICIPATE", mTexture, Vec2(3, 2942), Vec2(582, 402), Vec2(3, 3), 5, 6,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_ATTACK", mTexture, Vec2(3, 3771), Vec2(705, 595), 3, 3,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_ATTACK_RECOVER", mTexture, Vec2(3, 4388), Vec2(658, 579), 3, 5,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP_ATTACK_ANTICIPATE", mTexture, Vec2(3, 4989), Vec2(713, 424), Vec2(3, 3), 4, 5,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP_ATTACK_P1", mTexture, Vec2(3, 5862), Vec2(842, 624), 2, 2,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP_ATTACK_P2", mTexture, Vec2(3, 6508), Vec2(489, 592), 2, 2,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_JUMP_ATTACK_P3", mTexture, Vec2(3, 7122), Vec2(618, 398), 2, 2,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_STURN(ROLL)", mTexture, Vec2(3, 7542), Vec2(765, 518), Vec2(3, 3), 4, 5,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_STURN(ROLL END)", mTexture, Vec2(3, 8603), Vec2(419, 468), 3, 4,true);
	CAssetMgr::GetInst()->CreateFlipbook(L"R_FalseKnight_STURN(OPEN)", mTexture, Vec2(3, 9093), Vec2(396, 457), 3, 4,true);


	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::IDLE,				CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_IDLE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::TURN,				CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_TURN"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::RUN_ANTICIPATE,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_RUN_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::RUN,				CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_RUN"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::JUMP_ANTICIPATE,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_JUMP_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::JUMP,				CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_JUMP"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::LAND,				CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_LAND"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::ATTACK_ANTICIPATE,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_ATTACK_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::ATTACK,			CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_ATTACK"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::ATTACK_RECOVER,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_ATTACK_RECOVER"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::JUMP_ATTACK_P1,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_JUMP_ATTACK_P1"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::JUMP_ATTACK_P2,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_JUMP_ATTACK_P2"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::JUMP_ATTACK_P3,	CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_JUMP_ATTACK_P3"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::STUN_ROLL,			CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_STURN(ROLL)"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::STUN_ROLLEND,		CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_STURN(ROLL END)"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::STUN_OPEN,			CAssetMgr::GetInst()->FindFlipbook(L"FalseKnight_STURN(OPEN)"));


	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_IDLE,				CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_IDLE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_TURN,				CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_TURN"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_RUN_ANTICIPATE,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_RUN_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_RUN,					CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_RUN"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_JUMP_ANTICIPATE,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_JUMP_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_JUMP,				CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_JUMP"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_LAND,				CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_LAND"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_ATTACK_ANTICIPATE,	CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_ATTACK_ANTICIPATE"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_ATTACK,				CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_ATTACK"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_ATTACK_RECOVER,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_ATTACK_RECOVER"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_JUMP_ATTACK_P1,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_JUMP_ATTACK_P1"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_JUMP_ATTACK_P2,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_JUMP_ATTACK_P2"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_JUMP_ATTACK_P3,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_JUMP_ATTACK_P3"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_STUN_ROLL,			CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_STURN(ROLL)"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_STUN_ROLLEND,		CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_STURN(ROLL END)"));
	m_BodyFlipbook->AddFlipbook((int)FALSEKNIGHT_BODY_STATE::R_STUN_OPEN,			CAssetMgr::GetInst()->FindFlipbook(L"R_FalseKnight_STURN(OPEN)"));


	//CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_STUN",					mTexture, Vec2(3, 7542), Vec2(621, 396), 3, 5);
	//CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_HIT",					mTexture, Vec2(3, 8603), Vec2(621, 396), 3, 5);
	//CAssetMgr::GetInst()->CreateFlipbook(L"FalseKnight_DEATH",					mTexture, Vec2(3, 22), Vec2(621, 396), 3, 5);






}

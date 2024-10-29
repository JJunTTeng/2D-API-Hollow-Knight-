#include "pch.h"
#include "CPlayer.h"

#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CRigidBody.h"

enum PLAYER_ANIM_STATE
{
	IDLE,
	IDLE_LEFT,
	IDLE_RIGHT,

	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,

	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,	
};


CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_RigidBody(nullptr)
	, m_Dir(P_DIR::D_LEFT)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(60.f, 100.f));
	m_HitBox->SetOffset(Vec2(0.f, 15.f));

	AddComponent(m_HitBox);

	// Flipbook 생성 및 등록
	CreatePlayerFlipbook();

	// RigidBody 컴포넌트 추가
	//m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	//m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	//m_RigidBody->SetInitialSpeed(100.f);
	//m_RigidBody->SetMaxSpeed(500.f);
	//m_RigidBody->SetMass(1.f);
	//m_RigidBody->SetFriction(700.f);
	//m_RigidBody->SetJumpVelocity(Vec2(0.f, -500.f));
}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;

	m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true );

	CCamera::GetInst()->SetTarget(this);

	//CCamera::GetInst()->SetTarget(this);
}

void CPlayer::Tick()
{
	if (KEY_TAP(LEFT))
	{
		m_FlipbookPlayer->Play(MOVE_LEFT, 15.f, true);
	}	
	if (KEY_TAP(RIGHT))
	{
		m_FlipbookPlayer->Play(MOVE_RIGHT, 15.f, true);
	}		
	if (KEY_TAP(UP))
	{
		if (m_Dir == P_DIR::D_LEFT)
			m_FlipbookPlayer->Play(LEFT_UP, 5.f, true);

		else
			m_FlipbookPlayer->Play(RIGHT_UP, 5.f, true);
	}	
	if (KEY_TAP(DOWN))
	{
		if (m_Dir == P_DIR::D_LEFT)
			m_FlipbookPlayer->Play(LEFT_DOWN, 5.f, true);

		else
			m_FlipbookPlayer->Play(RIGHT_DOWN, 5.f, true);
	}		



	if (KEY_PRESSED(KEY::A))
	{
		Vec2 mPos = GetPos();
		mPos.x -= 2.0f;

		SetPos(mPos);
		//CCamera::GetInst()->SetPlusCameraPos(Vec2(-2.0f, 0.0f));

	}
	if (KEY_PRESSED(KEY::D))
	{
		Vec2 mPos = GetPos();
		mPos.x += 2.0f;

		SetPos(mPos);

		//CCamera::GetInst()->SetPlusCameraPos(Vec2(2.0f, 0.0f));

	}
	if (KEY_PRESSED(KEY::W))
	{
		Vec2 mPos = GetPos();
		mPos.y -= 2.0f;

		SetPos(mPos);

		//CCamera::GetInst()->SetPlusCameraPos(Vec2(0.0f,-2.0f));

	}
	if (KEY_PRESSED(KEY::S))
	{
		Vec2 mPos = GetPos();
		mPos.y += 2.0f;

		SetPos(mPos);

		//CCamera::GetInst()->SetPlusCameraPos(Vec2(0.0f, 2.0f));

	}


	if (KEY_RELEASED(LEFT))
	{
		m_Dir = P_DIR::D_LEFT;
		m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);
	}
	if (KEY_RELEASED(RIGHT))
	{
		m_Dir = P_DIR::D_RIGHT;
		m_FlipbookPlayer->Play(IDLE_RIGHT, 5.f, true);
	}
	if (KEY_RELEASED(UP))
	{
		if(m_Dir == P_DIR::D_LEFT)
			m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);

		else
			m_FlipbookPlayer->Play(IDLE_RIGHT, 5.f, true);

	}
	if (KEY_RELEASED(DOWN))
	{
		if (m_Dir == P_DIR::D_LEFT)
			m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);

		else
			m_FlipbookPlayer->Play(IDLE_RIGHT, 5.f, true);
	}

	if (KEY_PRESSED(LEFT))
		m_RigidBody->AddForce(Vec2(-1000.f, 0.f), true);
	if (KEY_PRESSED(RIGHT))
		m_RigidBody->AddForce(Vec2(1000.f, 0.f), true);
	/*if (KEY_PRESSED(UP))
		m_RigidBody->AddForce(Vec2(0.f, -1000.f));
	if (KEY_PRESSED(DOWN))
		m_RigidBody->AddForce(Vec2(0.f, 1000.f));*/

	if (KEY_TAP(SPACE))
	{
		CCamera::GetInst()->PostProcessEffect(HEART, 0.2f);
		m_RigidBody->Jump();
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}

	// 미사일 발사
	if (KEY_PRESSED(SPACE))
	{
		// 시간체크
		m_AccTime += DT;

		if (1.f / m_AttSpeed <= m_AccTime)
		{
			m_AccTime -= 1.f / m_AttSpeed;

			// 미사일 생성			
			CMissile* pMissile = new CGuidedMissile;
			pMissile->SetPos(GetPos() + Vec2(0.f, -GetScale().y / 2.f));
			pMissile->SetScale(20.f, 20.f);
			pMissile->SetVelocity(Vec2(cosf(PI / 2.f), -sinf(PI / 2.f)) * 400.f);
			CreateObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);			
		}
	}

	else if (KEY_RELEASED(SPACE))
	{
		m_AccTime = 1.f / m_AttSpeed;
	}
}

void CPlayer::Render()
{
	m_FlipbookPlayer->Render();
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		//DeleteObject(_OtherObject);
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::CreatePlayerFlipbook()
{
	// AtlasTexture
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayIdle", L"Texture\\Knight\\001.Idle\\idle.png");
	CreateFlipbook(L"PLAY_IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 9.0f, pAtlas->GetHeight()), 9);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayLookUp", L"Texture\\Knight\\014.LookUp\\LookUp.png");
	CreateFlipbook(L"PLAY_LOOKUP", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayDown", L"Texture\\Knight\\013.LookDown\\LookDown.png");
	CreateFlipbook(L"PLAY_LOOKDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayRun", L"Texture\\Knight\\005.Run\\run.png");
	CreateFlipbook(L"PLAY_RUN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 13.0f, pAtlas->GetHeight()), 13);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayIdle", L"Texture\\Knight\\001.Idle\\R_idle.png");
	CreateFlipbook(L"R_PLAY_IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 9.0f, pAtlas->GetHeight()), 9,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayLookUp", L"Texture\\Knight\\014.LookUp\\R_LookUp.png");
	CreateFlipbook(L"R_PLAY_LOOKUP", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayDown", L"Texture\\Knight\\013.LookDown\\R_LookDown.png");
	CreateFlipbook(L"R_PLAY_LOOKDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayRun", L"Texture\\Knight\\005.Run\\R_run.png");
	CreateFlipbook(L"R_PLAY_RUN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 13.0f, pAtlas->GetHeight()), 13,true);





	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	{
		//LEFT
		m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_IDLE", L"Flipbook\\PLAY_IDLE.flip"));
		m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_RUN", L"Flipbook\\PLAY_RUN.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_UP, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_LOOKUP", L"Flipbook\\LookUp.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_LOOKDOWN", L"Flipbook\\LookDown.flip"));
	}

	{
		//RIGHT
		m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_IDLE", L"Flipbook\\PLAY_IDLE.flip"));
		m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_RUN", L"Flipbook\\PLAY_RUN.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_UP, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_LOOKUP", L"Flipbook\\LookUp.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_LOOKDOWN", L"Flipbook\\LookDown.flip"));
	}
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame, bool IsRight)
{
	// Sprite 생성하기

	for (int i = 0; i < MaxFrame; ++i)
	{
		CSprite* pSprite = new CSprite;

		if (IsRight == true)
		{
			pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * (MaxFrame - (i + 1))), _LeftTop.y), _Slice);

		}
		else
		{
			pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * i), _LeftTop.y), _Slice);
		}
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		CAssetMgr::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}


	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);		
		wstring Path = L"Sprite\\";		
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}


	// Flipbook 생성하기
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));		
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	wstring Path = L"Flipbook\\";
	pFlipbook->Save(Path + _FlipbookName);
}


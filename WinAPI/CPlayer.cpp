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
#include "CAttack_Eft.h"

#include "CFSM.h"
#include "MoveState.h"
#include "P_Idle.h"
#include "p_JUMP.h"
#include "P_Run.h"
#include "p_Down.h"

#include "ActionState.h"

CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, m_AttackTime(0.0f)

	, m_CHitBox(nullptr)
	, m_CHead(nullptr)
	, m_CFloor(nullptr)

	, m_FlipbookPlayer(nullptr)
	, m_RigidBody(nullptr)
	, m_AttackActive(false)
{

	SetDir(Dir::RIGHT);
	SetUd(UD::NONE);

	// Collider 컴포넌트 추가
	//몸전체 히트박스
	m_CHitBox = new CCollider;
	m_CHitBox->SetName(L"HitBox_01");
	m_CHitBox->SetScale(Vec2(61.f, 130.f));

	AddComponent(m_CHitBox);

	//머리 히트 박스
	m_CHead = new CCollider;
	m_CHead->SetName(L"HeadBox");
	m_CHead->SetScale(Vec2(61.f, 5.f));
	m_CHead->SetOffset(Vec2(0.f, -62.5f));

	AddComponent(m_CHead);

	//다리 히트박스
	m_CFloor = new CCollider;
	m_CFloor->SetName(L"FloorBox");
	m_CFloor->SetScale(Vec2(50.f, 5.f));
	m_CFloor->SetOffset(Vec2(0.f, 62.5f));
	AddComponent(m_CFloor);

	//왼쪽 히트박스
	m_CLeft = new CCollider;
	m_CLeft->SetName(L"LeftBox");
	m_CLeft->SetScale(Vec2(5.f, 120.f));
	m_CLeft->SetOffset(Vec2(-30.5f, 0.0f));
	AddComponent(m_CLeft);

	//오른쪽 히트박스
	m_CRight = new CCollider;
	m_CRight->SetName(L"RightBox");
	m_CRight->SetScale(Vec2(5.f, 120.f));
	m_CRight->SetOffset(Vec2(30.5f, 0.0f));
	AddComponent(m_CRight);

	//공격 박스
	m_CAttackEft = new CCollider;
	m_CAttackEft->SetName(L"Attack_Effact");
	m_CAttackEft->IsActive(false);
	AddComponent(m_CAttackEft);




	// Collider 컴포넌트 추가
	//m_CAttack = new CCollider;
	//m_CAttack->SetName(L"HitBox_01");
	//m_CAttack->SetScale(Vec2(60.f, 100.f));
	//m_CAttack->SetOffset(Vec2(0.f, 15.f));

	//AddComponent(m_CAttack);



	// Flipbook 생성 및 등록
	CreatePlayerFlipbook();
	Attack_Effact();
	 //RigidBody 컴포넌트 추가
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	m_RigidBody->SetInitialSpeed(400.f);
	m_RigidBody->SetMaxSpeed(400.f);
	m_RigidBody->SetFriction(0.0f);
	m_RigidBody->SetMass(1.f);

	// FSM등록
	m_FSM = (CFSM*)AddComponent(new CFSM);
	m_FSM->AddState(L"IDLE", new P_Idle);
	m_FSM->AddState(L"RUN", new p_Run);
	m_FSM->AddState(L"JUMP", new p_JUMP);
	m_FSM->AddState(L"AIRDOWN", new p_Down);

	m_FSM->AddState(L"MOVE_STATE", new MoveState);

	m_FSM->AddState(L"ATTACK", new p_Run);

	m_FSM->AddState(L"ACTION_STATE", new ActionState);

	m_FSM->ChangeState(L"MOVE_STATE");
}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{
	m_AccTime = 1.f / m_AttSpeed;

	m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true );



	CCamera::GetInst()->SetOffset(Vec2(0, -100));
	CCamera::GetInst()->SetTarget(this);


}

void CPlayer::Tick()
{
	Dir m_prevDir = GetDir();
	SetPrevPos(GetPos());

	if (m_AttackTime >= 0.7f && m_AttackActive == true)
	{
		m_FlipbookPlayer->Play(m_prevAni, 50.f, true);
		m_AttackActive = false;
		m_AttackTime = 0.0f;
	}
	else
	{
		m_AttackTime += DT; 
	}
	
	

	if(CKeyMgr::GetInst()->GetLeftOrRight() == LeftOrRight::LR_NONE)
	{
		if (KEY_PRESSED(KEY::LEFT))
		{
			SetDir(Dir::LEFT);
			SetPos(GetPos() - Vec2(m_Speed * DT, 0.f));
		}

		if (KEY_PRESSED(KEY::RIGHT))
		{
			SetDir(Dir::RIGHT);
			SetPos(GetPos() + Vec2(m_Speed * DT, 0.f));

		}
	}

	else if (CKeyMgr::GetInst()->GetLeftOrRight() == LeftOrRight::LR_LEFT)
	{
		SetDir(Dir::LEFT);
		SetPos(GetPos() - Vec2(m_Speed * DT, 0.f));
	}
	else if (CKeyMgr::GetInst()->GetLeftOrRight() == LeftOrRight::LR_RIGHT)
	{
		SetDir(Dir::RIGHT);
		SetPos(GetPos() + Vec2(m_Speed * DT, 0.f));
	}

	if (m_prevDir != GetDir())
	{
		m_FSM->ChangeState(L"IDLE");
	}


	if (KEY_PRESSED(KEY::UP))
	{
		SetUd(UD::UP);
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		SetUd(UD::DOWN);
	}

	if (KEY_RELEASED(KEY::UP))
	{
		SetUd(UD::NONE);
	}

	if (KEY_RELEASED(KEY::DOWN))
	{
		SetUd(UD::NONE);
	}

	if (KEY_PRESSED(KEY::X))
	{
		m_RigidBody->Jump(-600.0f);
	}

	m_CAttackEft->IsActive(false);
	
	//Move();
	//Jump();
	//Attack();

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

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlaySlashAlt", L"Texture\\Knight\\004.SlashAlt\\SlashAlt.png");
	CreateFlipbook(L"PLAY_SLASHALT", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayUpSlash", L"Texture\\Knight\\009.UpSlash\\UpSlash.png");
	CreateFlipbook(L"PLAY_UPSLASH", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayDownSlash", L"Texture\\Knight\\010.DownSlash\\DownSlash.png");
	CreateFlipbook(L"PLAY_DOWNSLASH", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15);
	//R

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayIdle", L"Texture\\Knight\\001.Idle\\R_idle.png");
	CreateFlipbook(L"R_PLAY_IDLE", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 9.0f, pAtlas->GetHeight()), 9,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayLookUp", L"Texture\\Knight\\014.LookUp\\R_LookUp.png");
	CreateFlipbook(L"R_PLAY_LOOKUP", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayDown", L"Texture\\Knight\\013.LookDown\\R_LookDown.png");
	CreateFlipbook(L"R_PLAY_LOOKDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayRun", L"Texture\\Knight\\005.Run\\R_run.png");
	CreateFlipbook(L"R_PLAY_RUN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 13.0f, pAtlas->GetHeight()), 13,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlaySlashAlt", L"Texture\\Knight\\004.SlashAlt\\R_SlashAlt.png");
	CreateFlipbook(L"R_PLAY_SLASHALT", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayUpSlash", L"Texture\\Knight\\009.UpSlash\\R_UpSlash.png");
	CreateFlipbook(L"R_PLAY_UPSLASH", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15,true);

	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayDownSlash", L"Texture\\Knight\\010.DownSlash\\R_DownSlash.png");
	CreateFlipbook(L"R_PLAY_DOWNSLASH", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 15.0f, pAtlas->GetHeight()), 15,true);

	//Slash Effact
	{
		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"SlashEffectAlt", L"Texture\\Knight\\008.SlashEffectAlt\\SlashEffectAlt.png");
		CreateFlipbook(L"SlashEffectAlt", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6);

		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"UpSlashEffect", L"Texture\\Knight\\015.UpSlashEffect\\UpSlashEffect.png");
		CreateFlipbook(L"UpSlashEffect", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6);

		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"DownSlashEffect", L"Texture\\Knight\\016.DownSlashEffect\\DownSlashEffect.png");
		CreateFlipbook(L"DownSlashEffect", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 6.0f, pAtlas->GetHeight()), 6);

	}


	//JUMP
	{
		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayJump", L"Texture\\Knight\\003.Airborne\\Jump.png");
		CreateFlipbook(L"PLAY_JUMP", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 9.0f, pAtlas->GetHeight()), 9);

		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_PlayJump", L"Texture\\Knight\\003.Airborne\\R_Jump.png");
		CreateFlipbook(L"R_PLAY_JUMP", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 9.0f, pAtlas->GetHeight()), 9, true);

		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Play_AirDown", L"Texture\\Knight\\003.Airborne\\Down.png");
		CreateFlipbook(L"PLAY_AIRDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 4.0f, pAtlas->GetHeight()), 4);

		pAtlas = CAssetMgr::GetInst()->LoadTexture(L"R_Play_AirDown", L"Texture\\Knight\\003.Airborne\\R_Down.png");
		CreateFlipbook(L"R_PLAY_AIRDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(pAtlas->GetWidth() / 4.0f, pAtlas->GetHeight()), 4, true);
	}

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	{
		//LEFT
		m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_IDLE", L"Flipbook\\PLAY_IDLE.flip"));
		m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_RUN", L"Flipbook\\PLAY_RUN.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_UP, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_LOOKUP", L"Flipbook\\LookUp.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_LOOKDOWN", L"Flipbook\\LookDown.flip"));

		m_FlipbookPlayer->AddFlipbook(LEFT_SLASH, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_SLASHALT", L"Flipbook\\SLASHALT.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_UPSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_UPSLASH", L"Flipbook\\UPSLASH.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_DOWNSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_DOWNSLASH", L"Flipbook\\DOWNSLASH.flip"));

		m_FlipbookPlayer->AddFlipbook(LEFT_JUMP, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_JUMP", L"Flipbook\\JUMP.flip"));
		m_FlipbookPlayer->AddFlipbook(LEFT_AIRDOWN, CAssetMgr::GetInst()->LoadFlipbook(L"PLAY_AIRDOWN", L"Flipbook\\DOWN.flip"));


	}

	{
		//RIGHT
		m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_IDLE", L"Flipbook\\R_PLAY_IDLE.flip"));
		m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_RUN", L"Flipbook\\R_PLAY_RUN.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_UP, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_LOOKUP", L"Flipbook\\R_LookUp.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_LOOKDOWN", L"Flipbook\\R_LookDown.flip"));

		m_FlipbookPlayer->AddFlipbook(RIGHT_SLASH, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_SLASHALT", L"Flipbook\\R_SLASHALT.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_UPSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_UPSLASH", L"Flipbook\\R_UPSLASH.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_DOWNSLASH, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_DOWNSLASH", L"Flipbook\\R_DOWNSLASH.flip"));

		m_FlipbookPlayer->AddFlipbook(RIGHT_JUMP, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_JUMP", L"Flipbook\\R_JUMP.flip"));
		m_FlipbookPlayer->AddFlipbook(RIGHT_AIRDOWN, CAssetMgr::GetInst()->LoadFlipbook(L"R_PLAY_AIRDOWN", L"Flipbook\\R_DOWN.flip"));

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

void CPlayer::Move()
{
	//이미지
	{	
		if (CKeyMgr::GetInst()->GetNoneKey() == true)
		{
			if(GetDir() == Dir::LEFT)
				m_FlipbookPlayer->Play(IDLE_LEFT, 30.f, true);

			else
				m_FlipbookPlayer->Play(IDLE_RIGHT, 30.f, true);


		}

		if (KEY_TAP(LEFT))
		{
			SetDir(Dir::LEFT);
			m_FlipbookPlayer->Play(MOVE_LEFT, 15.f, true);
		}
		if (KEY_TAP(RIGHT))
		{
			SetDir(Dir::RIGHT);
			m_FlipbookPlayer->Play(MOVE_RIGHT, 15.f, true);
		}

		if (KEY_TAP(UP))
		{
			if (GetDir() == Dir::LEFT)
				m_FlipbookPlayer->Play(LEFT_UP, 3.f, true);
			else
				m_FlipbookPlayer->Play(RIGHT_UP, 3.f, true);

		 
		}

		if (KEY_TAP(DOWN))
		{

			if (GetDir() == Dir::LEFT)
				m_FlipbookPlayer->Play(LEFT_DOWN, 3.f, true);

			else
				m_FlipbookPlayer->Play(RIGHT_DOWN, 3.f, true);
		}
		

		if (KEY_RELEASED(UP))
		{
			if (GetDir() == Dir::LEFT)
				m_FlipbookPlayer->Play(IDLE_LEFT, 30.f, true);

			else
				m_FlipbookPlayer->Play(IDLE_RIGHT, 30.f, true);

		}
		if (KEY_RELEASED(DOWN))
		{
			if (GetDir() == Dir::LEFT)
				m_FlipbookPlayer->Play(IDLE_LEFT, 30.f, true);

			else
				m_FlipbookPlayer->Play(IDLE_RIGHT, 30.f, true);
		}
	}

	//움직이는 속도
	{
		if (KEY_PRESSED(LEFT))
			SetPos(GetPos().x - 500.0f * DT,GetPos().y);
			//m_RigidBody->AddForce(Vec2(-1000.f, 0.f), true);
		if (KEY_PRESSED(RIGHT))
			SetPos(GetPos().x + 500.0f * DT, GetPos().y);

			//m_RigidBody->AddForce(Vec2(1000.f, 0.f), true);
	}
}

void CPlayer::Attack()
{
	
	//이미지
	if (KEY_TAP(X))
	{
		if (m_AttackTime < 1.0f && m_AttackActive == true)
		{
			return;
		}

		m_AttackActive = true;

		m_prevAni = m_FlipbookPlayer->GetFlipNum();

		if (GetDir() == Dir::LEFT && GetUD() == UD::UP)
		{
			m_FlipbookPlayer->Play(LEFT_UPSLASH, 50.f, false);
		}

		else if (GetDir() == Dir::RIGHT && GetUD() == UD::UP)
		{
			m_FlipbookPlayer->Play(RIGHT_UPSLASH, 50.f, false);

		}

		else if (GetDir() == Dir::LEFT && GetUD() == UD::DOWN && m_RigidBody->IsGround() == false)
		{
			m_FlipbookPlayer->Play(LEFT_DOWNSLASH, 50.f, false);

		}

		else if (GetDir() == Dir::RIGHT && GetUD() == UD::DOWN && m_RigidBody->IsGround() == false)
		{
			m_FlipbookPlayer->Play(RIGHT_DOWNSLASH, 50.f, false);
		}

		else if (GetDir() == Dir::LEFT)
		{
			m_FlipbookPlayer->Play(LEFT_SLASH, 50.f, false);
		}

		else if (GetDir() == Dir::RIGHT)
		{
			m_FlipbookPlayer->Play(RIGHT_SLASH, 50.f, false);
		}
	}

}

void CPlayer::Attack_Effact()
{


}

void CPlayer::Jump()
{
	if (KEY_TAP(Z))
	{
		m_RigidBody->Jump(-1000);
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}
}


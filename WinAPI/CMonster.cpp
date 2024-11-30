#include "pch.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFSM.h"

#include "CIdleState.h"
#include "CTraceState.h"

CMonster::CMonster()
{
	//m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Character", L"Texture\\TX_GlowScene_2.png");

	//// Collider 컴포넌트 추가
	//m_Collider = (CCollider*)AddComponent(new CCollider);
	//m_Collider->SetScale(Vec2(100.f, 100.f));

	//// 몬스터 스탯
	//m_Info.MaxHP = 100.f;
	//m_Info.CurHP = 100.f;
	//m_Info.AttRange = 100.f;
	//m_Info.DetectRange = 200.f;
	//m_Info.Speed = 100.f;

	//// FSM 컴포넌트 추가
	//m_FSM = (CFSM*)AddComponent(new CFSM);

	//// FSM 에 상태 추가
	//m_FSM->AddState(L"Idle", new CIdleState);
	//m_FSM->AddState(L"Trace", new CTraceState);
}

CMonster::~CMonster()
{
}

void CMonster::Begin()
{

}

void CMonster::Tick()
{

}

void CMonster::Render()
{

}

void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}
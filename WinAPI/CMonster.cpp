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

#include "MonsterFlipbook.h"

#include "CRigidBody.h"
#include "CCamera.h"

CMonster::CMonster()
	:m_Loop(false),
	m_Dir(dir::LEFT)
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

void CMonster::LoopPlay()
{
	m_Loop = true;
}

void CMonster::Begin()
{
	//MonsterFlipbook::GetInst()->CreateFlipbook();
}

void CMonster::Tick()
{
	m_prevDir = m_Dir;

	if (GetComponent< CRigidBody>())
	{

	}

	else
	{
		if (!m_Loop)
			return;

		if (m_Dir == dir::LEFT)
		{
			if (FrnLpMove <= GetPos())
				m_Dir = dir::RIGHT;

			else
				SetPos(GetPos() + Vec2(-10.0f, 0.0f) * DT);
		}

		else
		{
			if (m_Dir == dir::RIGHT)
			{
				if (FrnLpMove >= GetPos())
					m_Dir = dir::LEFT;

				else
					SetPos(GetPos() + Vec2(10.0f, 0.0f) * DT);
			}
		}

	}

}

void CMonster::Render()
{

	//if (!m_Loop)
	//	return;

	HDC dc = CEngine::GetInst()->GetSecondDC();
	Vec2 mPos = CCamera::GetInst()->GetRenderPos(GetPos());

	MoveToEx(dc, mPos.x, mPos.y, NULL);
	LineTo(dc, CCamera::GetInst()->GetRenderPos(FrnLpMove).x, mPos.y);

	MoveToEx(dc, GetPos().x, GetPos().y, NULL);
	LineTo(dc, CCamera::GetInst()->GetRenderPos(EndLpMove).x, mPos.y);
}

void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
} 
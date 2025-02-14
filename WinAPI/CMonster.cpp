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
	:
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

void CMonster::LoopPlay(bool _Chase)
{
	m_Chase = _Chase;
	m_Loop = true;
	
}

void CMonster::ChaseObject(CObj* _Player)
{
	m_Player = _Player;
}

void CMonster::Chase()
{
	if (GetComponent<CCollider>())
	{
		if (GetPos().x == FrnLpMove.x || GetPos().x == EndLpMove.x)
		{
			m_Chase = false;
			return;
		}

		if (GetPos().x >= m_Player->GetPos().x && FrnLpMove.x <= GetPos().x)
		{
			SetPos(Vec2(GetPos().x - m_Speed.x * DT, GetPos().y));
		}

		else if (GetPos().x <= m_Player->GetPos().x && EndLpMove.x >= GetPos().x)
		{
			SetPos(Vec2(GetPos().x + m_Speed.x * DT, GetPos().y));
		}
	}

}

void CMonster::Begin()
{
	//MonsterFlipbook::GetInst()->CreateFlipbook();
}

void CMonster::Tick()
{
	m_prevDir = m_Dir;

	if (!m_Loop)
		return;

	if (GetComponent< CRigidBody>())
	{
		if (m_Dir == dir::LEFT)
		{
			if (FrnLpMove.x <= GetPos().x)
				SetPos(GetPos() + Vec2(-100.0f, 0.0f) * DT);

			else
				m_Dir = dir::RIGHT;

		}

		else
		{
			if (m_Dir == dir::RIGHT)
			{
				if (EndLpMove.x >= GetPos().x)
					SetPos(GetPos() + Vec2(100.0f, 0.0f) * DT);

				else
					m_Dir = dir::LEFT;

			}
		}
	}

	else
	{




	}


	if (fabs(m_Player->GetPos().x + m_Player->GetPos().y - (GetPos().x + GetPos().y)) <= 100)
		m_Chase = true;


}

void CMonster::Render()
{

	//if (!m_Loop)
	//	return;

	HDC dc = CEngine::GetInst()->GetSecondDC();
	Vec2 mPos = CCamera::GetInst()->GetRenderPos(GetPos());

	MoveToEx(dc, mPos.x, mPos.y, NULL);
	LineTo(dc, CCamera::GetInst()->GetRenderPos(FrnLpMove).x, mPos.y);

	MoveToEx(dc, mPos.x, mPos.y, NULL);
	LineTo(dc, CCamera::GetInst()->GetRenderPos(EndLpMove).x, mPos.y);
}

void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
} 
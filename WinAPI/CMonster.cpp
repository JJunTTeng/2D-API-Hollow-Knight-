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

#include "CPlayer.h"

CMonster::CMonster()
	:m_SponTime(0.0f)
	, m_IsKnockback(false)
	, m_KnockbackTime(0.0f)
	, m_KnockbackDuration(0.2f)
	, m_Velocity(0.0f,0.0f)
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

void CMonster::ApplyKnockback(Vec2 _dir, float power)
{
	m_IsKnockback = true;

	//넉백 지속시간
	m_KnockbackTime = m_KnockbackDuration;

	m_Velocity = _dir.Normalize() * power;
}

void CMonster::TakeDamage(float damage)
{
	if (m_Info.CurHP <= 0)
		return;

	m_Info.CurHP -= damage;

	OnHit();
}

void CMonster::OnHit()
{
}

void CMonster::Begin()
{
	//MonsterFlipbook::GetInst()->CreateFlipbook();
}

void CMonster::Tick()
{
	if (m_IsKnockback)
	{
		m_KnockbackTime -= DT;

		if (m_KnockbackTime <= 0.0f)
		{
			m_IsKnockback = false;
			m_Velocity = Vec2(0.0f, 0.0f);
		}

		SetPlusPos(Vec2(m_Velocity.x,0.0f) * DT);

	}




	if (!m_Loop)
		return;

	else
	{




	}


	//if (fabs(m_Player->GetPos().x + m_Player->GetPos().y - (GetPos().x + GetPos().y)) <= 100)
	//	m_Chase = true;


}

void CMonster::Render()
{

}

void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (CPlayer* mPlayer = dynamic_cast<CPlayer*>(_OtherObject))
	{
		tPlayInfo m_info = mPlayer->GetPlayInfo();
		m_info.CurHP -= 1;

		Vec2 dir = _OtherObject->GetPos() - GetPos();
		dir = dir.Normalize();

		mPlayer->PApplyKnockback(dir, 300.0f);
	}

	

} 
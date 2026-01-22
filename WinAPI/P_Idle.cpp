#include "pch.h"
#include "P_Idle.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CFlipbookPlayer.h"
#include "CRigidBody.h"

#include "CKeyMgr.h"

P_Idle::P_Idle()
	: m_Player(nullptr)
	, m_FlipbookPlayer(nullptr)
{
}

P_Idle::~P_Idle()
{
}

void P_Idle::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();
	if (pPlayer->GetDir() == Dir::LEFT)
	{
		pPlayer->GetFlipbookPlayer()->Play(IDLE_LEFT, 2.f, true);
	}
	else
	{
		pPlayer->GetFlipbookPlayer()->Play(IDLE_RIGHT, 2.f, true);
	}
}

void P_Idle::FinalTick()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();
	if (mRigidBody->IsGround() == false)
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"JUMP");
	}

	else if (KEY_PRESSED(LEFT) || KEY_PRESSED(RIGHT))
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"RUN");
	}
}

void P_Idle::Exit()
{
}

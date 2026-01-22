#include "pch.h"
#include "p_JUMP.h"

#include "CPlayer.h"
#include "CFlipbookPlayer.h"

#include "CKeyMgr.h"

#include "CRigidBody.h"

p_JUMP::p_JUMP()
{
}

p_JUMP::~p_JUMP()
{
}

void p_JUMP::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();
	if (pPlayer->GetDir() == Dir::LEFT)
	{
		pPlayer->GetFlipbookPlayer()->Play(LEFT_JUMP, 15.f, false);
	}
	else
	{
		pPlayer->GetFlipbookPlayer()->Play(RIGHT_JUMP, 15.f, false);
	}
}

void p_JUMP::FinalTick()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();

	if (mRigidBody->IsGround() == true)
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"IDLE");
	}
}

void p_JUMP::Exit()
{
}

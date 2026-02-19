#include "pch.h"
#include "P_Idle.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CFlipbookPlayer.h"
#include "CRigidBody.h"

#include "CKeyMgr.h"

P_Idle::P_Idle()
{
}

P_Idle::~P_Idle() 
{
}

void P_Idle::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	pPlayer->SetPMove(P_Move::IDLE);
}

void P_Idle::FinalTick()
{
	MoveState::FinalTick();
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();
	if (mRigidBody->IsGround() == false)
	{
		pPlayer->GetMoveFSM()->ChangeState(L"JUMP");
	}

	else if (KEY_PRESSED(LEFT) || KEY_PRESSED(RIGHT))
	{
		pPlayer->GetMoveFSM()->ChangeState(L"RUN");
	}
}

void P_Idle::Exit()
{
}

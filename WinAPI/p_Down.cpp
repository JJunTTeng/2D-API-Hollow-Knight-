#include "pch.h"
#include "p_Down.h"

#include "CPlayer.h"
#include "CFlipbookPlayer.h"

#include "CKeyMgr.h"

#include "CRigidBody.h"

p_Down::p_Down()
{
}

p_Down::~p_Down()
{
}

void p_Down::Enter()
{

	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	pPlayer->SetPMove(P_Move::AIRBON);
}

void p_Down::FinalTick()
{
	MoveState::FinalTick();

	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();

	if (mRigidBody->IsGround() == true)
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"IDLE");
	}

}

void p_Down::Exit()
{
}

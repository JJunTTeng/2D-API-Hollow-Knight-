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

	pPlayer->SetPMove(P_Move::JUMP);


}

void p_JUMP::FinalTick()
{

	MoveState::FinalTick();

	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();

	if (mRigidBody->GetVelocity().y > 0)
	{
		//p_Down
		pPlayer->GetComponent<CFSM>()->ChangeState(L"AIRDOWN");
	}
}

void p_JUMP::Exit()
{
}

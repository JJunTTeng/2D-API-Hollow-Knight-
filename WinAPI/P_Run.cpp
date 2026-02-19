#include "pch.h"
#include "p_Run.h"

#include "CPlayer.h"
#include "CFlipbookPlayer.h"

#include "CRigidBody.h"

#include "CKeyMgr.h"

p_Run::p_Run()
{
}

p_Run::~p_Run()
{
}

void p_Run::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	pPlayer->SetPMove(P_Move::MOVE);


}

void p_Run::FinalTick()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	CRigidBody* mRigidBody = pPlayer->GetComponent<CRigidBody>();
	if (mRigidBody->IsGround() == false)
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"JUMP");
	}

	else if (CKeyMgr::GetInst()->GetNoneKey() == true)
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"IDLE");
	}
}

void p_Run::Exit()
{
}

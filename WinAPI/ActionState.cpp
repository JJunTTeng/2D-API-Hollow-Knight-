#include "pch.h"
#include "ActionState.h"

#include "CKeyMgr.h"

#include "CPlayer.h"

ActionState::ActionState()
{
}

ActionState::~ActionState()
{
}

void ActionState::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	pPlayer->SetPAction(P_Action::NONE);
}

void ActionState::FinalTick()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	if (KEY_TAP(X))
	{
		pPlayer->GetComponent<CFSM>()->ChangeState(L"ATTACK");
	}

}

void ActionState::Exit()
{
}

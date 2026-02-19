#include "pch.h"
#include "P_Attack.h"

#include "CPlayer.h"

#include "CFlipbookPlayer.h"

P_Attack::P_Attack()
{
}

P_Attack::~P_Attack()
{
}

void P_Attack::Enter()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	pPlayer->SetPAction(P_Action::ATTACK);
}

void P_Attack::FinalTick()
{
	CPlayer* pPlayer = (CPlayer*)GetOwnerObj();

	if(pPlayer->GetComponent<CFlipbookPlayer>()->IsFinish() == true)
		pPlayer->GetActionFSM()->ChangeState(L"ACTION_STATE");
}

void P_Attack::Exit()
{
}

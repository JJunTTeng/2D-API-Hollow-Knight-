#include "pch.h"
#include "P_Attack.h"

#include "CPlayer.h"

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

	if()
}

void P_Attack::Exit()
{
}

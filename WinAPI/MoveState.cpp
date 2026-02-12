#include "pch.h"
#include "MoveState.h"
#include "P_Idle.h"
#include "p_JUMP.h"
#include "P_Run.h"
#include "p_Down.h"

MoveState::MoveState()
{
}

MoveState::~MoveState()
{
}

void MoveState::Enter()
{
	GetFSM()->GetOwner()->GetComponent<CFSM>()->ChangeState(L"IDLE");
}

void MoveState::FinalTick()
{
}

void MoveState::Exit()
{
}

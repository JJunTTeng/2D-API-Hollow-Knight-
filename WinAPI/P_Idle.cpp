#include "pch.h"
#include "P_Idle.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CFlipbookPlayer.h"

P_Idle::P_Idle()
	: m_Player(nullptr)
{
}

P_Idle::~P_Idle()
{
}

void P_Idle::Enter()
{
	m_Player = (CPlayer*)GetOwnerObj();
	m_FlipbookPlayer = m_Player->GetFlipbookPlayer();

	m_FlipbookPlayer->Play(IDLE_LEFT, 5.f, true);
}

void P_Idle::FinalTick()
{
}

void P_Idle::Exit()
{
}

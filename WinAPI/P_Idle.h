#pragma once
#include "CState.h"
class CPlayer;
class CFlipbookPlayer;
class P_Idle : public CState

{
public:
	P_Idle();
	~P_Idle();

	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit()override;


	CPlayer* m_Player;
	CFlipbookPlayer* m_FlipbookPlayer;
};


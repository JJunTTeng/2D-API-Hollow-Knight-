#pragma once
#include "ActionState.h"

class P_Attack : public ActionState

{
public:
	P_Attack();
	~P_Attack();

	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit()override;

};


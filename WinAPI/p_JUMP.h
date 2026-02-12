#pragma once
#include "MoveState.h"

class CPlayer;
class p_JUMP :
    public MoveState
{
public:
    p_JUMP();
    ~p_JUMP();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;



};
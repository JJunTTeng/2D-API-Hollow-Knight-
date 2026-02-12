#pragma once
#include "MoveState.h"

class CPlayer;
class p_Down:
    public MoveState
{
public:
    p_Down();
    ~p_Down();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;



};
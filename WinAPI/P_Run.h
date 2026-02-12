#pragma once
#include "MoveState.h"

class CPlayer;
class p_Run :
    public MoveState
{
public:
    p_Run();
    ~p_Run();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;



};
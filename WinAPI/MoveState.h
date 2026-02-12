#pragma once
#include "CState.h"

class MoveState :
    public CState
{
public:
    MoveState();
    ~MoveState();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;

protected:

};


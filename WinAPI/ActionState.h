#pragma once
#include "CState.h"

class CPlayer;
class ActionState :
    public CState
{
public:
    ActionState();
    ~ActionState();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;



};

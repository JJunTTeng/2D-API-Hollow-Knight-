#pragma once
#include "CState.h"

class CPlayer;
class p_JUMP :
    public CState
{
public:
    p_JUMP();
    ~p_JUMP();

public:
    virtual void Enter()override;
    virtual void FinalTick()override;
    virtual void Exit() override;



};
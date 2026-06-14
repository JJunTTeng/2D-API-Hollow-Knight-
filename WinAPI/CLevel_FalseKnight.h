#pragma once
#include "CLevel.h"


class CLevel_FalseKnight :
    public CLevel
{
private:
public:
    CLevel_FalseKnight();
    ~CLevel_FalseKnight();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void End() override;



};


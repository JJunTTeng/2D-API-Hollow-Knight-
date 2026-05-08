#pragma once
#include "CLevel.h"


class CLevel_KingPass :
    public CLevel
{
private:
public:
    CLevel_KingPass();
    ~CLevel_KingPass();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void End() override;



};


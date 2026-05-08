#pragma once
#include "CLevel.h"


class CLevel_Dirtmouth :
    public CLevel
{
private:
public:
    CLevel_Dirtmouth();
    ~CLevel_Dirtmouth();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void End() override;



};


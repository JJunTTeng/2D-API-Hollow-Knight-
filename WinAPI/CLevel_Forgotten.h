#pragma once
#include "CLevel.h"


class CLevel_Forgotten :
    public CLevel
{
private:
public:
    CLevel_Forgotten();
    ~CLevel_Forgotten();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void End() override;



};


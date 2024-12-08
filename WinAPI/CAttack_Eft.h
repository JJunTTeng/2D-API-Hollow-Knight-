#pragma once
#include "CObj.h"
class CAttack_Eft : public CObj
{
public:
    virtual void Tick() override;
    virtual void Render() override;

public:

    CAttack_Eft();
    ~CAttack_Eft();
private:


};


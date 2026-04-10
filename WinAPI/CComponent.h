#pragma once
#include "CBase.h"

#include "CObj.h"

class CComponent :
    public CBase
{
private:
    CObj*                   m_Owner;
    const COMPONENT_TYPE    m_Type;
    bool                    m_Death;

public:
    COMPONENT_TYPE GetType() { return m_Type; }
    CObj* GetOwner() { return m_Owner; }

    void IsDead(bool _isDead) { m_Death = _isDead; }
    bool GetDead() { return m_Death;}
public:
    virtual void FinalTick() = 0;

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

    friend class CObj;
};


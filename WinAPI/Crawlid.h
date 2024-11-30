#pragma once
#include "CMonster.h"
class Crawlid :
    public CMonster
{
public:
    Crawlid();
    ~Crawlid();
private:
    tMonInfo    m_Info;

    int         m_Dir;
    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    CTexture* m_Tex;
    CCollider* m_Collider;
    CFSM* m_FSM;

public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;


};


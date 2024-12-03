#pragma once
#include "CMonster.h"

class CFlipbookPlayer;
class Gruzzer :
    public CMonster
{
public:
    Gruzzer();
    ~Gruzzer();
private:
    tMonInfo    m_Info;

    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    bool        m_Dir;

    CFlipbookPlayer* m_Flipbook;

public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    void LoadFlipbook();

};
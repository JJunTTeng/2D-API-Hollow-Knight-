#pragma once
#include "CMonster.h"

class CRigidBody;
class CFlipbookPlayer;

enum Crawlid_STATE
{
    WALK,
    TURN,
    DEATH,

    R_WALK,
    R_TURN,
    R_DEATH
};


class Crawlid :
    public CMonster
{
public:
    Crawlid();
    ~Crawlid();
private:
    tMonInfo    m_Info;

    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;


    CFlipbookPlayer* m_Flipbook;

public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    void LoadFlipbook();
    CRigidBody* m_RigidBody;

    Crawlid_STATE m_STATE;

    tMonInfo Crawlid_Info;
};


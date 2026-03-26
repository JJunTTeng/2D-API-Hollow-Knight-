#pragma once
#include "CMonster.h"

class CRigidBody;
class CFlipbookPlayer;

enum Crawlid_STATE
{
    WALK,
    TURN,
    HIT,
    DEATH,

    R_WALK,
    R_TURN,
    R_HIT,
    R_DEATH,

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

    float       m_HITtime;


    CFlipbookPlayer* m_Flipbook;

public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    void LoadFlipbook();

    //void SetState(Crawlid_STATE m_state) { m_STATE = m_state; }
    //void SetPrevState(Crawlid_STATE m_Prevstate) { m_PrevSTATE = m_Prevstate; }

    CRigidBody* m_RigidBody;

    Crawlid_STATE m_STATE;
    Crawlid_STATE m_PrevSTATE;


};


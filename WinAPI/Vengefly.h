#pragma once
#include "CMonster.h"


enum class Vengefly_STATE
{
    IDLE,
    TURN,
    START,
    CHASE,
    HIT,
    DEATH,
    DEATHANI,

    R_IDLE,
    R_TURN,
    R_START,
    R_CHASE,
    R_HIT,
    R_DEATH,
    R_DEATHANI

};

class CFlipbook;
class CFlipbookPlayer;
class Vengefly :
    public CMonster
{
public:
    Vengefly();
    ~Vengefly();
private:
    tMonInfo    m_Info;

    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    bool        m_Dir;

    CFlipbookPlayer* m_Flipbook;
    CFlipbook* mFlipbook;

    //³Ë¹é
    Vec2            m_KnockbackVelocity;
    bool            m_IsKnockback;
    float           m_KnockbackTime;
    float           m_KnockbackDuration;

    bool            m_Chase;

    Vengefly_STATE  m_State;
public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    void LoadFlipbook();
    void PApplyKnockback(Vec2 power);

	void OnHit() override;

    void Chase();
    void Death();
    


};
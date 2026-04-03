#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFSM;

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;

    float       m_Speed;
    //첫 포지션
    float       m_Dist;

    CTexture*   m_Tex;
    CCollider*  m_Collider;
    CFSM*       m_FSM;

    Vec2        FrnLpMove;
    Vec2        EndLpMove;

    bool        m_Chase;
    bool        m_Loop;

    CObj*       m_Player;

protected:
    Vec2        m_InitPos;

    float       m_SponTime;
    
    Vec2        m_Velocity;
    bool        m_IsKnockback;

    float       m_KnockbackTime;
    float       m_KnockbackDuration;


public:
    Vec2  GetInitPos() { return m_InitPos; }
    Vec2  GetFrnLpMove() { return FrnLpMove; }
    Vec2  GetEndLpMove() { return EndLpMove; }

    void SetInitPos(Vec2 _Pos) {  m_InitPos = _Pos; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }

    void ApplyKnockback(Vec2 _dir, float power);

    //void LoopPlay(bool _Chase);
    //void ChaseObject(CObj* _Player);
    //void Chase();

    virtual void TakeDamage(float damage);
    virtual void OnHit();

    

    const tMonInfo& GetMonInfo() { return m_Info; }
    void SetMonsInfo(tMonInfo _monsInfo) { m_Info = _monsInfo; }
    

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

public:
    CMonster();
    ~CMonster();
};


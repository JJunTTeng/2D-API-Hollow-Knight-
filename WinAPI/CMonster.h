#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFSM;

enum class dir
{
    LEFT,
    RIGHT
};

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;

    dir         m_Dir;
    dir         m_prevDir;

    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    CTexture*   m_Tex;
    CCollider*  m_Collider;
    CFSM*       m_FSM;

    Vec2        FrnLpMove;
    Vec2        EndLpMove;

    bool        m_Chase;
    bool        m_Loop;
public:
    dir GetDir() { return m_Dir; }
    dir GetprevDir() {return m_prevDir;}
    Vec2  GetFrnLpMove() { return FrnLpMove; }
    Vec2  GetEndLpMove() { return EndLpMove; }


    void SetDir(dir _dir) { m_Dir = _dir; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }
    void SetFrnLpMove(Vec2 _pos) { FrnLpMove = _pos; }
    void SetEndLpMove(Vec2 _pos) { EndLpMove = _pos; }

    void LoopPlay();


    const tMonInfo& GetMonInfo() { return m_Info; }
    

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

public:
    CMonster();
    ~CMonster();
};


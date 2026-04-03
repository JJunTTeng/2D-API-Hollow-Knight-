#pragma once
#include "CObj.h"

class CFlipbook;
class CCollider;
class CFlipbookPlayer;
class CAttack_Eft : public CObj
{
public:
    virtual void Begin()override;
    virtual void Tick() override;
    virtual void Render() override;

    void LoadPlayer(CObj* mPlayer) { m_Player = mPlayer; }
    void LoadParticles(CObj* m_particles) { m_Particles = m_particles; }
    void FlipbookLoad();



    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


public:
    CAttack_Eft();
    ~CAttack_Eft();
private:
    CFlipbook* mFlipbook;
    CObj* m_Player;
    CObj* m_Particles;
    CFlipbookPlayer* m_FilpbookAttack;
    CFlipbookPlayer* m_HitEffect;


    CCollider* m_CAttack;
    bool       m_AttackActive;
    float      m_AttackTime;

    //일자모형 파티클
    float      m_Life;
    float      m_Time;

    Vec2       m_dir;
    float      m_Length;
};


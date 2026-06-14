#pragma once
#include "CMonster.h"

class CRigidBody;
class CFlipbookPlayer;

enum class  FALSEKNIGHT_BODY_STATE
{
    IDLE,
    TURN,
    RUN_ANTICIPATE,
    RUN,
    JUMP_ANTICIPATE,
    JUMP,
    LAND,
    ATTACK_ANTICIPATE,
    ATTACK,
    ATTACK_RECOVER,
    JUMP_ATTACK_ANTICIPATE,
    JUMP_ATTACK_P1,
    JUMP_ATTACK_P2,
    JUMP_ATTACK_P3,
    STUN_ROLL,
    STUN_ROLLEND,
    STUN_OPEN,
    HIT,
    DEATH,

    R_IDLE,
    R_TURN,
    R_RUN_ANTICIPATE,
    R_RUN,
    R_JUMP_ANTICIPATE,
    R_JUMP,
    R_LAND,
    R_ATTACK_ANTICIPATE,
    R_ATTACK,
    R_ATTACK_RECOVER,
    R_JUMP_ATTACK_ANTICIPATE,
    R_JUMP_ATTACK_P1,
    R_JUMP_ATTACK_P2,
    R_JUMP_ATTACK_P3,
    R_STUN_ROLL,
    R_STUN_ROLLEND,
    R_STUN_OPEN,
    R_STUN,
    R_HIT,
    R_DEATH,
};

enum class  FALSEKNIGHT_HEAD_STATE
{
    IDLE,
    HIT,
    DEATH,
    NONE
};

enum class  FALSEKNIGHT_MACE_STATE
{
    ROLL,
    EMERGE,
    LEAVE,
    NONE
};



class CFalseKnight :
    public CMonster
{
public:
    CFalseKnight();
    ~CFalseKnight();
private:

    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    CFlipbookPlayer* m_BodyFlipbook;
    CFlipbookPlayer* m_HeadFlipbook;
    CFlipbookPlayer* m_MaceFlipbook;

public:

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;


    virtual void OnHit()override;

    void Death();
    void DeathAni();

    void LoadFlipbook();

    //void SetState(Crawlid_STATE m_state) { m_STATE = m_state; }
    //void SetPrevState(Crawlid_STATE m_Prevstate) { m_PrevSTATE = m_Prevstate; }

    CRigidBody* m_RigidBody;

	FALSEKNIGHT_BODY_STATE m_BodyState;
	FALSEKNIGHT_HEAD_STATE m_HeadState;
	FALSEKNIGHT_MACE_STATE m_MaceState;
};


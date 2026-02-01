#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CRigidBody;
class CFSM;

enum PLAYER_ANIM_STATE
{
    IDLE,
    IDLE_LEFT,
    IDLE_RIGHT,

    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,

    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,

    LEFT_SLASH,
    LEFT_UPSLASH,
    LEFT_DOWNSLASH,

    RIGHT_SLASH,
    RIGHT_UPSLASH,
    RIGHT_DOWNSLASH,

    LEFT_JUMP,
    RIGHT_JUMP,

    LEFT_AIRDOWN,
    RIGHT_AIRDOWN,

    END
};

struct Flip
{
    int Name;
    float Fps;
    bool Loop;
};


class CPlayer :
    public CObj
{
private:
    float               m_AttackTime;
    float               m_Speed;
    float               m_AttSpeed; // 초당 발사 속도
    float               m_AccTime;  // 시간 누적
    bool                m_AttackActive;
    

    CCollider*          m_CHitBox;
    CCollider*          m_CHead;
    CCollider*          m_CFloor;
    CCollider*          m_CLeft;
    CCollider*          m_CRight;

    CCollider*          m_CAttackEft;

    CFlipbookPlayer*    m_FlipbookPlayer;
    CRigidBody*         m_RigidBody;

	CFSM*               m_FSM;        

    UINT                m_prevAni;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


	CFlipbookPlayer* GetFlipbookPlayer() { return m_FlipbookPlayer; }

private:
    void CreatePlayerFlipbook();
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame, bool IsRight = false);

    void Move();
    void Attack();
    void Attack_Effact();
    void Jump();

    

private:



public:
    CPlayer();
    ~CPlayer();    
};


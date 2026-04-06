#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CRigidBody;
class CFSM;


struct tPlayInfo
{
    float MaxHP;
    float CurHP;

    float MaxMP;
    float CurMP;

    float Att;
    float Def;
    float Dex;

    float AttRange;
    float DetectRange;

    float Speed;
    float damageCooldown;
};


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

enum class P_Move
{
    IDLE,
    MOVE,
    JUMP,
    AIRBON,

    NONE
};

enum class P_Action
{
    ATTACK,

    NONE
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
    CFlipbookPlayer*    m_AtkPlayer;

    CRigidBody*         m_RigidBody;

	CFSM*               m_MoveFSM; 
    CFSM*               m_ActionFSM;


    UINT                m_prevAni;

    P_Move              m_prevpMove;
    P_Move              m_pMove;

    P_Action            m_prevpAction;
    P_Action            m_pAction;


    // 넉백
    Vec2                m_Velocity;
    bool                m_IsKnockback;

    float               m_KnockbackTime;
    float               m_KnockbackDuration;

    tPlayInfo           m_PlayInfo;
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


	CFlipbookPlayer* GetFlipbookPlayer() { return m_FlipbookPlayer; }

    void SetPMove(P_Move pMove) { m_pMove = pMove; }
    void SetPAction(P_Action pAction) { m_pAction = pAction; }

	CFSM* GetMoveFSM() { return m_MoveFSM; }
    CFSM* GetActionFSM() { return m_ActionFSM; }

    void PApplyKnockback(Vec2 _dir, float power);

    void SetPlayInfo(tPlayInfo _Playinfo) { m_PlayInfo = _Playinfo; }
    tPlayInfo GetPlayInfo() { return m_PlayInfo; }


private:
    void CreatePlayerFlipbook();
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame, bool IsRight = false);

    void UpdateAnimation(); 

    

public:
    CPlayer();
    ~CPlayer();    
};


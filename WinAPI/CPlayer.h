#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CRigidBody;


enum P_DIR
{
    D_LEFT,
    D_RIGHT,
};

enum P_UD
{
    D_NONE,
    D_UP,
    D_DOWN
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
    float               m_Speed;
    float               m_AttSpeed; // 초당 발사 속도
    float               m_AccTime;  // 시간 누적
    
    CCollider*          m_CHitBox;
    CCollider*          m_CHead;
    CCollider*          m_CFloor;
    CCollider*          m_CLeft;
    CCollider*          m_CRight;

    CCollider*          m_CAttack;


    CFlipbookPlayer*    m_FlipbookPlayer;
    CFlipbookPlayer*    m_FilpbookAttack;
    CRigidBody*         m_RigidBody;

    
    P_DIR               m_Dir;
    P_UD                m_Ud;

public:     
    virtual void Begin() override;
    virtual void Tick() override;    
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    

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


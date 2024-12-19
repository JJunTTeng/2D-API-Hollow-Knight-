#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CRigidBody;

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
    float               m_AttSpeed; // �ʴ� �߻� �ӵ�
    float               m_AccTime;  // �ð� ����
    bool                m_AttackActive;
    

    CCollider*          m_CHitBox;
    CCollider*          m_CHead;
    CCollider*          m_CFloor;
    CCollider*          m_CLeft;
    CCollider*          m_CRight;

    CCollider*          m_CAttackEft;

    CFlipbookPlayer*    m_FlipbookPlayer;
    CRigidBody*         m_RigidBody;

    UINT                m_prevAni;

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


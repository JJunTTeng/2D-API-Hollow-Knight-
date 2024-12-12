#pragma once
#include "CObj.h"

class CCollider;
class CFlipbook;
class CFlipbookPlayer;
class CAttack_Eft : public CObj
{
public:


    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


    void LoadPlayer(CObj* _Player) { mPlayer = _Player; }
    void AtakLoadImage();

public:

    CAttack_Eft();
    ~CAttack_Eft();
private:
    CObj* mPlayer;
    CFlipbookPlayer* m_ImagePlayer;
    CFlipbook* mFlipBook;
    CCollider* m_colision;
};


#pragma once
#include "CObj.h"

enum TileName
{
    KingLoad,
    None
};

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CTile : public CObj
{
public:

    CTile();
    ~CTile();

    virtual void Begin() override;         
    virtual void Tick() override;      
    virtual void Render()override;        

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    void OnHit();

private:

private:
    CCollider* m_collider;
    CFlipbookPlayer* m_Animation;
    CTexture* m_Texture;
    float m_Size;
    float m_HitTile;

    int CurHP;
};


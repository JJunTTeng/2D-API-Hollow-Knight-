#pragma once
#include "CObj.h"

class CCollider;
class CCameraBound : public CObj
{
public:
    CCameraBound();
    ~CCameraBound();


    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


    float LerpTime;

private:
    CCollider* m_Coliider;
};


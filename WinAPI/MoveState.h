#pragma once

class CPlayer;
class CCollider;
class MoveState
{
public:
    virtual void Begin(CObj* obj) =0;
    virtual void Tick() =0;
    virtual void Render() =0;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)=0;
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)=0;
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)=0;

};


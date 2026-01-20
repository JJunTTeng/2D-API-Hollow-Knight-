#pragma once

class CPlayer;
class CCollider;
class ActionState
{
    virtual void Begin() = 0;
    virtual void Tick() = 0;
    virtual void Render() = 0;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) = 0;
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) = 0;
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) = 0;


};


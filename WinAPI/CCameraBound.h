#pragma once
#include "CObj.h"

class CCollider;
class CCameraBound : public CObj
{
public:
    CCameraBound();
    ~CCameraBound();

    enum RoomName
    {
        StopRoom,
        YStopRoom,
        None
    };

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    Vec2 Lerp(Vec2 _Pos1,Vec2 _finalPos2, float _v);

    float LerpTime;
    RoomName m_roomName;
};


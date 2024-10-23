#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2        m_Offset;   // 상대 좌표
    Vec2        m_Scale;    // 크기
    Vec2        m_FinalPos; // 충돌체의 실제 위치

    bool        m_Active;   // 활성화

    int         m_OverlapCount; // 충돌 중인 물체의 숫자


public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() { return m_Scale; }

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    Vec2 GetOffset() { return m_Offset; }

    Vec2 GetFinalPos() { return m_FinalPos; }

public:
    void BeginOverlap(CCollider* _Other);   // 다른 충돌체와 최초 충돌 시
    void Overlap(CCollider* _Other);        // 다른 충돌체와 BeginOverlap 이후에도 계속 겹쳐있을 경우
    void EndOverlap(CCollider* _Other);     // 다른 충돌체와 겹쳐있다가 최초로 떨어지는 순간


public:
    virtual void FinalTick() override;

public:
    CCollider();
    ~CCollider();
};


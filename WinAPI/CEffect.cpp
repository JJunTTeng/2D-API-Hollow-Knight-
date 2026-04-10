#include "pch.h"
#include "CEffect.h"

#include "CParticles.h"
#include "CTimeMgr.h"
#include "CEngine.h"
CEffect::CEffect()
	: mVelocity(0.f, 0.f)
    , mAccel(0.f, 0.f)
    , mLifeTime(0.f)
    , mMaxLifeTime(0.f)
    , mAngle(0.f)
    , mAngularVelocity(0.f)
    , mSize(4.f)
    , mStartSize(4.f)
    , mEndSize(4.f)
    , mFadeOut(false)
    , mShape(ParticleShape::Rect)
    , mColor(RGB(255, 255, 255))
{

}

CEffect::~CEffect()
{
}

void CEffect::Begin()
{
}

void CEffect::Tick()
{
    mLifeTime -= DT;

    if (mLifeTime <= 0.0f)
    {
        SetDead();
        return;
    }

    mVelocity += mAccel * DT;
    SetPos(GetPos() + mVelocity * DT);

    mAngle += mAngularVelocity * DT;

    float ratio = 1.f - (mLifeTime / mMaxLifeTime);
    mSize = mStartSize + (mEndSize - mStartSize) * ratio;
}

void CEffect::Render()
{
    Vec2 pos = GetRenderPos();

    int size = mSize;
    int half = size / 2;

    HDC _dc = CEngine::GetInst()->GetSecondDC();

    HBRUSH brush = CreateSolidBrush(mColor);
    HBRUSH oldBrush = (HBRUSH)SelectObject(_dc, brush);

    HPEN pen = CreatePen(PS_NULL, 0, mColor);
    HPEN oldPen = (HPEN)SelectObject(_dc, pen);

    switch (mShape)
    {
    case ParticleShape::Rect:
    {
        Rectangle(_dc,
            (int)pos.x - half,
            (int)pos.y - half,
            (int)pos.x + half,
            (int)pos.y + half);
    }
    break;

    case ParticleShape::Circle:
    {
        Ellipse(_dc,
            (int)pos.x - half,
            (int)pos.y - half,
            (int)pos.x + half,
            (int)pos.y + half);
    }
    break;

    case ParticleShape::Slash:
    {
        // 간단 버전: 가느다란 직사각형처럼 그림
        Rectangle(_dc,
            (int)pos.x - size,
            (int)pos.y - 1,
            (int)pos.x + size,
            (int)pos.y + 1);
    }
    break;
    }

    SelectObject(_dc, oldBrush);
    DeleteObject(brush);

    SelectObject(_dc, oldPen);
    DeleteObject(pen);

}

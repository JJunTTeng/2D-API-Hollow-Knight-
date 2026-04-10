#pragma once
#include "CObj.h"

enum class ParticleShape
{
    Rect,
    Circle,
    Slash,
};

class CEffect : public CObj
{
public:
	CEffect();
	~CEffect();

    virtual void Begin()override;
    virtual void Tick() override;
    virtual void Render() override;

private:
    Vec2            mVelocity;
    Vec2            mAccel;

    float           mLifeTime;
    float           mMaxLifeTime;

    float           mAngle;
    float           mAngularVelocity;

    float           mSize;
    float           mStartSize;
    float           mEndSize;

    bool            mFadeOut;

    ParticleShape   mShape;
    COLORREF        mColor;

public:
    void SetVelocity(const Vec2& vel) { mVelocity = vel; }
    void SetAccel(const Vec2& acel) { mAccel = acel; }

    void SetLifeTime(float time)
    {
        mLifeTime = time;
        mMaxLifeTime = time;
    }

    void SetAngle(float angle) { mAngle = angle; }
    void SetAngularVelocity(float value) { mAngularVelocity = value; }

    void SetSize(float startSize, float endSize = -1.f)
    {
        mStartSize = startSize;
        mEndSize = (endSize < 0.f) ? startSize : endSize;
        mSize = startSize;
    }

    void SetFadeOut(bool value) { mFadeOut = value; }
    void SetShape(ParticleShape shape) { mShape = shape; }
    void SetColor(COLORREF color) { mColor = color; }

};


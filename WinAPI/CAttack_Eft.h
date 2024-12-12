#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CAttack_Eft : public CObj
{
public:
    virtual void Begin()override;
    virtual void Tick() override;
    virtual void Render() override;

    void LoadPlayer(CObj* mPlayer) { m_Player = mPlayer; }
    void FlipbookLoad();

public:
    CAttack_Eft();
    ~CAttack_Eft();
private:
    CObj* m_Player;
    CFlipbookPlayer* mFlipbookPlay;
};


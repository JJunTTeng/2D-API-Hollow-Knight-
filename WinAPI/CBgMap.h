#pragma once
#include "CObj.h"

class CTexture;
class CBgMap :
    public CObj
{
private:

public:
    virtual void Tick() override;
    virtual void Render() override;

public:



    CBgMap();
    ~CBgMap();

private:
    CTexture* mTexture;
};


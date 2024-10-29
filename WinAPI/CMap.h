#pragma once
#include "CObj.h"

class CTexture;
class CMap :
    public CObj
{
private:

public:
    virtual void Tick() override;
    virtual void Render() override;

public:



    CMap();
    ~CMap();

private:
    CTexture* mTexture;
};


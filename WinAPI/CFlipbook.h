#pragma once
#include "CAsset.h"

class CTexture;
class CSprite;

class CFlipbook :
    public CAsset
{
private:
    vector<CSprite*>    m_Sprites;

public:
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int _blank, int MaxFrame, bool IsRight = false);
    void AddSprite(CSprite* _Sprite) { m_Sprites.push_back(_Sprite); }
    CSprite* GetSprite(int _Idx) { return m_Sprites[_Idx]; }

    int GetMaxSpriteCount() { return m_Sprites.size(); }
    
public:
    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _RelativePath) override;

public:
    CFlipbook();
    ~CFlipbook();
};


#pragma once

#include "CLevel.h"

enum class EditMode
{
     FilbookMode,
     ColliderMode,
     AnimesMode,
     None
};


class CPlayer;
class Colision;
class CTexture;
class CLevel_Editor :
    public CLevel
{
private:
    class CMap* m_MapObj;
    HMENU       m_hMenu;

public:
    CMap* GetMapObject() { return m_MapObj; }
    std::list<Colision*> GetColisions() { return mDrawCol; }

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void End() override;

public:
    void SaveTileMap();
    void LoadTileMap();

    void SaveColider();
    void LoadColider(wchar_t* Path);

    void OpenImage();
    void SaveImage();

    void SavePlibook();
    void LoadPlibook();

    void Anime();
    void AnimeSave();
    void AnimeLoad();

    void AnimeMode();
public:
    CLevel_Editor();
    ~CLevel_Editor();

private:
    std::list<Colision*> mDrawCol;
    CPlayer* mPlayer;
    CTexture* mTexture;
    CTexture* mSubTexture;

    Vec2 ColBeginPos;
    Vec2 ColEndPos;
    Vec2 MouseRenderPos;
    Vec2 EditRenderPos;

    EditMode mEditMode;

};


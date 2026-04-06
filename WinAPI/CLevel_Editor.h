#pragma once

#include "CLevel.h"

enum class EditMode
{
     FilbookMode,
     ColliderMode,
     EnimesMode,
     PatternMode,
     CameraMode,
     TileMode,
     None
};

enum class EnimesName
{
    Crawlid,
    None
};

class CAttack_Eft;
class CMonsPattern;
class CPlayer;
class Colision;
class CTexture;
class CMonster;
class CCameraBound;
class CTile;

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

    void Collider();
    void SaveColider();
    void LoadColider(wchar_t* Path);

    void OpenImage();
    void SaveImage();

    void SavePlibook();
    void LoadPlibook();

    void Enime();
    void EnimeSave();
    void EnimeLoad(wchar_t* Path);

    void ColliderMode();
    void EnimeMode();
    void EnimeRenderer();

    void EnimesPattern();

    void CameraBound(wstring _name);
    void CameraBoundSave();
    void CameraBoundLoad(wchar_t* Path);

    void InsertTile(wstring _name);
    void TileSave();
    void TileLoad(wchar_t* Path);

public:
    CLevel_Editor();
    ~CLevel_Editor();

private:
    std::list<Colision*> mDrawCol;
    std::list<CMonster*> mMonsters;
    std::list<CCameraBound*> mCameraBounds;
    std::list<CTile*> mTiles;



    CPlayer* mPlayer;

    CTexture* mTexture;
    CTexture* mSubTexture;
    CTexture* mMouseTextue;

    Vec2 ColBeginPos;
    Vec2 ColEndPos;
    Vec2 MouseRenderPos;
    Vec2 EditRenderPos;

    EditMode mEditMode;
    EnimesName mEnimeName;

    CMonster* SelectMons;
    CMonsPattern* mMonsPtn;

    CAttack_Eft* m_Play_Effact;

    Vec2 mMonsPtnPos;

    wstring m_TileName;
    wstring m_BoundName;
    float _Size;

};


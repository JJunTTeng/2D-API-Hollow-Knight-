#pragma once

#include "CLevel.h"

class CPlayer;
class Colision;
class CLevel_Editor :
    public CLevel
{
private:
    class CMap* m_MapObj;
    HMENU       m_hMenu;

public:
    CMap* GetMapObject() { return m_MapObj; }

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void End() override;

public:
    void SaveTileMap();
    void LoadTileMap();

public:
    CLevel_Editor();
    ~CLevel_Editor();

private:
    std::vector<Colision*> mDrawCol;
    CPlayer* mPlayer;

    Vec2 ColBeginPos;
    Vec2 ColEndPos;

};


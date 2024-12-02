#include "pch.h"
#include "CFlipbook.h"

#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CSprite.h"

CFlipbook::CFlipbook()
    : CAsset(ASSET_TYPE::FLIPBOOK)
{
}

CFlipbook::~CFlipbook()
{
}

void CFlipbook::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int _blank, int MaxFrame, bool IsRight)
{
    // Sprite �����ϱ�

    for (int i = 0; i < MaxFrame; ++i)
    {
        CSprite* pSprite = new CSprite;

        
        if (IsRight == true)
        {
            pSprite->Create(_Atlas, Vec2(_LeftTop.x - (_blank *(i+1)) + (_Slice.x * (MaxFrame - (i + 1))), _LeftTop.y), _Slice);

        }
        else
        {
            pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_blank * (i + 1)) +  (_Slice.x * i), _LeftTop.y), _Slice);
        }
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        CAssetMgr::GetInst()->AddSprite(Key, pSprite);
        wstring strSavePath = L"Sprite\\";
        strSavePath += pSprite->GetKey();
        pSprite->Save(strSavePath);
    }


    for (int i = 0; i < MaxFrame; ++i)
    {
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        wstring Path = L"Sprite\\";
        Path += Key;
        CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
    }


    CFlipbook* mFlipbook = new CFlipbook;

    for (int i = 0; i < MaxFrame; ++i)
    {
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        mFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));
    }


    CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, mFlipbook);
    wstring Path = L"Flipbook\\";
    mFlipbook->Save(Path + _FlipbookName);
}

int CFlipbook::Save(const wstring& _RelativePath)
{
    wstring RelativePath = _RelativePath;
    CheckExt(L".flip", RelativePath);

    // ������ �ڽ��� ��� ����Ǵ����� �˰� ��
    SetRelativePath(RelativePath);

    // ���� ���� ���
    wstring strFilePath = CPathMgr::GetContentPath() + RelativePath;

    // Sprite �� Key, RelativePath �� ����
    FILE* File = nullptr;
    _wfopen_s(&File, strFilePath.c_str(), L"w");

    // KEY, Path ����
    fwprintf_s(File, L"[KEY]\n");
    fwprintf_s(File, L"%s\n", GetKey().c_str());

    fwprintf_s(File, L"[PATH]\n");
    fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

    // Sprite ����
    fwprintf_s(File, L"[SPRITE_COUNT]\n");
    int SpriteCount = (int)m_Sprites.size();
    fwprintf_s(File, L"%d\n", SpriteCount);

    // ������ Sprite ���� ����
    for (int i = 0; i < (int)m_Sprites.size(); ++i)
    {
        fwprintf_s(File, L"[INDEX]\n");
        fwprintf_s(File, L"%d\n", i);
        fwprintf_s(File, L"[KEY]\n");
        fwprintf_s(File, L"%s\n", m_Sprites[i]->GetKey().c_str());
        fwprintf_s(File, L"[PATH]\n");
        fwprintf_s(File, L"%s\n\n", m_Sprites[i]->GetRelativePath().c_str());
    }

    fclose(File);

    return 0;
}

int CFlipbook::Load(const wstring& _RelativePath)
{
    wstring strFilePath = CPathMgr::GetContentPath();
    strFilePath += _RelativePath;

    // Sprite �� Key, RelativePath �� ����
    FILE* File = nullptr;
    _wfopen_s(&File, strFilePath.c_str(), L"r");

    wchar_t Buff[255] = {};

    while (true)
    {
        if (EOF == fwscanf_s(File, L"%s", Buff, 255))
            break;

        wstring strRead = Buff;

        if (strRead == L"[KEY]")
        {
            fwscanf_s(File, L"%s", Buff, 255);
            SetKey(Buff);
        }

        else if (strRead == L"[PATH]")
        {
            fwscanf_s(File, L"%s", Buff, 255);
            SetRelativePath(Buff);
        }

        else if (strRead == L"[SPRITE_COUNT]")
        {
            int SpriteCount = 0;
            fwscanf_s(File, L"%d", &SpriteCount);
            m_Sprites.resize(SpriteCount);
        }

        else if (strRead == L"[INDEX]")
        {
            int index = 0;
            fwscanf_s(File, L"%d", &index);
            fwscanf_s(File, L"%s", Buff, 255);
            fwscanf_s(File, L"%s", Buff, 255);

            wstring SpriteKey = Buff;

            fwscanf_s(File, L"%s", Buff, 255);
            fwscanf_s(File, L"%s", Buff, 255);

            wstring SpritePath = Buff;

            m_Sprites[index] = CAssetMgr::GetInst()->LoadSprite(SpriteKey, SpritePath);
        }
    }


    fclose(File);

    return S_OK;
}

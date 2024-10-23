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

int CFlipbook::Save(const wstring& _RelativePath)
{
    wstring RelativePath = _RelativePath;
    CheckExt(L".flip", RelativePath);

    // 에셋이 자신이 어디에 저장되는지를 알게 함
    SetRelativePath(RelativePath);

    // 최종 저장 경로
    wstring strFilePath = CPathMgr::GetContentPath() + RelativePath;

    // Sprite 의 Key, RelativePath 를 저장
    FILE* File = nullptr;
    _wfopen_s(&File, strFilePath.c_str(), L"w");

    // KEY, Path 저장
    fwprintf_s(File, L"[KEY]\n");
    fwprintf_s(File, L"%s\n", GetKey().c_str());

    fwprintf_s(File, L"[PATH]\n");
    fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

    // Sprite 개수
    fwprintf_s(File, L"[SPRITE_COUNT]\n");
    int SpriteCount = (int)m_Sprites.size();
    fwprintf_s(File, L"%d\n", SpriteCount);

    // 각각의 Sprite 정보 저장
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

    // Sprite 의 Key, RelativePath 를 저장
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

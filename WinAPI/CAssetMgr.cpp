#include "pch.h"
#include "CAssetMgr.h"

#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CSound.h"
#include "CEngine.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
    Delete_Map(m_mapTex);
    Delete_Map(m_mapSprite); 
    Delete_Map(m_mapFlipbook);
    Delete_Map(m_mapSound);
}

void CAssetMgr::Init()
{
   
}

CTexture* CAssetMgr::FindTexture(const wstring& _Key)
{
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    return iter->second;
}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _RelativePath, bool FullPath)
{
    CAsset* pTex = FindTexture(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pTex)
    {
        // 로딩한 텍스쳐를 반환
        return (CTexture*)pTex;
    }

    pTex = new CTexture;
    if(FullPath == true)
    pTex->Load(_RelativePath, FullPath);

    else
        pTex->Load(_RelativePath);


    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pTex->SetKey(_Key);
    pTex->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapTex.insert(make_pair(_Key, (CTexture*)pTex));

    return (CTexture*)pTex;
}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _RelativePath, HDC _hdc, bool FullPath)
{
    CAsset* pTex = FindTexture(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pTex)
    {
        // 로딩한 텍스쳐를 반환
        return (CTexture*)pTex;
    }

    pTex = new CTexture;
    if (FullPath == true)
    {
        if (_hdc == nullptr)
            pTex->Load(_RelativePath, FullPath);
        else
            pTex->Load(_RelativePath, FullPath, _hdc);
    }
    else
        pTex->Load(_RelativePath);


    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pTex->SetKey(_Key);
    pTex->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapTex.insert(make_pair(_Key, (CTexture*)pTex));

    return (CTexture*)pTex;
}

CTexture* CAssetMgr::DrawTexture(CTexture* _texture, Vec2 _Renderpos, Vec2 _scale)
{
    HDC dc = CEngine::GetInst()->GetSecondDC();

    BLENDFUNCTION blend = {};

    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    AlphaBlend(dc
        , _Renderpos.x
        , _Renderpos.y
        , _scale.x
        , _scale.y
        , _texture->GetDC()
        , 0, 0
        , _texture->GetWidth()
        , _texture->GetHeight()
        , blend);


    return nullptr;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height, HDC _hdc)
{
    CTexture* pTex = FindTexture(_Key);
    assert(!pTex);

    pTex = new CTexture;
    if(_hdc == nullptr)
    pTex->Create(_Width, _Height);

    else
        pTex->Create(_Width, _Height , _hdc);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값을 세팅해준다.
    pTex->SetKey(_Key);
  
    // 컨테이너에 텍스쳐 등록
    m_mapTex.insert(make_pair(_Key, (CTexture*)pTex));

    return pTex;
}

CSprite* CAssetMgr::FindSprite(const wstring& _Key)
{
    map<wstring, CSprite*>::iterator iter = m_mapSprite.find(_Key);

    if (iter == m_mapSprite.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSprite* CAssetMgr::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pSprite = FindSprite(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pSprite)
    {
        // 로딩한 텍스쳐를 반환
        return (CSprite*)pSprite;
    }

    pSprite = new CSprite;
    pSprite->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pSprite->SetKey(_Key);
    pSprite->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapSprite.insert(make_pair(_Key, (CSprite*)pSprite));

    return (CSprite*)pSprite;
}

void CAssetMgr::AddSprite(const wstring& _Key, CSprite* _Sprite)
{
    assert(!FindSprite(_Key));

    _Sprite->SetKey(_Key);
    m_mapSprite.insert(make_pair(_Key, _Sprite));
}

void CAssetMgr::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int _blank, int MaxFrame, bool IsRight)
{
    // Sprite 생성하기

    for (int i = 0; i < MaxFrame; ++i)
    {
        CSprite* pSprite = new CSprite;

        if (IsRight == true)
        {
            pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_blank * (MaxFrame - (i + 1))) + (_Slice.x * (MaxFrame - (i + 1))), _LeftTop.y), _Slice);

        }
        else
        {
            pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_blank * i) + (_Slice.x * i), _LeftTop.y), _Slice);
        }
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        AddSprite(Key, pSprite);
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
        mFlipbook->AddSprite(FindSprite(Key));
  
    }


    CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, mFlipbook);
    wstring Path = L"Flipbook\\";
    mFlipbook->Save(Path + _FlipbookName);
}

void CAssetMgr::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, Vec2 _blank, /*한줄에 최대 그림갯수*/int MaxLine, int MaxFrame, bool IsRight)
{
    for (int i = 0; i < MaxFrame; ++i)
    {
        int _y = (i - 1) / MaxLine + 1;
        int _x = i - (_y - 1) * MaxLine;
        CSprite* pSprite = new CSprite;

        if (IsRight == true)
        {
            pSprite->Create(_Atlas, Vec2(_Atlas->GetWidth() - _LeftTop.x - (_Slice.x * (_x + 1)) - (_x * _blank.x), _LeftTop.y + (_blank.y * _y) + (_Slice.y * _y)), _Slice);
        }
        else
        {
            pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_blank.x * _x) + (_Slice.x * _x), _LeftTop.y + (_blank.y * _y) + (_Slice.y * _y)), _Slice);
        }
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        AddSprite(Key, pSprite);
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
        mFlipbook->AddSprite(FindSprite(Key));

    }


    CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, mFlipbook);
    wstring Path = L"Flipbook\\";
    mFlipbook->Save(Path + _FlipbookName);

}

//좌우 반전
void CAssetMgr::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int _blank, int MaxFrame, bool IsRight, bool _Palindrome)
{
    // Sprite 생성하기

    for (int i = 0; i < MaxFrame; ++i)
    {
        CSprite* pSprite = new CSprite;

        if (IsRight == true && _Palindrome == true)
        {
            pSprite->Create(_Atlas, Vec2(_Atlas->GetWidth() - _LeftTop.x  - (_Slice.x  * (i + 1)) - (i * _blank), _LeftTop.y), _Slice);
        }
        wchar_t Key[50] = {};
        swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
        AddSprite(Key, pSprite);
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
        mFlipbook->AddSprite(FindSprite(Key));

    }


    CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, mFlipbook);
    wstring Path = L"Flipbook\\";
    mFlipbook->Save(Path + _FlipbookName);
}


CFlipbook* CAssetMgr::FindFlipbook(const wstring& _Key)
{
    map<wstring, CFlipbook*>::iterator iter = m_mapFlipbook.find(_Key);

    if (iter == m_mapFlipbook.end())
    {
        return nullptr;
    }

    return iter->second;
}

CFlipbook* CAssetMgr::LoadFlipbook(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pFlipbook = FindFlipbook(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pFlipbook)
    {
        // 로딩한 텍스쳐를 반환
        return (CFlipbook*)pFlipbook;
    }

    pFlipbook = new CFlipbook;
    pFlipbook->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pFlipbook->SetKey(_Key);
    pFlipbook->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapFlipbook.insert(make_pair(_Key, (CFlipbook*)pFlipbook));

    return (CFlipbook*)pFlipbook;
}

void CAssetMgr::AddFlipbook(const wstring& _Key, CFlipbook* _Flipbook)
{
    assert(!FindFlipbook(_Key));

    _Flipbook->SetKey(_Key);
    m_mapFlipbook.insert(make_pair(_Key, _Flipbook));
}


CSound* CAssetMgr::FindSound(const wstring& _Key)
{
    map<wstring, CSound*>::iterator iter = m_mapSound.find(_Key);

    if (iter == m_mapSound.end())
    {
        return nullptr;
    }

    return iter->second;
}

CSound* CAssetMgr::LoadSound(const wstring& _Key, const wstring& _RelativePath)
{
    CAsset* pSound = FindSound(_Key);

    // 이미 로딩한 적이 있는 Texture 라면
    if (nullptr != pSound)
    {
        // 로딩한 텍스쳐를 반환
        return (CSound*)pSound;
    }

    pSound = new CSound;
    pSound->Load(_RelativePath);

    // 에셋에, 자신이 에셋매니저에 등록될때 사용된 키값과 로딩할 때 사용한 경로를 세팅해준다.
    pSound->SetKey(_Key);
    pSound->SetRelativePath(_RelativePath);

    // 컨테이너에 텍스쳐 등록
    m_mapSound.insert(make_pair(_Key, (CSound*)pSound));

    return (CSound*)pSound;
}



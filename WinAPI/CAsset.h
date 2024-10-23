#pragma once
#include "CBase.h"


class CAsset :
    public CBase
{
private:
    wstring             m_Key;          // 에셋의 고유한 이름(에셋매니저에서 해당 에셋을 찾아올때 사용)
    wstring             m_RelativePath; // 에셋의 경로
    const ASSET_TYPE    m_Type;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }

protected:
    void CheckExt(const wstring& _Ext, wstring& _strFilePath);
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

private:
    virtual int Save(const wstring& _FilePath) { return S_OK; }
    virtual int Load(const wstring& _FilePath) = 0;

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
    friend class CAssetMgr;
};


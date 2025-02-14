#pragma once
#include "CComponent.h"

class CFlipbook;

class CFlipbookPlayer :
    public CComponent
{
private:
    vector<CFlipbook*>  m_vecFlipbook;  // Flipbook 목록
    CFlipbook*          m_CurFlipbook;  // 현재 재생중인 Flipbook
    int                 m_SpriteIdx;    // 현재 재생중인 Flipbook 에서, 화면에 노출중인 Sprite 인덱스

    float               m_FPS;          // Flipbook 재생속도
    float               m_Time;         // 누적시간
    bool                m_Repeat;       // 반복재생인지 아닌지
    bool                m_Finish;       // 재생이 끝났는지 체크
    bool                m_Right;
    int                 m_FlipNum;

 
    //이전 플립북
    int                 m_BeFlipNum;
    float               m_BeFPS;



public:


    void AddFlipbook(CFlipbook* _Flipbook) { m_vecFlipbook.push_back(_Flipbook); }
    void AddFlipbook(int _idx, CFlipbook* _Flipbook)
    {
        if (m_vecFlipbook.size() <= _idx)
        {
            m_vecFlipbook.resize(_idx + 1);
        }

        m_vecFlipbook[_idx] = _Flipbook;
    }

    void Play(int _FlipbookIdx, float _FPS, bool _Repeat);

    
    bool IsFinish() { return m_Finish; }

    void Reset();

    int GetFlipNum() { return m_FlipNum; }

public:
    virtual void FinalTick() override;
    void Render(); 

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};


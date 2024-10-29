#pragma once
#include "CComponent.h"

class CFlipbook;

class CFlipbookPlayer :
    public CComponent
{
private:
    vector<CFlipbook*>  m_vecFlipbook;  // Flipbook ���
    CFlipbook*          m_CurFlipbook;  // ���� ������� Flipbook
    int                 m_SpriteIdx;    // ���� ������� Flipbook ����, ȭ�鿡 �������� Sprite �ε���

    float               m_FPS;          // Flipbook ����ӵ�
    float               m_Time;         // �����ð�
    bool                m_Repeat;       // �ݺ�������� �ƴ���
    bool                m_Finish;       // ����� �������� üũ
    bool                m_Right;

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


public:
    virtual void FinalTick() override;
    void Render(); 

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};


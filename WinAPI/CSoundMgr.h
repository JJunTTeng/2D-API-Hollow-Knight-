#pragma once

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr)
private:
	LPDIRECTSOUND8		m_SoundeDevice;	// 사운드 카드 제어
	CSound*				m_pBGM;			// BGM Sound


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_SoundeDevice; }
	void RegisterToBGM(CSound* _pSound);
};


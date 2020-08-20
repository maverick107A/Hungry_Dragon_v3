#ifndef FmodMgr_h__
#define FmodMgr_h__

#include "Engine_Define.h"
#include "Base.h"


BEGIN(FMOD)
class Sound;
class System;
class Channel;
END

USING(Engine)

class ENGINE_DLL CFmodMgr : public CBase
{
	DECLARE_SINGLETON(CFmodMgr)

public:
	CFmodMgr();
	~CFmodMgr();

public:
	void Set_BgmVolume(float _fVol) { m_fBgmVolume = _fVol; }
	void Set_SfxVolume(float _fVol) { m_fSfxVolume = _fVol; }
	void Add_BgmVolume(float _fVol) { m_fBgmVolume += _fVol; if (m_fBgmVolume > 1.f) m_fBgmVolume = 1.f; if (m_fBgmVolume < 0.f) m_fBgmVolume = 0.f; }
	void Add_SfxVolume(float _fVol) { m_fSfxVolume += _fVol;  if (m_fSfxVolume > 1.f) m_fSfxVolume = 1.f; if (m_fSfxVolume < 0.f) m_fSfxVolume = 0.f; }
	float Get_BgmVolume() { return m_fBgmVolume; }
	float Get_SfxVolume() { return m_fSfxVolume; }

public:
	void Initialize();
	void Update();
	void Release();

	void Insert_Bgm(const char* _pFilePath, const TCHAR* _pSoundKey);
	void Insert_Sfx(const char* _pFilePath, const TCHAR* _pSoundKey);
	void Insert_Sfx_NoCheck(const char* _pFilePath, const TCHAR* _pSoundKey);
	FMOD::Sound* Find_Sound(const TCHAR* _pSoundKey);

	void PlayBgm(const TCHAR* _pSoundKey);
	void PlayEffect(const TCHAR* _pSoundKey);
	void PlayEffect(FMOD::Sound* _pSound);
	void PlayEffectChartered(const TCHAR* _pSoundKey);
	void PlayEffectChartered(FMOD::Sound* _pSound);
	void PlayLoop(const TCHAR* _pSoundKey);
	void PlayVoice(const TCHAR* _pSoundKey);
	void StopBgm();
	void PauseBgm();
	void ResumeBgm();
	void StopLoop(const TCHAR* _pSoundKey = L"");

	void Bring_Sound();
	
	bool Is_Playing(const TCHAR* _pSoundKey);

private:
	map<const TCHAR*, FMOD::Sound*>	m_mapSnd;

	 FMOD::System*		m_pBgmSystem;
	 FMOD::System*		m_pEffectSystem;
	 FMOD::System*		m_pLoopSystem;
	
	 FMOD::Channel*	m_pEffectChannel[5];
	 FMOD::Channel*	m_pCharterChannel;
	 FMOD::Channel*	m_pBgmChannel;
	 FMOD::Channel*	m_pLoopChannel;

	FMOD::Sound*		m_pCurrPlayingBgm;
	FMOD::Sound*		m_pCurrPlayingLoop;

	int m_iEffectRotate;

	float		m_fBgmVolume = 1.f;
	float		m_fSfxVolume = 1.f;

	// CBase을(를) 통해 상속됨
	virtual void Free(void) override;
};

#endif
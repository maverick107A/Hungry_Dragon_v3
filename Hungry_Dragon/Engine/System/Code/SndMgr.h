#pragma once

class CSndMgr
{
public:
	CSndMgr();
	~CSndMgr();


public:
	void Initialize();
	void Update();
	void Release();

	void Insert_Bgm(const char* _pFilePath, const TCHAR* _pSoundKey);
	void Insert_Sfx(const char* _pFilePath, const TCHAR* _pSoundKey);
	void Insert_Sfx_NoCheck(const char* _pFilePath, const TCHAR* _pSoundKey);
	Sound* Find_Sound(const TCHAR* _pSoundKey);

	void PlayBgm(const TCHAR* _pSoundKey);
	void PlayEffect(const TCHAR* _pSoundKey);
	void PlayEffect(Sound* _pSound);
	void PlayEffectChartered(const TCHAR* _pSoundKey);
	void PlayEffectChartered(Sound* _pSound);
	void PlayLoop(const TCHAR* _pSoundKey);
	void PlayVoice(const TCHAR* _pSoundKey);
	void StopBgm();
	void PauseBgm();
	void ResumeBgm();
	void StopLoop(const TCHAR* _pSoundKey = L"");

	void PlayFire();

	void Bring_Sound();
	
	bool Is_Playing(const TCHAR* _pSoundKey);

public:
	static CSndMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSndMgr;
			m_pInstance->Initialize();
		}
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		Safe_Delete(m_pInstance);
	}

private:
	static CSndMgr*						m_pInstance;

	map<const TCHAR*, Sound*>	m_mapSnd;

	System*		m_pBgmSystem;
	System*		m_pEffectSystem;
	System*		m_pLoopSystem;
	
	Channel*	m_pEffectChannel[5];
	Channel*	m_pCharterChannel;
	Channel*	m_pBgmChannel;
	Channel*	m_pLoopChannel;

	Sound*		m_pCurrPlayingBgm;
	Sound*		m_pCurrPlayingLoop;

	int m_iEffectRotate;

	float		m_fBgmVolume = 1.f;
	float		m_fSfxVolume = 1.f;
};


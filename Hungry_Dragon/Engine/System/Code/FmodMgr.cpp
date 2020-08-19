#include "FmodMgr.h"
#include "fmod.hpp"

USING(Engine)
IMPLEMENT_SINGLETON(CFmodMgr)

using namespace FMOD;
CFmodMgr::CFmodMgr() 
{
}


CFmodMgr::~CFmodMgr()
{
	
}

void CFmodMgr::Initialize()
{
	System_Create(&m_pBgmSystem);
	System_Create(&m_pEffectSystem);
	System_Create(&m_pLoopSystem);
	m_pBgmSystem->init(1, FMOD_INIT_NORMAL, 0);
	m_pEffectSystem->init(10, FMOD_INIT_NORMAL, 0);
	m_pLoopSystem->init(1, FMOD_INIT_NORMAL, 0);

	m_iEffectRotate = 0;

}

void CFmodMgr::Update()
{
	m_pBgmSystem->update();
	m_pEffectSystem->update();
	m_pLoopSystem->update();

	m_pBgmChannel->setVolume(m_fBgmVolume);
	m_pLoopChannel->setVolume(m_fSfxVolume);
	//m_pEffectChannel->setVolume(m_fSfxVolume);
}

void CFmodMgr::Release()
{
	for (auto& iter : m_mapSnd)
	{
		if (nullptr != iter.second)
			iter.second->release();
	}
	m_mapSnd.clear();
	
	m_pLoopChannel->stop();

	m_pBgmSystem->release();
	m_pEffectSystem->release();
	m_pLoopSystem->release();
	m_pBgmSystem->close();
	m_pEffectSystem->close();
	m_pLoopSystem->close();
}

void CFmodMgr::Insert_Bgm(const char * _pFilePath, const TCHAR * _pSoundKey)
{
	auto iter = find_if(m_mapSnd.begin(), m_mapSnd.end(), CTag_Finder(_pSoundKey));

	if (m_mapSnd.end() == iter)
	{
		Sound* pSnd = nullptr;

		m_pBgmSystem->createSound(_pFilePath, FMOD_LOOP_NORMAL, 0, &pSnd);

		m_mapSnd.emplace(_pSoundKey, pSnd);
	}
}

void CFmodMgr::Insert_Sfx(const char * _pFilePath, const TCHAR * _pSoundKey)
{
	auto iter = find_if(m_mapSnd.begin(), m_mapSnd.end(), CTag_Finder(_pSoundKey));

	if (m_mapSnd.end() == iter)
	{
		Sound* pSnd = nullptr;

		m_pEffectSystem->createSound(_pFilePath, FMOD_DEFAULT, 0, &pSnd);

		m_mapSnd.emplace(_pSoundKey, pSnd);
	}
}

void CFmodMgr::Insert_Sfx_NoCheck(const char * _pFilePath, const TCHAR * _pSoundKey)
{

	Sound* pSnd = nullptr;

	m_pEffectSystem->createSound(_pFilePath, FMOD_DEFAULT, 0, &pSnd);

	m_mapSnd.emplace(_pSoundKey, pSnd);

}

Sound* CFmodMgr::Find_Sound(const TCHAR * _pSoundKey)
{
	auto iter = find_if(m_mapSnd.begin(), m_mapSnd.end(), CTag_Finder(_pSoundKey));

	if (m_mapSnd.end() == iter)
		return nullptr;

	return iter->second;
}

void CFmodMgr::PlayBgm(const TCHAR* _pSoundKey)
{
	
	Sound* pSnd = Find_Sound(_pSoundKey);
	if (pSnd)
	{
		m_pBgmSystem->playSound(pSnd, 0, false, &m_pBgmChannel);
		m_pCurrPlayingBgm = pSnd;
	}
	m_pBgmChannel->setVolume(0.5f);
}

void CFmodMgr::PlayEffect(const TCHAR* _pSoundKey)
{
	
	Sound* pSnd = Find_Sound(_pSoundKey);
	if (pSnd)
	{
		m_iEffectRotate = (m_iEffectRotate + 1) % 5;
		m_pEffectSystem->playSound(pSnd, 0, false, &m_pEffectChannel[m_iEffectRotate]);
	}
	m_pEffectChannel[m_iEffectRotate]->setVolume(m_fSfxVolume);
}
void CFmodMgr::PlayEffect(Sound * _pSound)
{
	Sound* pSnd = _pSound;
	
	if (pSnd)
	{
		m_iEffectRotate = (m_iEffectRotate + 1) % 5;
		m_pEffectSystem->playSound(pSnd, 0, false, &m_pEffectChannel[m_iEffectRotate]);
	}
	m_pEffectChannel[m_iEffectRotate]->setVolume(m_fSfxVolume);
}
void CFmodMgr::PlayEffectChartered(const TCHAR * _pSoundKey)
{
	Sound* pSnd = Find_Sound(_pSoundKey);
	if (pSnd)
	{
		m_iEffectRotate = (m_iEffectRotate + 1) % 5;
		m_pEffectSystem->playSound(pSnd, 0, false, &m_pCharterChannel);
	}
	m_pCharterChannel->setVolume(m_fSfxVolume);
}
void CFmodMgr::PlayEffectChartered(Sound * _pSound)
{
	Sound* pSnd = _pSound;

	if (pSnd)
	{
		m_iEffectRotate = (m_iEffectRotate + 1) % 5;
		m_pEffectSystem->playSound(pSnd, 0, false, &m_pCharterChannel);
	}
	m_pCharterChannel->setVolume(m_fSfxVolume);
}
void CFmodMgr::PlayLoop(const TCHAR * _pSoundKey)
{
	Sound* pSnd = Find_Sound(_pSoundKey);
	bool bPlaying;
	m_pLoopChannel->isPlaying(&bPlaying);
	
	if (bPlaying)
	{ 
		if (m_pCurrPlayingLoop == pSnd)
		{
			return;
		}
	}
	m_pLoopChannel->stop();
	m_pLoopSystem->playSound(pSnd, 0, false, &m_pLoopChannel);
	m_pCurrPlayingLoop = pSnd;
}
void CFmodMgr::PlayVoice(const TCHAR* _pSoundKey)
{
	
	Sound* pSnd = Find_Sound(_pSoundKey);
	if (pSnd)
	{
		m_pEffectSystem->playSound(pSnd, 0, false, &m_pLoopChannel);
		m_iEffectRotate = (m_iEffectRotate + 1) % 5;
	}
	m_pLoopChannel->setVolume(0.5f);
}


void CFmodMgr::StopBgm()
{
	m_pBgmChannel->stop();
	m_pCurrPlayingBgm = nullptr;
}

void CFmodMgr::PauseBgm()
{
	m_pBgmChannel->setPaused(true);
}

void CFmodMgr::ResumeBgm()
{
	m_pBgmChannel->setPaused(false);
}

void CFmodMgr::StopLoop(const TCHAR* _pSoundKey)
{
	bool bPlaying = false;
	m_pLoopChannel->isPlaying(&bPlaying);
	if (!bPlaying)
	{
		return;
	}
	if (lstrcmp(_pSoundKey, L""))
	{
		if (m_pCurrPlayingLoop == Find_Sound(_pSoundKey))
		{
			m_pLoopChannel->stop();
			m_pCurrPlayingLoop = nullptr;
		}
	}
	else
	{
		m_pLoopChannel->stop();
		m_pCurrPlayingLoop = nullptr;
	}
}


void CFmodMgr::Bring_Sound()
{
	// bgm


	// loop
	

	// sfx
	
}

bool CFmodMgr::Is_Playing(const TCHAR * _pSoundKey)
{
	return (m_pCurrPlayingBgm == Find_Sound(_pSoundKey));
}

void CFmodMgr::Free(void)
{
	Release();
}

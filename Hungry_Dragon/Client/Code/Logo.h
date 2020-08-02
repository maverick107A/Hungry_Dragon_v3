#ifndef Logo_h__
#define Logo_h__

#include "Define.h"
#include "Scene.h"

//-------------------------------------------------------
//매니저 헤더********************************************
//-------------------------------------------------------
//여기에 매니저 헤더 추가


//-------------------------------------------------------
//기타 헤더**********************************************
//-------------------------------------------------------
//여기에 기타 헤더 추가
#include "BackGround.h"
#include "TestPlayer.h"

//-------------------------------------------------------

using namespace Engine;

class CLogo : public Engine::CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogo(void);

public:
	LOADINGID			Get_LoadingID(void) const { return m_eLoadingID; }
	CRITICAL_SECTION*	Get_Crt(void) { return &m_Crt; }
	_bool				Get_Finish(void) const { return m_bFinish; }
	const _tchar*		Get_String(void) const { return m_szFinish; }

public:
public:
	HRESULT	Ready_Loading(LOADINGID eLoadingID);
	_uint	Loading_ForStage(void);

public:
	static unsigned int CALLBACK Thread_Main(void* pArg);

public:
	static CLogo*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;

private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	LOADINGID			m_eLoadingID;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	_bool				m_bFinish;
	_tchar				m_szFinish[256];
};

#endif // Logo_h__

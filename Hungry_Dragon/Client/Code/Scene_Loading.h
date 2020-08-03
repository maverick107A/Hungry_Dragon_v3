#ifndef Loading_h__
#define Loading_h__

#include "Define.h"
#include "Base.h"

using namespace Engine;

class CScene_Loading : public CBase
{
private:
	explicit CScene_Loading(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Loading(void);

public:
	LOADINGID			Get_LoadingID(void) const { return m_eLoadingID; }
	CRITICAL_SECTION*	Get_Crt(void) { return &m_Crt; }
	_bool				Get_Finish(void) const { return m_bFinish; }
	const _tchar*		Get_String(void) const { return m_szFinish; }
 
public:
	HRESULT	Ready_Loading(LOADINGID eLoadingID);
	_uint	Loading_ForStage(void);

public:
	static unsigned int CALLBACK Thread_Main(void* pArg);

private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	LOADINGID			m_eLoadingID;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	_bool				m_bFinish;
	_tchar				m_szFinish[256];

public:
	static CScene_Loading*	Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eLoading);
private:
	virtual void		Free(void);
};

#endif // Loading_h__

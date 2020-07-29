#ifndef MainApp_h__
#define MainApp_h__

#include "Define.h"
#include "Base.h"
#include "Export_Function.h"

BEGIN(Engine)

class CGraphicDev;
class CManagement;

END
class CMainApp : public CBase
{
private: // 생성자
	explicit CMainApp(void);
	virtual ~CMainApp(void);

	// Get
	// Set
	// Public 함수
	// Public 변수
public:
	HRESULT			Ready_MainApp(void);
	Engine::_int	Update_MainApp(const Engine::_float& fTimeDelta);
	void			Render_MainApp(void);

	// Protected 함수
	// Protected 변수
	// Private 함수
private:
	HRESULT		Set_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	
	HRESULT		Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagementInstance);

	// Private 변수
private:
	Engine::CGraphicDev*		m_pDeviceClass		= nullptr;
	Engine::CManagement*		m_pManagementClass	= nullptr;
	LPDIRECT3DDEVICE9			m_pGraphicDev		= nullptr;

public: // 생성 함수
	static CMainApp*	Create(void);

private: // 해제 함수
	virtual void		Free(void);

};

#endif // MainApp_h__


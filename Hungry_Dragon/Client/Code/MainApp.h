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
private: // ������
	explicit CMainApp(void);
	virtual ~CMainApp(void);

	// Get
	// Set
	// Public �Լ�
	// Public ����
public:
	HRESULT			Ready_MainApp(void);
	Engine::_int	Update_MainApp(const Engine::_float& fTimeDelta);
	void			Render_MainApp(void);

	// Protected �Լ�
	// Protected ����
	// Private �Լ�
private:
	HRESULT		Set_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	
	HRESULT		Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagementInstance);

	// Private ����
private:
	Engine::CGraphicDev*		m_pDeviceClass		= nullptr;
	Engine::CManagement*		m_pManagementClass	= nullptr;
	LPDIRECT3DDEVICE9			m_pGraphicDev		= nullptr;

public: // ���� �Լ�
	static CMainApp*	Create(void);

private: // ���� �Լ�
	virtual void		Free(void);

};

#endif // MainApp_h__


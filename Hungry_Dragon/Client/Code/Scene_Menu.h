#ifndef Scene_Menu_h__
#define Scene_Menu_h__

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
#include "Scene_Loading.h"
#include "BackGround_Logo.h"
#include "Page_Out.h"
//-------------------------------------------------------

using namespace Engine;

class CScene_Menu : public Engine::CScene
{
private:
	explicit CScene_Menu(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Menu(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT	Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax);
	HRESULT	Ready_Layer_Environment(const _tchar* pLayerTag) { return S_OK; }
	HRESULT	Ready_Layer_GameLogic(const _tchar* pLayerTag) { return S_OK; }
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);

private:
	CPage_Out* m_pPageOut = nullptr;
	_uint m_uFocusNum = 0;
	_bool m_bSelected = false;
	CBackGround_Logo* m_pLogo = nullptr;

public:
	static CScene_Menu*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;


};

#endif // Logo_h__

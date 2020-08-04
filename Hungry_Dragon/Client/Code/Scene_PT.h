#ifndef Scene_PT_h__
#define Scene_PT_h__

#include "Define.h"
#include "Scene.h"
#include "TestPlayer.h"

//-------------------------------------------------------
//매니저 헤더********************************************
//-------------------------------------------------------
//여기에 매니저 헤더 추가


//-------------------------------------------------------
//기타 헤더**********************************************
//-------------------------------------------------------
//여기에 기타 헤더 추가
#include "BackGround.h"
//-------------------------------------------------------

using namespace Engine;

class CScene_PT : public Engine::CScene
{
private:
	explicit CScene_PT(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_PT(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT	Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax);
	HRESULT	Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_GameLogic(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);

private:
	bool			m_bWireFrame = true;

public:
	static CScene_PT*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

#endif // Scene_PT_h__

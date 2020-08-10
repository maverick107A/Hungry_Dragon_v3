#ifndef Scene_Cave_h__
#define Scene_Cave_h__

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


//-------------------------------------------------------

using namespace Engine;

class CScene_Cave : public Engine::CScene
{
private:
	explicit CScene_Cave(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Cave(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT	Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax);
	HRESULT	Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_GameLogic(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);
	
public:
	static CScene_Cave*		Create(LPDIRECT3DDEVICE9 pGraphicDev);


private:
	virtual void Free(void) override;
};

#endif // Logo_h__

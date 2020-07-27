#ifndef PlayerTest_h__
#define PlayerTest_h__

#include "Define.h"
#include "Scene.h"
#include "BackGround.h"
#include "TestPlayer.h"

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

class CPlayerTest : public Engine::CScene
{
private:
	explicit CPlayerTest(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerTest(void);

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
	static CPlayerTest*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

#endif // PlayerTest_h__

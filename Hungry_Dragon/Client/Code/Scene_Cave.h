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

#include "Bat_Monster.h"
#include "Horizon_Bat_Monster.h"
//-------------------------------------------------------

using namespace Engine;

class CCave;
class CVent;


class CScene_Cave : public Engine::CScene
{
	enum SCENEPHASE{ PHASE_1 , PHASE_2, PHASE_3, PHASE_4, PHASE_END};
private:
	explicit CScene_Cave(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Cave(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void LateUpdate_Scene(const _float& fTimeDelta)override;
	virtual void Render_Scene(void) override;

private:
	HRESULT	Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax);
	HRESULT	Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_GameLogic(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);
	
private:
	void Switch_Phase(int _iNum);

public:
	static CScene_Cave*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CCave* m_pCave = nullptr;
	CVent* m_pVent = nullptr;
	SCENEPHASE m_ePhaseNum = PHASE_1;


	bool			m_bFogEnable = true;
	ID3DXEffect*	m_pFogEffect = 0;
	D3DXHANDLE		m_hFogTechHandle = 0;

private:
	// 플레이어 받아오는곳
	Engine::CTransform*		pPlayerTransformCom;
private:
	virtual void Free(void) override;
};

#endif // Logo_h__

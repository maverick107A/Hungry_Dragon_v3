#ifndef Scene_Forest_h__
#define Scene_Forest_h__

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
// 몬스터
#include "Monster.h"
#include "Chase_Monster.h"
#include "Bat_Monster.h"
#include "Run_Monster.h"
#include "Jump_Monster.h"
#include "Fly_Monster.h"

#include "Golem.h"

#include "GiantGolem.h"



#include "MonsterBeam.h"
#include "NormalBullet.h"

#include "BackGround.h"


#include "TestPlayer.h"
#include "CavePlayer.h"
#include "SkySphere.h"
#include "Ocean.h"
#include "PlayerUI.h"
#include "Terrain_Locater.h"
#include "Tree_Locater.h"
#include "Animate_Monster.h"
//-------------------------------------------------------

using namespace Engine;

class CScene_Forest : public Engine::CScene {
private:
	explicit CScene_Forest(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Forest(void);

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

public:
	static CScene_Forest*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	bool						m_bWireFrame = false;
	bool						m_bFogEnable = true;
	bool						m_bWireFrameMode = false;
	int							m_iMaskNum=0;
	ID3DXEffect* m_pFogEffect = 0;
	D3DXHANDLE m_hFogTechHandle = 0;

private:
	virtual void Free(void) override;
private:
	// 플레이어 받아오는곳
	Engine::CTransform*		pPlayerTransformCom;

	Engine::CMovingObject*	m_pTempMovingObj;
};

#endif //

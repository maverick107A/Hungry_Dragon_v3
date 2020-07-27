#ifndef Scene_Monster_h__
#define Scene_Monster_h__

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
#include "Monster.h"
#include "Chase_Monster.h"
#include "Run_Monster.h"
#include "Jump_Monster.h"
#include "Terrain.h"
#include "Player.h"
#include "NormalBullet.h"
#include "Fly_Monster.h"
//-------------------------------------------------------

using namespace Engine;

class CScene_Monster : public Engine::CScene {
private:
	explicit CScene_Monster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Monster(void);

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
	static CScene_Monster*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
private:
	// 플레이어 받아오는곳
	Engine::CTransform*		pPlayerTransformCom;
};

#endif // Logo_h__

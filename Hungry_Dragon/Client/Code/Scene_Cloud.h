#ifndef Scene_Cloud_h__
#define Scene_Cloud_h__

#include "Define.h"
#include "Scene.h"

//-------------------------------------------------------
//�Ŵ��� ���********************************************
//-------------------------------------------------------
//���⿡ �Ŵ��� ��� �߰�


//-------------------------------------------------------
//��Ÿ ���**********************************************
//-------------------------------------------------------
//���⿡ ��Ÿ ��� �߰�
// ����
#include "Fly_Monster.h"
#include "FlyGolem.h"
#include "FlyChaseGolem.h"
#include "RedCrystal_Monster.h"

#include "Accel_Torus.h"

#include "NormalBullet.h"


#include "BackGround.h"


#include "TestPlayer.h"
#include "CavePlayer.h"
#include "SkySphere.h"
#include "Ocean.h"
#include "PlayerUI.h"
#include "Cloud_Locater.h"
#include "Cliff_Locater.h"
#include "View_Mask.h"
#include "BillCloud_Locater.h"

//-------------------------------------------------------

using namespace Engine;

class CScene_Cloud : public Engine::CScene {
private:
	explicit CScene_Cloud(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Cloud(void);

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void LateUpdate_Scene(const _float& fTimeDelta)override;
	virtual void Render_Scene(void) override;

private:
	HRESULT	Ready_Resource(LPDIRECT3DDEVICE9 pGraphicDev, RESOURCEID eMax);
	HRESULT	Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_IgnoreEffect(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_GameLogic(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);

public:
	//���Ӹ� ��ġ ����ִ� �Լ�
	void Set_AccelRingPos(Engine::CLayer* pLayer);

public:
	static CScene_Cloud*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	bool						m_bWireFrame = false;
	bool						m_bFogEnable = true;
	ID3DXEffect* m_pFogEffect = 0;
	D3DXHANDLE	m_hFogTechHandle = 0;
	D3DXHANDLE m_hvFog = 0;

	ID3DXEffect* m_pDarkEffect = 0;
	D3DXHANDLE m_hDarkTechHandle = 0;

	FLOAT						m_near = -1.0f;		// ���׽���
	FLOAT						m_far = -0.2f;		// ��������
	
	CBillCloud_Locater*			m_pBillCloudLocater = nullptr;
	CView_Mask*					m_pMaskSprite = nullptr;

	//�ʿ� �ѷ��� �� ����
	_int						m_iRingCnt=40;

private:
	virtual void Free(void) override;
private:
	// �÷��̾� �޾ƿ��°�
	Engine::CTransform*		pPlayerTransformCom;
};

#endif //

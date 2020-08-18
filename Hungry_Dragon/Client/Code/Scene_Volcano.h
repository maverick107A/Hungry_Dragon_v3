#ifndef Scene_Volcano_h__
#define Scene_Volcano_h__

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


#include "BackGround.h"


#include "TestPlayer.h"
#include "RedSky.h"
#include "Lava.h"
#include "PlayerUI.h"
#include "AshCloud_Locater.h"
#include "Volcano_Parts.h"

//-------------------------------------------------------

using namespace Engine;

class CScene_Volcano : public Engine::CScene {
private:
	explicit CScene_Volcano(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Volcano(void);

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
	static CScene_Volcano*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

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
	// �÷��̾� �޾ƿ��°�
	Engine::CTransform*		pPlayerTransformCom;
};

#endif //
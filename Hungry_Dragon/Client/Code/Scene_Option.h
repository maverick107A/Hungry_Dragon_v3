#ifndef Scene_Option_h__
#define Scene_Option_h__

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
#include "BackGround.h"
#include "TestPlayer.h"
#include "Scene_Loading.h"
#include "BackGround_Logo.h"
//-------------------------------------------------------

using namespace Engine;

class CScene_Option : public Engine::CScene
{
private:
	explicit CScene_Option(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene_Option(void);

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
	_uint m_uFocusNum = 0;
	_bool m_bSelected = false;

public:
	static CScene_Option*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;


};

#endif // Logo_h__

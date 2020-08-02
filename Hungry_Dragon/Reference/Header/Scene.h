#ifndef Scene_h__
#define Scene_h__

#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene : public CBase
{ 
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene(void);

public:
	CComponent*		Get_Component(const _tchar* pLayerTag,
								const _tchar* pObjTag,
								const _tchar* pComponentTag,
								COMPONENTID eID);

public:
	virtual	HRESULT	Ready_Scene(void);
	virtual _int	Update_Scene(const _float& fTimeDelta);
	virtual void	Render_Scene(void);


public:	// 편의성 함수 템플릿
	template<typename T>
	HRESULT Register_GameObject(T** _ppOut, CLayer* _pLayer,  const _tchar* _pTag)
	{
		*_ppOut = T::Create(m_pGraphicDev);
		CGameObject* _pObj = static_cast<CGameObject*>(*_ppOut);
		NULL_CHECK_RETURN(_pObj, E_FAIL);
		FAILED_CHECK_RETURN(_pLayer->Add_Object(_pTag, _pObj), E_FAIL);
		_pObj->Set_Address(_pLayer);
		return S_OK;
	}
	// 간소화 버전
	template<typename T>
	HRESULT Register_GameObject(CLayer* _pLayer, const _tchar* _pTag)
	{
		CGameObject* _pObj = static_cast<CGameObject*>(T::Create(m_pGraphicDev));
		NULL_CHECK_RETURN(_pObj, E_FAIL);
		FAILED_CHECK_RETURN(_pLayer->Add_Object(_pTag, _pObj), E_FAIL);
		_pObj->Set_Address(_pLayer);
		return S_OK;
	}


protected:
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	map<const _tchar*, CLayer*>		m_mapLayer;

public:
	virtual void Free(void);
protected:
	_vec3					m_vPlayerPos;
};
END
#endif // Scene_h__

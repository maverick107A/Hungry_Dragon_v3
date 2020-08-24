#include "stdafx.h"
#include "Compass.h"
#include "Export_Function.h"
#include "Terrain.h"
#include "LandTex.h"
#include "Texture.h"



USING(Engine)

CCompass::CCompass(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CCompass::~CCompass(void)
{

}

HRESULT CCompass::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int CCompass::Update_Object(const float& fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	

	return 0;
}

void CCompass::Render_Object(void)
{
	
}

void CCompass::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CCompass::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;



	// buffer
	return S_OK;
}

CCompass* CCompass::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCompass*		pInstance = new CCompass(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

#include "stdafx.h"
#include "Color_Mask.h"
#include "Export_Function.h"
#include "Terrain.h"
#include "LandTex.h"
#include "Texture.h"



USING(Engine)

CColor_Mask::CColor_Mask(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CColor_Mask::~CColor_Mask(void)
{

}

HRESULT CColor_Mask::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

int CColor_Mask::Update_Object(const float& fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	

	return 0;
}

void CColor_Mask::Render_Object(void)
{
	
}

void CColor_Mask::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CColor_Mask::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	return S_OK;
}

CColor_Mask* CColor_Mask::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CColor_Mask*		pInstance = new CColor_Mask(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

HRESULT CColor_Mask::Init_MaskTex(int _iNum)
{
	switch (_iNum)
	{
	case 0:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_BLACK", ID_STATIC, L"Com_Texture"));
		break;
	case 1:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_DARKBLUE", ID_STATIC, L"Com_Texture"));
		break;
	case 2:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_EMERALD", ID_STATIC, L"Com_Texture"));
		break;
	case 3:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_ORANGE", ID_STATIC, L"Com_Texture"));
		break;
	case 4:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_PURPLE", ID_STATIC, L"Com_Texture"));
		break;
	case 5:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_RED", ID_STATIC, L"Com_Texture"));
		break;
	case 6:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_SKYBLUE", ID_STATIC, L"Com_Texture"));
		break;
	case 7:
		FAILED_CHECK(Clone_Component<CTexture>(&m_pTexture, RESOURCE_STAGE, L"TEX_WHITE", ID_STATIC, L"Com_Texture"));
		break;

	}
	
	return S_OK;
}

void CColor_Mask::Set_ColorMask()
{
	m_pTexture->Set_Texture();
}

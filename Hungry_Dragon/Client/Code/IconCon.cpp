#include "stdafx.h"
#include "IconCon.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"



CIconCon::CIconCon(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CIconCon::~CIconCon(void)
{

}

HRESULT CIconCon::Ready_Object(void)
{
	m_bDestroyed = true;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CIconCon::Update_Object(const _float& fTimeDelta)
{
	
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CIconCon::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
}



void CIconCon::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CIconCon::Set_Scale(_uint _uTimes)
{
	m_pTransform->Set_Scale((_float)_uTimes);
}

IDirect3DBaseTexture9* CIconCon::Get_Texture(_uint _uNum)
{
	return m_pTex->Get_Texture(_uNum);
}



void CIconCon::Free(void)
{

	Engine::CGameObject::Free();

	//Safe_Release(m_pBufferCom);
}


HRESULT CIconCon::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CTexture>(&m_pTex, RESOURCE_STAGE, L"Texture_HudIcon", ID_STATIC, L"Com_Tex"));
	//m_pBufferCom = CVICustom::Create(m_pGraphicDev, L"BUFFER_TREEMESH");
	//FAILED_CHECK(Clone_Component<CHeightCol>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CIconCon* CIconCon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIconCon*		pInstance = new CIconCon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


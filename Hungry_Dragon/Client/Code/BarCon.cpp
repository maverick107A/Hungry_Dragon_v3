#include "stdafx.h"
#include "BarCon.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"



CBarCon::CBarCon(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CBarCon::~CBarCon(void)
{

}

HRESULT CBarCon::Ready_Object(void)
{
	m_bDestroyed = true;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CBarCon::Update_Object(const _float& fTimeDelta)
{
	
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CBarCon::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
}



void CBarCon::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CBarCon::Set_Scale(_uint _uTimes)
{
	m_pTransform->Set_Scale((_float)_uTimes);
}

IDirect3DBaseTexture9* CBarCon::Get_Texture(_uint _uNum)
{
	return m_pTex->Get_Texture(_uNum);
}



void CBarCon::Free(void)
{

	Engine::CGameObject::Free();

	//Safe_Release(m_pBufferCom);
}


HRESULT CBarCon::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CTexture>(&m_pTex, RESOURCE_STAGE, L"Texture_GageBar", ID_STATIC, L"Com_Tex"));
	//m_pBufferCom = CVICustom::Create(m_pGraphicDev, L"BUFFER_TREEMESH");
	//FAILED_CHECK(Clone_Component<CHeightCol>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CBarCon* CBarCon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBarCon*		pInstance = new CBarCon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


#include "stdafx.h"
#include "Volcano_Erupt.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"



CVolcano_Erupt::CVolcano_Erupt(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CVolcano_Erupt::~CVolcano_Erupt(void)
{

}

HRESULT CVolcano_Erupt::Ready_Object(void)
{
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CVolcano_Erupt::Update_Object(const _float& fTimeDelta)
{
	
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);


	

	m_uTexFrame = (m_uTexFrame + 1) % 44;

	return 0;
}

void CVolcano_Erupt::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);


	m_pTextureCom->Set_Texture(m_uTexFrame);

	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, false);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, true);

}



void CVolcano_Erupt::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CVolcano_Erupt::Set_Scale(_uint _uTimes)
{
	m_pTransform->Set_Scale((_float)_uTimes);
}



void CVolcano_Erupt::Free(void)
{

	Engine::CGameObject::Free();

	//Safe_Release(m_pBufferCom);
}


HRESULT CVolcano_Erupt::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CTexture>(&m_pTextureCom, RESOURCE_STAGE, L"Texture_Erupt", ID_STATIC, L"Com_Texture"));
	//m_pBufferCom = CVICustom::Create(m_pGraphicDev, L"BUFFER_TREEMESH");
	//FAILED_CHECK(Clone_Component<CHeightCol>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));


	pComponent = m_pBufferCom = dynamic_cast<Engine::CTexture_Square*>
		(Engine::Clone(RESOURCE_STATIC, L"Buffer_TexSquare"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CVolcano_Erupt* CVolcano_Erupt::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVolcano_Erupt*		pInstance = new CVolcano_Erupt(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


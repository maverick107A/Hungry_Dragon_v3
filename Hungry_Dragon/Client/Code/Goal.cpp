#include "stdafx.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Goal.h"


CGoal::CGoal(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
}

CGoal::~CGoal(void)
{
}

HRESULT CGoal::Ready_Object(void)
{

	return S_OK;
}

int CGoal::Update_Object(const float & fTimeDelta)
{

	return 0;
}

void CGoal::Render_Object(void)
{	
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	m_pTextureCom->Set_Texture(0);
	m_pBufferBoradCom->Render_Buffer();
	
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


}

HRESULT CGoal::Add_Component(void)
{

	Engine::CComponent*		pComponent = nullptr;

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	// buffer
	pComponent = m_pBufferBoradCom = dynamic_cast<Engine::CMonsterBoard*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_OUTLINE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Buffer", pComponent);
	
	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(Engine::Clone(RESOURCE_STAGE, L"TEXTURE_OUTLINE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Texture", pComponent);


	return S_OK;
}

CGoal * CGoal::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGoal*		pInstance = new CGoal(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CGoal::Free(void)
{
	Engine::CGameObject::Free();
}

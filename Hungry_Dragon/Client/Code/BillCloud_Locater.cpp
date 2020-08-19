#include "stdafx.h"
#include "BillCloud_Locater.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Terrain_Parts.h"
#include "Ingame_Flow.h"
#include "BillCloud_Object.h"

CBillCloud_Locater::CBillCloud_Locater(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CBillCloud_Locater::~CBillCloud_Locater(void)
{

}

HRESULT CBillCloud_Locater::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

void CBillCloud_Locater::Initialize_Object()
{
	m_pPlayerTrans = static_cast<Engine::CTransform*>(Engine::Get_Component(L"GameLogic", L"TestPlayer", L"Com_Transform", Engine::ID_DYNAMIC));

}

_int CBillCloud_Locater::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;
	//m_pCloud->Update_Object(fTimeDelta);

	return 0;
}

void CBillCloud_Locater::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	for (auto& pObj : m_listRenderGroup)
	{
		pObj->Render_Object();
	}
	//m_pCloud->Render_Object();
	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);

}

void CBillCloud_Locater::Instantiate_Cloud(_vec3 & vPos)
{
}

void CBillCloud_Locater::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/

	Safe_Release(m_pCloud);
	Engine::CGameObject::Free();

	for (auto& pObj : m_vecObjectPool)
	{
		Safe_Release(pObj);
	}

}


HRESULT CBillCloud_Locater::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	
	// 구름 세팅
	m_pCloud = CBillCloud_Object::Create(m_pGraphicDev);
	
	return S_OK;
}

CBillCloud_Locater* CBillCloud_Locater::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBillCloud_Locater*		pInstance = new CBillCloud_Locater(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


#include "stdafx.h"
#include "Tree_Object.h"
#include "Export_Function.h"


CTree_Object::CTree_Object(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CTree_Object::~CTree_Object(void)
{

}

HRESULT CTree_Object::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTree_Object::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CTree_Object::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	
	m_pBufferCom->Render_Buffer();
}



void CTree_Object::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CTree_Object::Set_Scale(_uint _uTimes)
{
	m_pTransform->Set_Scale(_uTimes);
}



void CTree_Object::Free(void)
{

	Engine::CGameObject::Free();

	//Safe_Release(m_pBufferCom);
}


HRESULT CTree_Object::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CVICustom>(&m_pBufferCom, RESOURCE_STAGE, L"BUFFER_TREEMESH", ID_STATIC, L"Com_Buffer"));
	//m_pBufferCom = CVICustom::Create(m_pGraphicDev, L"BUFFER_TREEMESH");
	//FAILED_CHECK(Clone_Component<CHeightCol>(&m_pBufferCom, RESOURCE_STATIC, L"BUFFER_KOREA", ID_STATIC, L"Com_Buffer"));

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	

	return S_OK;
}

CTree_Object* CTree_Object::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTree_Object*		pInstance = new CTree_Object(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


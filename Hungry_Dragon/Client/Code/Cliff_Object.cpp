#include "stdafx.h"
#include "Cliff_Object.h"

#include "Export_Function.h"
#include "HeightCol.h"
#include "Ingame_Flow.h"

CCliff_Object::CCliff_Object(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CCliff_Object::~CCliff_Object(void)
{

}

HRESULT CCliff_Object::Ready_Object(void)
{
	m_uVerCntX = 129;
	m_uVerCntZ = 129;
	m_uLength = 1000;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CCliff_Object::Initialize_Object()
{

}

_int CCliff_Object::Update_Object(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	
	_bool bOutline = true;


	return 0;
}

void CCliff_Object::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//m_pDummy->Render_Buffer();
	m_pGraphicDev->SetTexture(0, 0);


	m_pBufferCom->Render_Buffer();
		
}

void CCliff_Object::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
	m_pTransform->Update_Component(0);
}


void CCliff_Object::Free(void)
{
	// 현재 인게임 플로우에서 소멸중
	/*for (int i = 0; i < 50; ++i)
	{
		Safe_Release(m_pParts[i]);
	}*/


	Engine::CGameObject::Free();

	

}


HRESULT CCliff_Object::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;	

	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));
	FAILED_CHECK_RETURN(Clone_Component<CCliffCylinder>(&m_pBufferCom, RESOURCE_STAGE, L"BUFFER_CLIFFCYLINDER", ID_STATIC, L"Com_Buffer"), E_FAIL);


	return S_OK;
}

CCliff_Object* CCliff_Object::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCliff_Object*		pInstance = new CCliff_Object(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


#include "stdafx.h"
#include "Tree_Object.h"
#include "Export_Function.h"
#include "Ingame_Flow.h"



CTree_Object::CTree_Object(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{
	
}

CTree_Object::~CTree_Object(void)
{

}

HRESULT CTree_Object::Ready_Object(void)
{
	m_bDestroyed = true;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTree_Object::Update_Object(const _float& fTimeDelta)
{
	
	Engine::CGameObject::Update_Object(fTimeDelta);
	//Engine::Add_RenderGroup(Engine::RENDER_PRIORITY, this);


	if (!m_bDestroyed)
	{
		_vec3 vPlayerPos;
		_vec3 vPos;
		CIngame_Flow::GetInstance()->Get_Player()->Get_Info(INFO_POS, &vPlayerPos);
		m_pTransform->Get_Info(INFO_POS, &vPos);
		vPos.y += 20.f;

		

		vPlayerPos -= vPos;
		if (100.f > D3DXVec3Length(&vPlayerPos))
		{
			vPos.y += 80.f;
			Engine::Set_ParticleTrans(Engine::Particle_Create(Engine::PART_LEAF, _vec3(0.f, 0.f, 0.f)), vPos);
			m_bDestroyed = true;
		}
	}
	return 0;
}

void CTree_Object::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);

	if (m_bDestroyed)
	{
		m_pBufferComDest->Render_Buffer();
	}
	else
	{
		m_pBufferCom->Render_Buffer();
	}
}



void CTree_Object::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CTree_Object::Set_Scale(_uint _uTimes)
{
	m_pTransform->Set_Scale((_float)_uTimes);
}



void CTree_Object::Free(void)
{

	Engine::CGameObject::Free();

	//Safe_Release(m_pBufferCom);
}


HRESULT CTree_Object::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	FAILED_CHECK(Clone_Component<CVICustom>(&m_pBufferComDest, RESOURCE_STAGE, L"BUFFER_STUMPMESH", ID_STATIC, L"Com_Buffer2"));
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


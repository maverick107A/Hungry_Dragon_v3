 #include "stdafx.h"
#include "Cave.h"

#include "Export_Function.h"

USING(Engine)

CCave::CCave(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CCave::~CCave(void)
{

}

HRESULT CCave::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fCaveLength = m_pBufferCom->Get_Height();
	m_pTransform->Set_Trans(&_vec3(0.f,0.f, m_fCaveLength*0.5f));
	m_pTransformBeyond->Set_Trans(&_vec3(0.f, 0.f, m_fCaveLength*1.5f ));
	m_fForwardSpeed = 100.f;
	return S_OK;
}

_int CCave::Update_Object(const _float& fTimeDelta)
{
	if (!m_bActive)
	{
		return 0;
	}

	m_pTransform->Add_Trans(&_vec3(0.f, 0.f, -m_fForwardSpeed*fTimeDelta));
	m_pTransformBeyond->Add_Trans(&_vec3(0.f, 0.f, -m_fForwardSpeed*fTimeDelta));

	if (m_bLoop)
	{
		if (-m_fCaveLength*0.5f >= m_pTransform->Get_World()._43)
		{
			m_pTransform->Add_Trans(&_vec3(0.f, 0.f, m_fCaveLength*2.f));

		}
		if (-m_fCaveLength*0.5f >= m_pTransformBeyond->Get_World()._43)
		{
			m_pTransformBeyond->Add_Trans(&_vec3(0.f, 0.f, m_fCaveLength*2.f));

		}
	}

	return 0;
}

void CCave::Render_Object(void)
{
	if (!m_bActive)
	{
		return;
	}

	Engine::CGameObject::Update_Object(float(0));
	//여기까지 레이트업데이트에 넣어줘야함
	

	
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
	m_pTransformBeyond->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
	
	
}

void CCave::Free(void)
{
	Engine::CGameObject::Free();
}


void CCave::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
	m_pTransformBeyond->Set_Trans(&_vec3(_vPos.x, _vPos.y, _vPos.z + m_fCaveLength*1.f));
}

float CCave::Get_EndPoint()
{
	return m_pTransform->Get_World()._43 > m_pTransformBeyond->Get_World()._43 ? 
		   m_pTransform->Get_World()._43 : m_pTransformBeyond->Get_World()._43 ;
}

HRESULT CCave::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK_RETURN(Clone_Component<CCaveCylinder>(&m_pBufferCom, RESOURCE_STAGE, L"BUFFER_CAVECYLINDER", ID_STATIC, L"Com_Buffer"), E_FAIL);
	
	//Transform
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"), E_FAIL);
	FAILED_CHECK_RETURN(Register_Component<CTransform>(&m_pTransformBeyond, ID_DYNAMIC, L"Com_TransformBeyond"), E_FAIL);
	m_pTransform->m_vAngle.y = D3DX_PI;
	m_pTransformBeyond->m_vScale.z = 1.1f;

	return S_OK;
}

CCave* CCave::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCave*		pInstance = new CCave(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


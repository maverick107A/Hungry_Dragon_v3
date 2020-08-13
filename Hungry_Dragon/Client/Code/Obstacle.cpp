#include "stdafx.h"
#include "Obstacle.h"

#include "Export_Function.h"

USING(Engine)

CObstacle::CObstacle(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CObstacle::~CObstacle(void)
{

}

HRESULT CObstacle::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_fForwardSpeed = 400.f;
	return S_OK;
}

_int CObstacle::Update_Object(const _float& fTimeDelta)
{
	if (!m_bActive)
	{
		return 0;
	}

	m_pTransform->Add_Trans(&_vec3(0.f, 0.f, -m_fForwardSpeed*fTimeDelta));

	return 0;
}

void CObstacle::Render_Object(void)
{
	if (!m_bActive)
	{
		return;
	}
	Engine::CGameObject::Update_Object(float(0));
	//여기까지 레이트업데이트에 넣어줘야함
	
	//m_pTex->Set_Texture();
	
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
	
	
}

void CObstacle::Free(void)
{
	Engine::CGameObject::Free();
}


void CObstacle::Set_Trans(_vec3 & _vPos)
{
	m_pTransform->Set_Trans(&_vPos);
}

void CObstacle::Set_RotationX(float _fAngleX)
{
	m_pTransform->m_vAngle.x = _fAngleX;
}

void CObstacle::Set_RotationY(float _fAngleY)
{
	m_pTransform->m_vAngle.y = _fAngleY;
}


HRESULT CObstacle::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	FAILED_CHECK(Clone_Component<CObstacleCube>(&m_pBufferCom, RESOURCE_STAGE, L"BUFFER_OBSTACLECUBE", ID_STATIC, L"Com_Buffer"));
	
	//Transform
	FAILED_CHECK(Register_Component<CTransform>(&m_pTransform, ID_DYNAMIC, L"Com_Transform"));

	// tex
	FAILED_CHECK(Clone_Component<CTexture>(&m_pTex, RESOURCE_STAGE, L"TEX_VENT", ID_STATIC, L"Com_Texture"));

	return S_OK;
}

CObstacle* CObstacle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CObstacle*		pInstance = new CObstacle(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


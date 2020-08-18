#include "stdafx.h"
#include "CavePlayer.h"

#include "Export_Function.h"
#include "CubeDra.h"
#include "CaveCamera.h"
#include "PlayerState.h"
#include "PCaveRush.h"
//#include "CaveCamera.h"

CCavePlayer::CCavePlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPlayerMain(pGraphicDev)
{

}

CCavePlayer::~CCavePlayer(void)
{

}

HRESULT CCavePlayer::Ready_Object(void)
{


	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vInfo[Engine::INFO_POS].x = 0.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 0.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 0.f;

	m_pTransform->Set_Scale(2.f);
	m_fColSize = 4.f;
	return S_OK;
}

void CCavePlayer::Initialize_Object(void)
{
}

int CCavePlayer::Update_Object(const float& fTimeDelta)
{
	m_pCamera->Update_Camera(fTimeDelta, &m_fAngleX, &m_fAngleY, &m_vLook, &m_vUp, m_pTerrain);
	m_pState->Update_State(fTimeDelta);
	m_pCamera->Camera_Set(m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS]);
	//
	State_Change();

	Engine::CGameObject::Update_Object(fTimeDelta);
	return 0;
}

void CCavePlayer::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();

	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end(); ++iter) {
		(*iter)->Render_Buffer();
	}
}

void CCavePlayer::Free(void)
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();) {
		Engine::Safe_Release((*iter));
		iter = m_arrParticle.erase(iter);

	}
	m_arrParticle.clear();

	m_pState->Release();
	Engine::CGameObject::Free();
}


void CCavePlayer::State_Change()
{
	switch (m_eState)
	{
	case STATE_FLYIDLE:
		break;
	}
	m_eState = STATE::STATE_END;
}

HRESULT CCavePlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_CUBEDRA"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Com_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);

	//Camera
	pComponent = m_pCamera = Engine::CCaveCamera::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Camera", pComponent);

	//State
	m_pState = Engine::CPCaveRush::Create();
	m_pState->Enter_State(this);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_State", m_pState);

	return S_OK;
}

void CCavePlayer::Switch_Phase(int _iPhase)
{
	switch (_iPhase)
	{
	case 0:
		static_cast<Engine::CPCaveRush*>(m_pState)->Switch_Phase(0);
		static_cast<Engine::CCaveCamera*>(m_pCamera)->Switch_Phase(0);
		m_pTransform->Set_Scale(2.f);
		break;
	case 1:
		static_cast<Engine::CPCaveRush*>(m_pState)->Switch_Phase(1);
		static_cast<Engine::CCaveCamera*>(m_pCamera)->Switch_Phase(1);
		m_pTransform->Set_Scale(1.f);
		break;
	case 2:
		static_cast<Engine::CPCaveRush*>(m_pState)->Switch_Phase(2);
		static_cast<Engine::CCaveCamera*>(m_pCamera)->Switch_Phase(2);
		m_pTransform->Set_Scale(2.f);
		break;
	}
}

CCavePlayer* CCavePlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCavePlayer*		pInstance = new CCavePlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}
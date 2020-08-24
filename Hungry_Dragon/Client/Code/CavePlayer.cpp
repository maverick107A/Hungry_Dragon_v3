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
	m_pCamera->Update_Camera(fTimeDelta, &m_fAngleX, &m_fAngleY, &m_vLook, &m_vUp, this);
	m_pState->Update_State(fTimeDelta);
	m_pCamera->Camera_Set(m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS]);
	//
	State_Change();

	//�ӽ�
	if (m_bBreath)
	{
		//m_pPartsTrans[PART_JAW]->m_vAngle.x = D3DX_PI*0.125f;
		//m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].y = -sinf(D3DX_PI*0.125f);
		//m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].z = cosf(D3DX_PI*0.125f);

		//m_pPartsTrans[PART_FACE]->m_vAngle.x = -D3DX_PI*0.125f;
		//m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].y = sinf(D3DX_PI*0.125f);
		//m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].z = cosf(D3DX_PI*0.125f);

		////m_pPartsTrans[PART_BODY]->m_vAngle.x = -D3DX_PI*0.125f;
		////m_pPartsTrans[PART_BODY]->m_vInfo[Engine::INFO_POS].y = sinf(D3DX_PI*0.125f);
		//m_pPartsTrans[PART_BODY]->m_vInfo[Engine::INFO_POS].z = -1.5f;
		//m_pPartsTrans[PART_2BODY]->m_vInfo[Engine::INFO_POS].z = -3.f;
		//m_pPartsTrans[PART_3BODY]->m_vInfo[Engine::INFO_POS].z = -4.5f;
	}
	else
	{
		/*m_pPartsTrans[PART_JAW]->m_vAngle.x = m_vAngle;
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].y = -sinf(m_vAngle);
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].z = cosf(m_vAngle);

		m_pPartsTrans[PART_FACE]->m_vAngle.x = -m_vAngle;
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].y = sinf(m_vAngle);
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].z = cosf(m_vAngle);

		m_pPartsTrans[PART_BODY]->m_vInfo[Engine::INFO_POS].z = -1.5f;
		m_pPartsTrans[PART_2BODY]->m_vInfo[Engine::INFO_POS].z = -3.f;
		m_pPartsTrans[PART_3BODY]->m_vInfo[Engine::INFO_POS].z = -4.5f;*/
	}


	if (m_vAngle < 0.f || m_vAngle > D3DX_PI*0.125f)
		m_fSpeed *= -1;
	m_vAngle += m_fSpeed;

	//

	Engine::CGameObject::Update_Object(fTimeDelta);
	return 0;
}

void CCavePlayer::Render_Object(void)
{
	Animation_Render();

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
	//��
	pComponent = m_pPartsBuffer[PART_FACE] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_FACE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Face_Buffer", pComponent);
	//��
	pComponent = m_pPartsBuffer[PART_JAW] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_JAW"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Jaw_Buffer", pComponent);
	//����
	pComponent = m_pPartsBuffer[PART_BODY] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_BODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Body_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
	//��
	//pComponent = m_pPartsTrans[PART_FACE] = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_FaceTransform", pComponent);
	////��
	//pComponent = m_pPartsTrans[PART_JAW] = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_JawTransform", pComponent);
	////����
	//pComponent = m_pPartsTrans[PART_BODY] = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);

	//pComponent = m_pPartsTrans[PART_2BODY] = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_2BodyTransform", pComponent);

	//pComponent = m_pPartsTrans[PART_3BODY] = Engine::CTransform::Create();
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_3BodyTransform", pComponent);

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

void CCavePlayer::Animation_Render()
{
	_matrix matWorld;
	//��
	//matWorld = m_pPartsTrans[PART_FACE]->Get_World() * m_pTransform->Get_World();
	//m_pPartsTrans[PART_FACE]->Set_World(&matWorld);
	//m_pPartsTrans[PART_FACE]->Set_Transform(m_pGraphicDev);
	//m_pPartsBuffer[PART_FACE]->Render_Buffer();
	////��
	//matWorld = m_pPartsTrans[PART_JAW]->Get_World() * m_pTransform->Get_World();
	//m_pPartsTrans[PART_JAW]->Set_World(&matWorld);
	//m_pPartsTrans[PART_JAW]->Set_Transform(m_pGraphicDev);
	//m_pPartsBuffer[PART_JAW]->Render_Buffer();
	////����
	//matWorld = m_pPartsTrans[PART_BODY]->Get_World() * m_matOld1;
	//m_pPartsTrans[PART_BODY]->Set_World(&matWorld);
	//m_pPartsTrans[PART_BODY]->Set_Transform(m_pGraphicDev);
	//m_pPartsBuffer[PART_BODY]->Render_Buffer();

	//matWorld = m_pPartsTrans[PART_2BODY]->Get_World() * m_matOld2;
	//m_pPartsTrans[PART_2BODY]->Set_World(&matWorld);
	//m_pPartsTrans[PART_2BODY]->Set_Transform(m_pGraphicDev);
	//m_pPartsBuffer[PART_BODY]->Render_Buffer();

	//matWorld = m_pPartsTrans[PART_3BODY]->Get_World() * m_matOld3;
	//m_pPartsTrans[PART_3BODY]->Set_World(&matWorld);
	//m_pPartsTrans[PART_3BODY]->Set_Transform(m_pGraphicDev);
	//m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_matOld3 = m_matOld2;
	m_matOld2 = m_matOld1;
	m_matOld1 = m_pTransform->Get_World();
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
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
	//æÛ±º
	pComponent = m_pPartsBuffer[PART_FACE] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_FACE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Face_Buffer", pComponent);
	//≈Œ
	pComponent = m_pPartsBuffer[PART_JAW] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_JAW"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Jaw_Buffer", pComponent);
	//∏ˆ≈Î
	pComponent = m_pPartsBuffer[PART_BODY] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_BODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Body_Buffer", pComponent);
	//≥Ø∞≥
	pComponent = m_pPartsBuffer[PART_WING] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_WING"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Wing_Buffer", pComponent);

	pComponent = m_pPartsBuffer[PART_LWING] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_LWING"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"LWing_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
	//æÛ±º
	pComponent = m_pPartsTrans[PART_FACE] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_FaceTransform", pComponent);
	//≈Œ
	pComponent = m_pPartsTrans[PART_JAW] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_JawTransform", pComponent);
	//∏ˆ≈Î
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_2BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_2BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_3BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_3BodyTransform", pComponent);
	//≥Ø∞≥
	pComponent = m_pPartsTrans[PART_WING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_WingTransform", pComponent);

	pComponent = m_pPartsTrans[PART_LWING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LWingTransform", pComponent);

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
	//æÛ±º
	m_pPartsTrans[PART_FACE]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_FACE]->Render_Buffer();
	//≈Œ
	m_pPartsTrans[PART_JAW]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_JAW]->Render_Buffer();
	//∏ˆ≈Î
	m_pPartsTrans[PART_BODY]->Set_Transform(m_pGraphicDev, m_matOld1);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_2BODY]->Set_Transform(m_pGraphicDev, m_matOld2);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_3BODY]->Set_Transform(m_pGraphicDev, m_matOld3);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_4BODY]->Set_Transform(m_pGraphicDev, m_matOld4);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_5BODY]->Set_Transform(m_pGraphicDev, m_matOld5);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_6BODY]->Set_Transform(m_pGraphicDev, m_matOld5);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_7BODY]->Set_Transform(m_pGraphicDev, m_matOld5);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();
	//≥Ø∞≥
	m_pPartsTrans[PART_WING]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_2BODY]->m_matWorld);
	m_pPartsBuffer[PART_WING]->Render_Buffer();

	m_pPartsTrans[PART_LWING]->Set_Transform(m_pGraphicDev, m_pPartsTrans[PART_2BODY]->m_matWorld);
	m_pPartsBuffer[PART_LWING]->Render_Buffer();

	m_matOld7 = m_matOld6;
	m_matOld6 = m_matOld5;
	m_matOld5 = m_matOld4;
	m_matOld4 = m_matOld3;
	m_matOld3 = m_matOld2;
	m_matOld2 = m_matOld1;
	m_matOld1 = m_pTransform->Get_World();
}

void CCavePlayer::Preset_Animation()
{
	////≥Ø±‚ 0«¡∑π¿”
	//for (int i = 0; i < PARTS_END; ++i)
	//	m_pPartsTrans[i]->m_vScale(1.f,1.f,)

	//for (int i = 0; i < PARTS_END; ++i)
	//	m_pAnimationController->Insert_Scale(ANI_FLY, i, 0, _vec3(1.f, 1.f, 1.f));

	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_BODY, 0, _vec3(0.8f, 0.8f, 0.8f));
	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_2BODY, 0, _vec3(0.8f, 0.8f, 0.8f));
	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_3BODY, 0, _vec3(0.8f, 0.8f, 0.8f));

	//for (int i = 0; i < PARTS_END; ++i)
	//	m_pAnimationController->Insert_Rotate(ANI_FLY, i, 0, _vec3(0.f, 0.f, 0.f));

	//m_pAnimationController->Insert_Rotate(ANI_FLY, PART_WING, 0, _vec3(0.f, D3DX_PI*0.25f, 0.f));
	//m_pAnimationController->Insert_Rotate(ANI_FLY, PART_LWING, 0, _vec3(0.f, -D3DX_PI*0.25f, 0.f));

	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_JAW, 0, _vec3(0.f, 0.f, 1.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_FACE, 0, _vec3(0.f, 0.f, 1.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_BODY, 0, _vec3(0.f, 0.f, -1.5f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_2BODY, 0, _vec3(0.f, 0.f, -3.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_3BODY, 0, _vec3(0.f, 0.f, -4.5f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_WING, 0, _vec3(1.f, 0.f, 3.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_LWING, 0, _vec3(-1.f, 0.f, 3.f));

	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_JAW, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_FACE, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_2BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_3BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_WING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_LWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));

	////≥Ø±‚ 1«¡∑π¿”
	//for (int i = 0; i < PARTS_END; ++i)
	//	m_pAnimationController->Insert_Scale(ANI_FLY, i, 1, _vec3(1.f, 1.f, 1.f));

	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_2BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	//m_pAnimationController->Insert_Scale(ANI_FLY, PART_3BODY, 1, _vec3(0.8f, 0.8f, 0.8f));

	//for (int i = 0; i < PARTS_END; ++i)
	//	m_pAnimationController->Insert_Rotate(ANI_FLY, i, 1, _vec3(0.f, 0.f, 0.f));

	//m_pAnimationController->Insert_Rotate(ANI_FLY, PART_WING, 1, _vec3(0.f, D3DX_PI*0.25f, 0.f));
	//m_pAnimationController->Insert_Rotate(ANI_FLY, PART_LWING, 1, _vec3(0.f, -D3DX_PI*0.25f, 0.f));

	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_JAW, 1, _vec3(0.f, 0.f, 1.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_FACE, 1, _vec3(0.f, 0.f, 1.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_BODY, 1, _vec3(0.f, 0.f, -1.5f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_2BODY, 1, _vec3(0.f, 0.f, -3.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_3BODY, 1, _vec3(0.f, 0.f, -4.5f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_WING, 1, _vec3(1.f, 0.f, 3.f));
	//m_pAnimationController->Insert_Trans(ANI_FLY, PART_LWING, 1, _vec3(-1.f, 0.f, 3.f));

	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_JAW, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_FACE, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_2BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_3BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_WING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	//m_pAnimationController->Insert_Revolute(ANI_FLY, PART_LWING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
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
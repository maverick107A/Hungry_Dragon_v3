#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"
//Vi����

#include "Camera.h"
#include "PlayerState.h"
#include "PFlyIdle.h"
#include "PFly.h"
#include "PLandIdle.h"
#include "PLandRush.h"
#include "PBreathIdle.h"
#include "PBreathFly.h"
#include "BreathBase.h"
#include "Terrain_Locater.h"

CTestPlayer::CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPlayerMain(pGraphicDev)
{

}

CTestPlayer::~CTestPlayer(void)
{

}

HRESULT CTestPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_pTransform->m_vInfo[Engine::INFO_POS].x = 0.f;
	//m_pTransform->m_vInfo[Engine::INFO_POS].y = 0.f;
	//m_pTransform->m_vInfo[Engine::INFO_POS].z = 0.f;

	m_pTransform->Set_Scale(10.f);

	for (int i = 0; i < PARTS_END; ++i)
	{
		m_pPartsTrans[i]->m_vScale = _vec3(1.f, 1.f, 1.f);
	}

	m_pPartsTrans[PART_BODY]->m_vScale = _vec3(0.7f, 0.7f, 0.7f);
	m_pPartsTrans[PART_2BODY]->m_vScale = _vec3(0.7f, 0.7f, 0.7f);
	m_pPartsTrans[PART_3BODY]->m_vScale = _vec3(0.7f, 0.7f, 0.7f);

	D3DXMatrixIdentity(&m_matOld1);
	D3DXMatrixIdentity(&m_matOld2);
	D3DXMatrixIdentity(&m_matOld3);


	m_fColSize = 400.f;
	return S_OK;
}

void CTestPlayer::Initialize_Object(void)
{
	m_pTerrrrrrrain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
	//m_pTerrain = static_cast<Engine::CBaseLand*>(pGroundObj->Get_Component(L"Com_Buffer", Engine::ID_STATIC));
}

int CTestPlayer::Update_Object(const float& fTimeDelta)
{
	m_bAccelCheck = false;
	if (Engine::Get_DIKeyState(DIK_K) & 0x80)
		m_bBreath = !m_bBreath;

	if(m_pTerrrrrrrain)
		m_pTerrain = m_pTerrrrrrrain->Get_Terrain();

	//R Ű ������ ����
	//if ((GetAsyncKeyState('R') & 0x8000) ) {
	//	Engine::_vec3 vOrigin=Engine::_vec3(0.f,0.f,3.f);
	//	Engine::BoundingBox tempBoundingBox;
	//	tempBoundingBox.vMax = Engine::_vec3(WINCX,WINCY,100.f);
	//	tempBoundingBox.vMin = Engine::_vec3(-WINCX, -WINCY, -100.f);
	//	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_WIND, tempBoundingBox, vOrigin);

	//	//���߿� �̸� �÷� ���� ������ ��������
	//	static_cast<Engine::CPart_Wind*>(tempParticle)->Set_Texture(L"../../Asset/snowflake.dds");
	//	m_arrParticle.emplace_back( tempParticle);
	//}

	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();) {
		int life = (*iter)->Update_Component(fTimeDelta);

		if (life == 0) {
			++iter;
		}
		else {
			Safe_Release(*iter);
			iter = m_arrParticle.erase(iter);
		}
	}
	m_pTransform->m_vInCamPos -= m_vUp*1.5f;
	m_pCamera->Update_Camera(fTimeDelta, &m_fAngleX, &m_fAngleY, &m_vLook, &m_vUp, m_pTerrain);
	m_pState->Update_State(fTimeDelta);
	m_pCamera->Camera_Set(m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS]);
	//
	State_Change();

	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	TCHAR szBuff[256] = L"";
	//	wsprintf(szBuff, L"x :%d, z :%d", int(m_pTransform->m_vInfo[Engine::INFO_POS].x * 100), int(m_pTransform->m_vInfo[Engine::INFO_POS].z * 100));
	//	MessageBox(nullptr, szBuff, L"XY", 0);
	//}

	m_pTransform->m_vInCamPos -= m_vUp*0.1f;

	Animations(fTimeDelta);

	Engine::CGameObject::Update_Object(fTimeDelta);
	return 0;
}

void CTestPlayer::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Animation_Render();
	if(m_bBreath)
		m_pBreath->Render_Breath(this);

	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();++iter) {
		(*iter)->Render_Buffer();
	}
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
}

void CTestPlayer::Free(void)
{
	for (list<Engine::CResources*>::iterator iter = m_arrParticle.begin(); iter != m_arrParticle.end();) {
		Engine::Safe_Release((*iter));
		iter = m_arrParticle.erase(iter);

	}
	m_arrParticle.clear();
	
	m_pState->Release();
	Engine::CGameObject::Free();
}


void CTestPlayer::State_Change()
{
	switch (m_eState)
	{
	case STATE_FLYIDLE:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPFlyIdle::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_FLY:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPFly::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_LANDIDLE:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPLandIdle::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_LANDRUSH:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPLandRush::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_BREATHIDLE:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPBreathIdle::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_BREATHFLY:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPBreathFly::Create();
		m_pState->Enter_State(this);
		break;
	}
	m_eState = STATE::STATE_END;
}

HRESULT CTestPlayer::Add_Component(void)
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
	//����
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
	//��
	pComponent = m_pPartsTrans[PART_FACE] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_FaceTransform", pComponent);
	//��
	pComponent = m_pPartsTrans[PART_JAW] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_JawTransform", pComponent);
	//����
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_2BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_2BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_3BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_3BodyTransform", pComponent);
	//����
	pComponent = m_pPartsTrans[PART_WING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_WingTransform", pComponent);

	pComponent = m_pPartsTrans[PART_LWING] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_LWingTransform", pComponent);
	//Camera
	pComponent = m_pCamera = Engine::CCamera::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Camera", pComponent);

	//State
	m_pState = Engine::CPFlyIdle::Create();
	m_pState->Enter_State(this);

	//Breath
	pComponent = m_pBreath = Engine::CBreathBase::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Breath", pComponent);

	return S_OK;
}

CTestPlayer* CTestPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestPlayer*		pInstance = new CTestPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}


void CTestPlayer::Animation_Render()
{
	_matrix matWorld;
	//��
	m_pPartsTrans[PART_FACE]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_FACE]->Render_Buffer();
	//��
	m_pPartsTrans[PART_JAW]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_JAW]->Render_Buffer();
	//����
	m_pPartsTrans[PART_BODY]->Set_Transform(m_pGraphicDev, m_matOld1);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_2BODY]->Set_Transform(m_pGraphicDev, m_matOld2);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_pPartsTrans[PART_3BODY]->Set_Transform(m_pGraphicDev, m_matOld3);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	//����
	m_pPartsTrans[PART_WING]->Set_Transform(m_pGraphicDev, m_matOld2);
	m_pPartsBuffer[PART_WING]->Render_Buffer();

	m_pPartsTrans[PART_LWING]->Set_Transform(m_pGraphicDev, m_matOld2);
	m_pPartsBuffer[PART_LWING]->Render_Buffer();

	m_matOld3 = m_matOld2;
	m_matOld2 = m_matOld1;
	m_matOld1 = m_pTransform->Get_World();
}

void CTestPlayer::Animations(const float& fTimeDelta)
{
	//�ӽ�
	if (0.f < m_fMouseTime)
	{
		m_fMouseTime -= fTimeDelta;
		//m_pPartsTrans[PART_JAW]->m_vAfterAngle.x = m_vAngle;
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.y = -sinf(m_vAngle);
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.z = cosf(m_vAngle);

		//m_pPartsTrans[PART_FACE]->m_vAfterAngle.x = -m_vAngle;
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.y = sinf(m_vAngle);
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.z = cosf(m_vAngle);

		m_pPartsTrans[PART_JAW]->m_vAfterRevAngle.x = m_vAngle;
		m_pPartsTrans[PART_JAW]->m_vAfterPos.z = 1.f;

		m_pPartsTrans[PART_FACE]->m_vAfterRevAngle.x = -m_vAngle;
		m_pPartsTrans[PART_FACE]->m_vAfterPos.z = 1.f;
	}
	else
	{
		//m_pPartsTrans[PART_JAW]->m_vAfterAngle.x = 0.f;
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.y = -sinf(0.f);
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.z = cosf(0.f);

		//m_pPartsTrans[PART_FACE]->m_vAfterAngle.x = -0.f;
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.y = sinf(0.f);
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.z = cosf(0.f);
		m_pPartsTrans[PART_JAW]->m_vAfterRevAngle.x = 0.f;
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.z = 1.f;

		m_pPartsTrans[PART_FACE]->m_vAfterRevAngle.x = -0.f;
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.z = 1.f;
	}

	if (m_bBreath)
	{
		//m_pPartsTrans[PART_JAW]->m_vAfterAngle.x = D3DX_PI*0.15f;
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.y = -sinf(D3DX_PI*0.15f);
		//m_pPartsTrans[PART_JAW]->m_vAfterPos.z = cosf(D3DX_PI*0.15f);

		//m_pPartsTrans[PART_FACE]->m_vAfterAngle.x = -D3DX_PI*0.15f;
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.y = sinf(D3DX_PI*0.15f);
		//m_pPartsTrans[PART_FACE]->m_vAfterPos.z = cosf(D3DX_PI*0.15f);
		m_pPartsTrans[PART_JAW]->m_vAfterRevAngle.x = D3DX_PI*0.15f;
		m_pPartsTrans[PART_JAW]->m_vAfterPos.z = 1.f;

		m_pPartsTrans[PART_FACE]->m_vAfterRevAngle.x = -D3DX_PI*0.15f;
		m_pPartsTrans[PART_FACE]->m_vAfterPos.z = 1.f;
	}
	m_pPartsTrans[PART_BODY]->m_vAfterPos.z = -1.5f;
	m_pPartsTrans[PART_2BODY]->m_vAfterPos.z = -3.f;
	m_pPartsTrans[PART_3BODY]->m_vAfterPos.z = -4.5f;

	m_pPartsTrans[PART_WING]->m_vAfterAngle.z = m_vWAngle;
	m_pPartsTrans[PART_WING]->m_vAfterPos.x = cosf(m_vWAngle);
	m_pPartsTrans[PART_WING]->m_vAfterPos.y = sinf(m_vWAngle);
	m_pPartsTrans[PART_WING]->m_vAfterPos.z = -3.f;

	m_pPartsTrans[PART_LWING]->m_vAfterAngle.z = -m_vWAngle;
	m_pPartsTrans[PART_LWING]->m_vAfterPos.x = -cosf(m_vWAngle);
	m_pPartsTrans[PART_LWING]->m_vAfterPos.y = sinf(m_vWAngle);
	m_pPartsTrans[PART_LWING]->m_vAfterPos.z = -3.f;

	if (m_vWAngle < -D3DX_PI*0.33f || m_vWAngle > D3DX_PI*0.33f)
		m_fWSpeed *= -1;

	if (m_vAngle < 0.f || m_vAngle > D3DX_PI*0.125f)
		m_fSpeed *= -1;
	m_vWAngle += m_fWSpeed;
	m_vAngle += m_fSpeed;

	//
}

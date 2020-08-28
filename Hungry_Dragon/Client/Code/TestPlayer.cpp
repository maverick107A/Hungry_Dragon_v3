#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"
//Vi버퍼

#include "Camera.h"
#include "PlayerState.h"
#include "PFlyIdle.h"
#include "PFly.h"
#include "PLandIdle.h"
#include "PLandRush.h"
#include "PBreathIdle.h"
#include "PBreathFly.h"
#include "BreathBase.h"
#include "PHit.h"
#include "Terrain_Locater.h"
#include "Part_Wind.h"
#include "Line_Renderer.h"

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

	m_pTransform->m_vInfo[Engine::INFO_POS].x = 0.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 1000.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 0.f;

	m_pTransform->Set_Scale(6.f);

	D3DXMatrixIdentity(&m_matOld1);
	D3DXMatrixIdentity(&m_matOld2);
	D3DXMatrixIdentity(&m_matOld3);
	D3DXMatrixIdentity(&m_matOld3);
	D3DXMatrixIdentity(&m_matOld3);
	D3DXMatrixIdentity(&m_matOld3);
	D3DXMatrixIdentity(&m_matOld3);

	m_iBreathRad = 30;

	m_fColSize = 400.f;
	return S_OK;
}

void CTestPlayer::Initialize_Object(void)
{
	m_pTerrrrrrrain = static_cast<CTerrain_Locater*>(((Engine::CLayer*)(Get_Parent()))->Get_Object(L"BackGround", Engine::Find_First, nullptr));
}

int CTestPlayer::Update_Object(const float& fTimeDelta)
{
	m_bAccelCheck = false;
	if (Engine::Get_DIKeyState(DIK_K) & 0x80)
		m_bBreath = !m_bBreath;

	//화면 내에서 플레어이가 아래에 위치하도록
	m_pTransform->m_vInCamPos -= m_vUp*2.f;
	m_pCamera->Update_Camera(fTimeDelta, &m_fAngleX, &m_fAngleY, &m_vLook, &m_vUp, this);
	m_pState->Update_State(fTimeDelta);
	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
	m_pCamera->Camera_Set(m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS], m_pTerrain);
	//
	if (GetAsyncKeyState('H'))
	{
		m_eState = STATE::STATE_HIT;
	}

	State_Change();

	
	for (int i = 0; i < PARTS_END; ++i)
	{
		MOVEMENT nextFrameMovement = m_pAnimationController->Get_Movement(m_eAnimation,i);
		m_pPartsTrans[i]->m_vAfterAngle = nextFrameMovement.vecRot;
		m_pPartsTrans[i]->m_vAfterPos = nextFrameMovement.vecTrans;
		m_pPartsTrans[i]->m_vAfterRevAngle = nextFrameMovement.vecRevolution;
		m_pPartsTrans[i]->m_vScale = nextFrameMovement.vecScale;
	}
	//입 움직이기
	if (0.f < m_fMouseTime) {
		m_fMouseTime -= fTimeDelta;

		m_pPartsTrans[PART_JAW]->m_vAfterRevAngle.x = m_vAngle;
		m_pPartsTrans[PART_JAW]->m_vAfterPos.z = 1.f;

		m_pPartsTrans[PART_FACE]->m_vAfterRevAngle.x = -m_vAngle;
		m_pPartsTrans[PART_FACE]->m_vAfterPos.z = 1.f;
		if (m_vAngle < -D3DX_PI*0.15f || m_vAngle > D3DX_PI*0.33f)
			m_fMSpeed *= -1;
		m_vAngle += m_fMSpeed;
	}
	else
	{
		m_vAngle = 0.f;
		m_fMSpeed = 0.1f;
	}
	
	if (GetAsyncKeyState('P'))
	{
		m_fPlusSpeed = 40.f;
	}

	m_fSpeed = m_fBaseSpeed + m_fPlusSpeed;
	if (m_fPlusSpeed != 0.f)
	{
		m_fPlusSpeed -= fTimeDelta*10.f;
		if (m_fPlusSpeed < 0.f)
			m_fPlusSpeed = 0.f;
	}
	m_fExhaust -= fTimeDelta;

	Engine::CGameObject::Update_Object(fTimeDelta);

	//날개 끝 위치
	_matrix matTotal = m_pPartsTrans[PART_WING]->m_matWorld*m_pPartsTrans[PART_2BODY]->m_matWorld*m_matOld2;
	_vec3 vWing = { 7.1f, -0.4f, -0.3f };
	D3DXVec3TransformCoord(&m_vRWingPos, &vWing, &matTotal);
	matTotal = m_pPartsTrans[PART_LWING]->m_matWorld*m_pPartsTrans[PART_2BODY]->m_matWorld*m_matOld2;
	vWing = { -7.1f, -0.4f, -0.3f };
	D3DXVec3TransformCoord(&m_vLWingPos, &vWing, &matTotal);
	//여기까지

	if (m_bBreath&&m_pParticle == nullptr) {
		_vec3 BeamPos;
		memcpy(&BeamPos, &m_pTransform->m_matWorld._31, sizeof(_vec3));
		m_pParticle = static_cast<CParticle*>(Engine::Particle_Create_Static(Engine::PART_BEAM, BeamPos*2));
		static_cast<CPart_Beam*>(m_pParticle)->Set_Player(this);
		static_cast<CPart_Beam*>(m_pParticle)->Set_Radius(m_iBreathRad);
		static_cast<CPart_Beam*>(m_pParticle)->Manual_Reset_Particle();
		m_pParticle->Set_ZeroToOne(10.f*sqrt(m_iBreathRad), 40.f * sqrt(m_iBreathRad));
		_matrix matMyPos = Get_Transform()->Get_World();
		Engine::Set_StaticParticleTrans(m_pParticle, _vec3(matMyPos._41, matMyPos._42, matMyPos._43));
	}
	else if (!m_bBreath&&m_pParticle!=nullptr) {
		m_pParticle->Set_Empty();
		m_pParticle = nullptr;
	}
	else if (m_bBreath) {
		_matrix matMyPos = Get_Transform()->Get_World();
		Engine::Set_StaticParticleTrans(m_pParticle, _vec3(matMyPos._41, matMyPos._42, matMyPos._43));
	}
	//가속시 윈드파티클
	if (m_fPlusSpeed != 0.f && m_pParticleWind == nullptr)
	{
		_matrix matMyPos = Get_Transform()->Get_World();
		_vec3 vWindStart;
		memcpy(&vWindStart, &matMyPos, sizeof(_vec3));
		m_pParticleWind = static_cast<CParticle*>(Engine::Particle_Create_Static(Engine::PART_WIND, vWindStart * 3));
		static_cast<CPart_Wind*>(m_pParticleWind)->Set_Player(this);
		Engine::Set_StaticParticleTrans(m_pParticleWind, _vec3(matMyPos._41, matMyPos._42, matMyPos._43));
	}
	else if (m_fPlusSpeed == 0.f && m_pParticleWind != nullptr)
	{
		m_pParticleWind->Set_Empty();
		m_pParticleWind = nullptr;
	}
	else if (m_fPlusSpeed != 0.f)
	{
		_matrix matMyPos = Get_Transform()->Get_World();
		Engine::Set_StaticParticleTrans(m_pParticleWind, _vec3(matMyPos._41, matMyPos._42, matMyPos._43));
	}


	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);
	//CLine_Renderer::GetInstance()->Draw_Dot(vPos.x, vPos.y, vPos.z);
	CLine_Renderer::GetInstance()->Draw_Dot(m_vRWingPos.x, m_vRWingPos.y, m_vRWingPos.z, 30.f, 10.f);
	CLine_Renderer::GetInstance()->Draw_Dot(m_vLWingPos.x, m_vLWingPos.y, m_vLWingPos.z, 30.f, 10.f);

	//if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	//{
	//	m_vP = vPos;
	//	m_vL = { m_pTransform->m_matWorld._31,m_pTransform->m_matWorld._32,m_pTransform->m_matWorld._33 };
	//	m_fMouseTime = 0.5f;
	//}
	//m_vP += m_vL*5.f;
	//CLine_Renderer::GetInstance()->Draw_Dot(m_vP.x, m_vP.y, m_vP.z);


	return 0;
}

void CTestPlayer::LateUpdate_Object(const float & fTimeDelta)
{
	if (m_pTerrrrrrrain)
		m_pTerrain = m_pTerrrrrrrain->Get_Terrain();
	m_pState->LateUpdate_State();
}

void CTestPlayer::Render_Object(void)
{
	TCHAR str[64] = L"";
	wsprintf(str, L"POSITION : (%d,%d,%d)", int(m_pTransform->m_vInfo[Engine::INFO_POS].x), int(m_pTransform->m_vInfo[Engine::INFO_POS].y), int(m_pTransform->m_vInfo[Engine::INFO_POS].z));
	Engine::Render_Font(L"Font_Light", str, &_vec2(50.f, 800.f), D3DXCOLOR(1.f, 1.f, 0.f, 1.f));

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Animation_Render();
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//if (m_bBreath) {
	//	m_pBreath->Render_Breath(this);
	//}

	
}

void CTestPlayer::Free(void)
{
	
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
	case STATE_HIT:
		m_pState->Out_State();
		m_pState->Release();
		m_pState = Engine::CPHit::Create();
		m_pState->Enter_State(this);
		break;
	}
	m_eState = STATE::STATE_END;
}

HRESULT CTestPlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	//얼굴
	pComponent = m_pPartsBuffer[PART_FACE] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_FACE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Face_Buffer", pComponent);
	//턱
	pComponent = m_pPartsBuffer[PART_JAW] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_JAW"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Jaw_Buffer", pComponent);
	//몸통
	pComponent = m_pPartsBuffer[PART_BODY] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_BODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Body_Buffer", pComponent);
	//날개
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
	//얼굴
	pComponent = m_pPartsTrans[PART_FACE] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_FaceTransform", pComponent);
	//턱
	pComponent = m_pPartsTrans[PART_JAW] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_JawTransform", pComponent);
	//몸통
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_2BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_2BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_3BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_3BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_4BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_4BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_5BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_5BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_6BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_6BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_7BODY] = Engine::CAnimationTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_7BodyTransform", pComponent);
	//날개
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

	//Breath
	pComponent = m_pBreath = Engine::CBreathBase::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Breath", pComponent);

	//애니메이터
	pComponent = m_pAnimationController = Engine::CAnimation_Controller::Create(PARTS_END);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_AnimationController", pComponent);
	pComponent->Set_Address(this);

	//애니메이션 설정
	Preset_Animation();

	//State
	m_pState = Engine::CPFlyIdle::Create();
	m_pState->Enter_State(this);

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
	//얼굴
	m_pPartsTrans[PART_FACE]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_FACE]->Render_Buffer();
	//턱
	m_pPartsTrans[PART_JAW]->Set_Transform(m_pGraphicDev, m_pTransform->Get_World());
	m_pPartsBuffer[PART_JAW]->Render_Buffer();
	//몸통
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
	//날개
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

void CTestPlayer::Preset_Animation()
{
	m_pAnimationController->Add_Animator(-1);

	//디폴트
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_FACE, 0, _vec3(1.f, 1.f, 1.f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_JAW, 0, _vec3(1.f, 1.f, 1.f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_BODY, 0, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_2BODY, 0, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_3BODY, 0, _vec3(0.7f, 0.7f, 0.7f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_4BODY, 0, _vec3(0.6f, 0.6f, 0.6f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_5BODY, 0, _vec3(0.5f, 0.5f, 0.5f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_6BODY, 0, _vec3(0.4f, 0.4f, 0.4f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_7BODY, 0, _vec3(0.3f, 0.3f, 0.3f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_WING, 0, _vec3(2.f, 2.f, 2.f));
	m_pAnimationController->Insert_Scale(ANI_DEFAULT, PART_LWING, 0, _vec3(2.f, 2.f, 2.f));

	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Rotate(ANI_DEFAULT, i, 0, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_JAW, 0, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_FACE, 0, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_BODY, 0, _vec3(0.f, 0.f, -1.5f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_2BODY, 0, _vec3(0.f, 0.f, -3.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_3BODY, 0, _vec3(0.f, 0.f, -4.5f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_4BODY, 0, _vec3(0.f, 0.f, -6.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_5BODY, 0, _vec3(0.f, 0.f, -7.5f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_6BODY, 0, _vec3(0.f, 0.f, -9.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_7BODY, 0, _vec3(0.f, 0.f, -10.5f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_WING, 0, _vec3(1.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(ANI_DEFAULT, PART_LWING, 0, _vec3(-1.f, 0.f, 0.f));

	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Revolute(ANI_DEFAULT, i, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));

	//애니메이션 추가
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//IDLE
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//Hit
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//Fly
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//BreathIdle
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//BreathFly
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//FASTFLY
	m_pAnimationController->Add_Animator(ANI_DEFAULT);//FASTBREATH

	//IDLE 0프레임
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_WING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, D3DX_PI*0.7f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_LWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -D3DX_PI*0.7f));

	//IDLE 1프레임
	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Scale(ANI_IDLE, i, 1, _vec3(1.f, 1.f, 1.f));

	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_2BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_3BODY, 1, _vec3(0.7f, 0.7f, 0.7f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_4BODY, 1, _vec3(0.6f, 0.6f, 0.6f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_5BODY, 1, _vec3(0.5f, 0.5f, 0.5f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_6BODY, 1, _vec3(0.4f, 0.4f, 0.4f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_7BODY, 1, _vec3(0.3f, 0.3f, 0.3f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_WING, 1, _vec3(2.f, 2.f, 2.f));
	m_pAnimationController->Insert_Scale(ANI_IDLE, PART_LWING, 1, _vec3(2.f, 2.f, 2.f));

	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Rotate(ANI_IDLE, i, 1, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_JAW, 1, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_FACE, 1, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_BODY, 1, _vec3(0.f, 0.f, -1.5f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_2BODY, 1, _vec3(0.f, 0.f, -3.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_3BODY, 1, _vec3(0.f, 0.f, -4.5f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_4BODY, 1, _vec3(0.f, 0.f, -6.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_5BODY, 1, _vec3(0.f, 0.f, -7.5f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_6BODY, 1, _vec3(0.f, 0.f, -9.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_7BODY, 1, _vec3(0.f, 0.f, -10.5f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_WING, 1, _vec3(1.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(ANI_IDLE, PART_LWING, 1, _vec3(-1.f, 0.f, 0.f));

	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_JAW, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_FACE, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_2BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_3BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_4BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_5BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_6BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_7BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_WING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -D3DX_PI*0.7f));
	m_pAnimationController->Insert_Revolute(ANI_IDLE, PART_LWING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, D3DX_PI*0.7f));

	//새로운 애니메이터 생성
	m_pPartsTrans[PART_WING]->m_fDamping = 0.02f;
	m_pPartsTrans[PART_LWING]->m_fDamping = 0.02f;
	m_pPartsTrans[PART_JAW]->m_fDamping = 0.1f;
	m_pPartsTrans[PART_FACE]->m_fDamping = 0.1f;

	//브레스 0프레임
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_JAW, 0, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_FACE, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_WING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, D3DX_PI*0.7f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_LWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -D3DX_PI*0.7f));

	//브레스 1프레임
	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, i, 1, _vec3(1.f, 1.f, 1.f));

	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_2BODY, 1, _vec3(0.8f, 0.8f, 0.8f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_3BODY, 1, _vec3(0.7f, 0.7f, 0.7f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_4BODY, 1, _vec3(0.6f, 0.6f, 0.6f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_5BODY, 1, _vec3(0.5f, 0.5f, 0.5f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_6BODY, 1, _vec3(0.4f, 0.4f, 0.4f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_7BODY, 1, _vec3(0.3f, 0.3f, 0.3f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_WING, 1, _vec3(2.f, 2.f, 2.f));
	m_pAnimationController->Insert_Scale(ANI_BREATHIDLE, PART_LWING, 1, _vec3(2.f, 2.f, 2.f));

	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Rotate(ANI_BREATHIDLE, i, 1, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_JAW, 1, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_FACE, 1, _vec3(0.f, 0.f, 1.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_BODY, 1, _vec3(0.f, 0.f, -1.5f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_2BODY, 1, _vec3(0.f, 0.f, -3.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_3BODY, 1, _vec3(0.f, 0.f, -4.5f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_4BODY, 1, _vec3(0.f, 0.f, -6.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_5BODY, 1, _vec3(0.f, 0.f, -7.5f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_6BODY, 1, _vec3(0.f, 0.f, -9.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_7BODY, 1, _vec3(0.f, 0.f, -10.5f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_WING, 1, _vec3(1.f, 0.f, 0.f));
	m_pAnimationController->Insert_Trans(ANI_BREATHIDLE, PART_LWING, 1, _vec3(-1.f, 0.f, 0.f));

	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_JAW, 1, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_FACE, 1, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_2BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_3BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_4BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_5BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_6BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_7BODY, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_WING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -D3DX_PI*0.7f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHIDLE, PART_LWING, 1, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, D3DX_PI*0.7f));

	//브레스 날기 0프레임
	for (int i = 0; i < PARTS_END; ++i)
		m_pAnimationController->Insert_Rotate(ANI_BREATHFLY, i, 0, _vec3(0.f, 0.f, 0.f));

	m_pAnimationController->Insert_Rotate(ANI_BREATHFLY, PART_WING, 0, _vec3(0.f, D3DX_PI*0.25f, 0.f));
	m_pAnimationController->Insert_Rotate(ANI_BREATHFLY, PART_LWING, 0, _vec3(0.f, -D3DX_PI*0.25f, 0.f));

	m_pAnimationController->Insert_Revolute(ANI_BREATHFLY, PART_JAW, 0, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_BREATHFLY, PART_FACE, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.25f, 0.f, 0.f));

	//날기 0프레임
	m_pAnimationController->Insert_Rotate(ANI_FLY, PART_WING, 0, _vec3(0.f, D3DX_PI*0.25f, 0.f));
	m_pAnimationController->Insert_Rotate(ANI_FLY, PART_LWING, 0, _vec3(0.f, -D3DX_PI*0.25f, 0.f));

	//뻐른날기 0프레임
	m_pAnimationController->Insert_Rotate(ANI_FASTFLY, PART_WING, 0, _vec3(0.f, D3DX_PI*0.5f, 0.f));
	m_pAnimationController->Insert_Rotate(ANI_FASTFLY, PART_LWING, 0, _vec3(0.f, -D3DX_PI*0.5f, 0.f));
	m_pAnimationController->Insert_Trans(ANI_FASTFLY, PART_WING, 0, _vec3(1.f, 0.f, 3.f));
	m_pAnimationController->Insert_Trans(ANI_FASTFLY, PART_LWING, 0, _vec3(-1.f, 0.f, 3.f));

	//빠른브레스 날기 0프레임
	m_pAnimationController->Insert_Rotate(ANI_FASTBREATH, PART_WING, 0, _vec3(0.f, D3DX_PI*0.5f, 0.f));
	m_pAnimationController->Insert_Rotate(ANI_FASTBREATH, PART_LWING, 0, _vec3(0.f, -D3DX_PI*0.5f, 0.f));

	m_pAnimationController->Insert_Trans(ANI_FASTBREATH, PART_WING, 0, _vec3(1.f, 0.f, 3.f));
	m_pAnimationController->Insert_Trans(ANI_FASTBREATH, PART_LWING, 0, _vec3(-1.f, 0.f, 3.f));

	m_pAnimationController->Insert_Revolute(ANI_FASTBREATH, PART_JAW, 0, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_FASTBREATH, PART_FACE, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.25f, 0.f, 0.f));

	//쳐맞기 0프레임
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_JAW, 0, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_FACE, 0, _vec3(0.f, 0.f, 0.f), _vec3(D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_2BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.05f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_3BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.1f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_4BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.15f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_5BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.2f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_6BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.25f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_7BODY, 0, _vec3(0.f, 0.f, 0.f), _vec3(-D3DX_PI*0.3f, 0.f, 0.f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_WING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -D3DX_PI*0.3f));
	m_pAnimationController->Insert_Revolute(ANI_HIT, PART_LWING, 0, _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, D3DX_PI*0.3f));
}

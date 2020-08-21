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

	//애니메이션 테스트

	//R 키 누르면 생성
	//if ((GetAsyncKeyState('R') & 0x8000) ) {
	//	Engine::_vec3 vOrigin=Engine::_vec3(0.f,0.f,3.f);
	//	Engine::BoundingBox tempBoundingBox;
	//	tempBoundingBox.vMax = Engine::_vec3(WINCX,WINCY,100.f);
	//	tempBoundingBox.vMin = Engine::_vec3(-WINCX, -WINCY, -100.f);
	//	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_WIND, tempBoundingBox, vOrigin);

	//	//나중엔 미리 올려 놓는 식으로 구현하자
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
	if (GetAsyncKeyState(VK_F2))
	{
		TCHAR szBuff[256] = L"";
		wsprintf(szBuff, L"x :%d, z :%d", int(m_pTransform->m_vInfo[Engine::INFO_POS].x ), int(m_pTransform->m_vInfo[Engine::INFO_POS].z ));
		MessageBox(nullptr, szBuff, L"XY", 0);
	}

	m_pTransform->m_vInCamPos -= m_vUp*0.1f;

	//Animations(fTimeDelta);2

	Engine::CGameObject::Update_Object(fTimeDelta);

	for (int i = 0; i < PARTS_END; ++i)
	{
		MOVEMENT nextFrameMovement=m_pAnimator->Get_Movement(i);
		m_pPartsTrans[i]->m_vAfterAngle = nextFrameMovement.vecRot;
		m_pPartsTrans[i]->m_vAfterPos = nextFrameMovement.vecTrans;
		m_pPartsTrans[i]->m_vAfterRevAngle = nextFrameMovement.vecRevolution;
		m_pPartsTrans[i]->m_vScale = nextFrameMovement.vecScale;


	}
	return 0;
}

void CTestPlayer::Render_Object(void)
{
	TCHAR str[64] = L"";
	wsprintf(str, L"POSITION : (%d,%d,%d)", int(m_pTransform->m_vInfo[Engine::INFO_POS].x), int(m_pTransform->m_vInfo[Engine::INFO_POS].y), int(m_pTransform->m_vInfo[Engine::INFO_POS].z));
	Engine::Render_Font(L"Font_Light", str, &_vec2(50.f, 10.f), D3DXCOLOR(1.f, 1.f, 0.f, 1.f));

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

	//State
	m_pState = Engine::CPFlyIdle::Create();
	m_pState->Enter_State(this);

	//Breath
	pComponent = m_pBreath = Engine::CBreathBase::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Breath", pComponent);

	//애니메이터
	pComponent = m_pAnimator = Engine::CAnimator::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Animation", pComponent);
	m_pAnimator->Set_PartsSize(PARTS_END);

	//애니메이션 설정
	//Preset_Animation();
	

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

	//날개
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
	//임시
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

void CTestPlayer::Preset_Animation()
{
	//현재 최대 프레임->6

	//얼굴
	m_pAnimator->Insert_Revolute(m_pGraphicDev, PART_JAW, 1, _vec3(0.f, 0.f, 1.f), _vec3(D3DX_PI*0.125f, 0.f, 0.f));
	//m_pAnimator->Insert_Ratate(PART_JAW, 1,_vec3(m_vAngle, 0.f, 0.f));
	m_pAnimator->Insert_Trans(PART_JAW, 0, _vec3(0.f, 0.f, 1.f));
	m_pAnimator->Insert_Trans(PART_JAW, 1, _vec3(0.f, 0.f, 1.f));

	m_pAnimator->Insert_Revolute(m_pGraphicDev, PART_FACE, 1, _vec3(0.f, 0.f, 1.f), _vec3(-D3DX_PI*0.125f, 0.f, 0.f));
	m_pAnimator->Insert_Trans(PART_FACE, 0, _vec3(0.f, 0.f, 1.f));
	m_pAnimator->Insert_Trans(PART_FACE, 1, _vec3(0.f, 0.f, 1.f));

	//몸통
	m_pAnimator->Insert_Trans(PART_BODY, 0, _vec3(0.f, 0.f, -1.5f));
	m_pAnimator->Insert_Trans(PART_BODY, 1, _vec3(0.f, 0.f, -1.5f));

	m_pAnimator->Insert_Trans(PART_2BODY, 0, _vec3(0.f, 0.f, -3.f));
	m_pAnimator->Insert_Trans(PART_2BODY, 1, _vec3(0.f, 0.f, -3.f));

	m_pAnimator->Insert_Trans(PART_3BODY, 0, _vec3(0.f, 0.f, -4.5f));
	m_pAnimator->Insert_Trans(PART_3BODY, 1, _vec3(0.f, 0.f, -4.5f));

	//날개
	m_pPartsTrans[PART_WING]->m_fDamping = 0.02f;
	m_pAnimator->Insert_Ratate(PART_WING, 0, _vec3(0.f, 0.f, D3DX_PI*0.33f));
	m_pAnimator->Insert_Ratate(PART_WING, 1, _vec3(0.f,0.f,-D3DX_PI*0.33f));
	m_pAnimator->Insert_Trans(PART_WING, 0, _vec3(cosf(D3DX_PI*0.33f), sinf(D3DX_PI*0.33f), -3.f));
	m_pAnimator->Insert_Trans(PART_WING, 1, _vec3(cosf(-D3DX_PI*0.33f),sinf(-D3DX_PI*0.33f), -3.f));

	m_pPartsTrans[PART_LWING]->m_fDamping = 0.02f;
	m_pAnimator->Insert_Ratate(PART_LWING, 0, _vec3(0.f, 0.f, -D3DX_PI*0.33f));
	m_pAnimator->Insert_Ratate(PART_LWING, 1, _vec3(0.f, 0.f, D3DX_PI*0.33f));
	m_pAnimator->Insert_Trans(PART_LWING, 0, _vec3(-cosf(D3DX_PI*0.33f), sinf(D3DX_PI*0.33f), -3.f));
	m_pAnimator->Insert_Trans(PART_LWING, 1, _vec3(-cosf(-D3DX_PI*0.33f), sinf(-D3DX_PI*0.33f), -3.f));
}

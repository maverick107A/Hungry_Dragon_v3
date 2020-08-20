#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"
//Vi¹öÆÛ

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
	m_pPartsTrans[PART_BODY]->Set_Scale(0.7f);
	m_pPartsTrans[PART_2BODY]->Set_Scale(0.7f);
	m_pPartsTrans[PART_3BODY]->Set_Scale(0.7f);

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

	//R Å° ´©¸£¸é »ý¼º
	//if ((GetAsyncKeyState('R') & 0x8000) ) {
	//	Engine::_vec3 vOrigin=Engine::_vec3(0.f,0.f,3.f);
	//	Engine::BoundingBox tempBoundingBox;
	//	tempBoundingBox.vMax = Engine::_vec3(WINCX,WINCY,100.f);
	//	tempBoundingBox.vMin = Engine::_vec3(-WINCX, -WINCY, -100.f);
	//	Engine::CResources* tempParticle = Engine::Get_Particle(m_pGraphicDev, Engine::PART_WIND, tempBoundingBox, vOrigin);

	//	//³ªÁß¿£ ¹Ì¸® ¿Ã·Á ³õ´Â ½ÄÀ¸·Î ±¸ÇöÇÏÀÚ
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
	//¾ó±¼
	pComponent = m_pPartsBuffer[PART_FACE] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_FACE"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Face_Buffer", pComponent);
	//ÅÎ
	pComponent = m_pPartsBuffer[PART_JAW] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_JAW"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Jaw_Buffer", pComponent);
	//¸öÅë
	pComponent = m_pPartsBuffer[PART_BODY] = static_cast<Engine::CVIBuffer*>
		(Engine::Clone(RESOURCE_STATIC, L"BUFFER_BODY"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_STATIC].emplace(L"Body_Buffer", pComponent);

	//Transform
	pComponent = m_pTransform = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
	//¾ó±¼
	pComponent = m_pPartsTrans[PART_FACE] = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_FaceTransform", pComponent);
	//ÅÎ
	pComponent = m_pPartsTrans[PART_JAW] = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_JawTransform", pComponent);
	//¸öÅë
	pComponent = m_pPartsTrans[PART_BODY] = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_2BODY] = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_2BodyTransform", pComponent);

	pComponent = m_pPartsTrans[PART_3BODY] = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_3BodyTransform", pComponent);

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
	//¾ó±¼
	matWorld = m_pPartsTrans[PART_FACE]->Get_World() * m_pTransform->Get_World();
	m_pPartsTrans[PART_FACE]->Set_World(&matWorld);
	m_pPartsTrans[PART_FACE]->Set_Transform(m_pGraphicDev);
	m_pPartsBuffer[PART_FACE]->Render_Buffer();
	//ÅÎ
	matWorld = m_pPartsTrans[PART_JAW]->Get_World() * m_pTransform->Get_World();
	m_pPartsTrans[PART_JAW]->Set_World(&matWorld);
	m_pPartsTrans[PART_JAW]->Set_Transform(m_pGraphicDev);
	m_pPartsBuffer[PART_JAW]->Render_Buffer();
	//¸öÅë
	matWorld = m_pPartsTrans[PART_BODY]->Get_World() * m_matOld1;
	m_pPartsTrans[PART_BODY]->Set_World(&matWorld);
	m_pPartsTrans[PART_BODY]->Set_Transform(m_pGraphicDev);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	matWorld = m_pPartsTrans[PART_2BODY]->Get_World() * m_matOld2;
	m_pPartsTrans[PART_2BODY]->Set_World(&matWorld);
	m_pPartsTrans[PART_2BODY]->Set_Transform(m_pGraphicDev);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	matWorld = m_pPartsTrans[PART_3BODY]->Get_World() * m_matOld3;
	m_pPartsTrans[PART_3BODY]->Set_World(&matWorld);
	m_pPartsTrans[PART_3BODY]->Set_Transform(m_pGraphicDev);
	m_pPartsBuffer[PART_BODY]->Render_Buffer();

	m_matOld3 = m_matOld2;
	m_matOld2 = m_matOld1;
	m_matOld1 = m_pTransform->Get_World();
}

void CTestPlayer::Animations(const float& fTimeDelta)
{
	//ÀÓ½Ã
	if (0.f < m_fMouseTime)
	{
		m_fMouseTime -= fTimeDelta;
		m_pPartsTrans[PART_JAW]->m_vAngle.x = m_vAngle;
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].y = -sinf(m_vAngle);
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].z = cosf(m_vAngle);

		m_pPartsTrans[PART_FACE]->m_vAngle.x = -m_vAngle;
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].y = sinf(m_vAngle);
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].z = cosf(m_vAngle);
	}
	else
	{
		m_pPartsTrans[PART_JAW]->m_vAngle.x = 0.f;
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].y = -sinf(0.f);
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].z = cosf(0.f);

		m_pPartsTrans[PART_FACE]->m_vAngle.x = -0.f;
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].y = sinf(0.f);
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].z = cosf(0.f);
	}

	if (m_bBreath)
	{
		m_pPartsTrans[PART_JAW]->m_vAngle.x = D3DX_PI*0.15f;
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].y = -sinf(D3DX_PI*0.15f);
		m_pPartsTrans[PART_JAW]->m_vInfo[Engine::INFO_POS].z = cosf(D3DX_PI*0.15f);

		m_pPartsTrans[PART_FACE]->m_vAngle.x = -D3DX_PI*0.15f;
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].y = sinf(D3DX_PI*0.15f);
		m_pPartsTrans[PART_FACE]->m_vInfo[Engine::INFO_POS].z = cosf(D3DX_PI*0.15f);
	}
	m_pPartsTrans[PART_BODY]->m_vInfo[Engine::INFO_POS].z = -1.5f;
	m_pPartsTrans[PART_2BODY]->m_vInfo[Engine::INFO_POS].z = -3.f;
	m_pPartsTrans[PART_3BODY]->m_vInfo[Engine::INFO_POS].z = -4.5f;


	if (m_vAngle < 0.f || m_vAngle > D3DX_PI*0.125f)
		m_fSpeed *= -1;
	m_vAngle += m_fSpeed;

	//
}

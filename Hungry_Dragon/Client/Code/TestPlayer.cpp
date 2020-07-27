#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"
#include "CubeDra.h"
#include "Camera.h"
#include "PlayerState.h"
#include "PFlyIdle.h"
#include "PFly.h"
#include "PLandIdle.h"
#include "PLandRush.h"

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

	m_pTransform->m_vInfo[Engine::INFO_POS].x = 64.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].z = 64.f;
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 150.f;

	return S_OK;
}

int CTestPlayer::Update_Object(const float& fTimeDelta)
{
	//임시용 레디때로 바꾸던가 밖에서 넣어줘야함
	m_pTerrain = static_cast<Engine::CTerrain*>
		(Engine::Get_Component(L"Environment",
			L"BackGround",
			L"Com_Buffer",
			Engine::ID_STATIC));

	//Key_Input(fTimeDelta);

	//Ride_Terrain();
	

	m_pState->Update_State(fTimeDelta);
	m_pCamera->Update_Component(fTimeDelta, m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS], &m_vLook, &m_vUp, m_pTerrain);
	//
	State_Change();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		TCHAR szBuff[32] = L"";
		wsprintf(szBuff, L"x :%d, y :%d, z :%d", int(m_pTransform->m_vInfo[Engine::INFO_POS].x) * 100, int(m_pTransform->m_vInfo[Engine::INFO_POS].y) * 100, int(m_pTransform->m_vInfo[Engine::INFO_POS].z) * 100);
		MessageBox(nullptr, szBuff, L"XY", 0);
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	return 0;
}

void CTestPlayer::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
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
		m_pState->Release();
		m_pState = Engine::CPFlyIdle::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_FLY:
		m_pState->Release();
		m_pState = Engine::CPFly::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_LANDIDLE:
		m_pState->Release();
		m_pState = Engine::CPLandIdle::Create();
		m_pState->Enter_State(this);
		break;
	case STATE_LANDRUSH:
		m_pState->Release();
		m_pState = Engine::CPLandRush::Create();
		m_pState->Enter_State(this);
		break;
	}
	m_eState = STATE::STATE_END;
}

HRESULT CTestPlayer::Add_Component(void)
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
	pComponent = m_pCamera = Engine::CCamera::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_Camera", pComponent);

	//State
	m_pState = Engine::CPFlyIdle::Create();
	m_pState->Enter_State(this);
	//m_mapComponent[Engine::ID_DYNAMIC].emplace(L"Com_State", m_pState);

	return S_OK;
}

CTestPlayer* CTestPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestPlayer*		pInstance = new CTestPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CTestPlayer::Key_Input(const float& fTimeDelta)
{
	D3DXVECTOR3 vDir = { 0.f,0.f,0.f };
	bool bCheck = false;
	if (GetAsyncKeyState('W'))
	{
		vDir += m_vLook;
		bCheck = true;
	}

	if (GetAsyncKeyState('S'))
	{
		vDir -= m_vLook;
		bCheck = true;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		vDir += D3DXVECTOR3(0.f,1.f,0.f);
		//vDir += m_vUp;
		/*m_pTransform->m_vInfo[Engine::INFO_POS].y += fTimeDelta*m_fSpeed;*/
		bCheck = true;
		m_bLand = false;
	}
	if (GetAsyncKeyState(VK_SHIFT))
	{
		m_bShift = true;
	}
	if (bCheck)
	{
		if (m_bLand)
		{
			vDir.y = 0.f;
			D3DXVec3Normalize(&vDir, &vDir);
			vDir *= fTimeDelta*m_fSpeed;;
			if (m_bShift)
			{
				vDir*=200.f;
				m_bShift = false;
			}
			m_pTransform->m_vInfo[Engine::INFO_POS] += vDir;
			float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
			float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
			float fAngleX = acosf(fPlaneDis / fDis);
			if (0 < vDir.y)
				fAngleX *= -1;
			//m_pTransform->m_vAngle.x = fAngleX;
			m_pTransform->m_vAngle.x = 0.f;
			if(0.f != fPlaneDis)
			{
				float fAngleY = acosf(vDir.z / fPlaneDis);
				if (0 > vDir.x)
					fAngleY *= -1;
				m_pTransform->m_vAngle.y = fAngleY;
				//m_pTransform->m_vAngle.y = m_pCamera->m_fAngleY;
			}

			bCheck = false;
		}
		else
		{
			D3DXVec3Normalize(&vDir, &vDir);
			if (m_bShift)
			{
				vDir*=200.f;
				m_bShift = false;
			}
			vDir *= fTimeDelta*m_fSpeed;;
			m_pTransform->m_vInfo[Engine::INFO_POS] += vDir;
			float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
			float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
			float fAngleX = acosf(fPlaneDis / fDis);
			if (0 < vDir.y)
				fAngleX *= -1;
			m_pTransform->m_vAngle.x = fAngleX;
			//m_pTransform->m_vAngle.x = m_pCamera->m_fAngleX;
			if (0.f != fPlaneDis)
			{
				float fAngleY = acosf(vDir.z / fPlaneDis);
				if (0 > vDir.x)
					fAngleY *= -1;
				m_pTransform->m_vAngle.y = fAngleY;
				//m_pTransform->m_vAngle.y = m_pCamera->m_fAngleY;
			}

			bCheck = false;
		}
	}
}

void CTestPlayer::Ride_Terrain()
{
	m_pTerrain = static_cast<Engine::CTerrain*>
		(Engine::Get_Component(L"Environment",
			L"BackGround",
			L"Com_Buffer",
			Engine::ID_STATIC));

	D3DXVECTOR3* vPos = &m_pTransform->m_vInfo[Engine::INFO_POS];

	//if (vPos->y > 13.f)
	//	return;

	int Vernum = (int(vPos->x*INVERSETILESIZE) + VERTEXSIZE*int(vPos->z*INVERSETILESIZE));

	D3DXVECTOR3 Vertex1 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(vPos->x*INVERSETILESIZE)*TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(vPos->x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(vPos->z*INVERSETILESIZE)*TILECZ + TILECZ) };


	D3DXVECTOR3 vTemp1 = *vPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = m_pTerrain->Get_TerrainHeight()[Vernum] * 0.5f;
		Vertex2.y = m_pTerrain->Get_TerrainHeight()[Vernum + 1] * 0.5f;
		Vertex3.y = m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] * 0.5f;

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		if (m_bLand)
		{
			m_pTransform->m_vInfo[Engine::INFO_POS].y = fTerrainHieght;

			D3DXVec3Normalize(&vNorm, &vNorm);

			m_pTransform->m_vAngle.x = (acosf(vNorm.x*vNorm.x + vNorm.z*vNorm.z) - Pi*0.5f);
		}
		else if (m_pTransform->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght+1)
			m_bLand = true;
	}
	else
	{
		Vertex2.y = m_pTerrain->Get_TerrainHeight()[Vernum + 1] * 0.5f;
		Vertex3.y = m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE] * 0.5f;
		Vertex4.y = m_pTerrain->Get_TerrainHeight()[Vernum + VERTEXSIZE+1] * 0.5f;

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex3);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		if (m_bLand)
		{
			m_pTransform->m_vInfo[Engine::INFO_POS].y = fTerrainHieght;

			D3DXVec3Normalize(&vNorm, &vNorm);
			m_pTransform->m_vAngle.x = acosf(vNorm.x*vNorm.x + vNorm.z*vNorm.z) - Pi*0.5f;
		}
		else if (m_pTransform->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght + 1)
			m_bLand = true;
	}
}


#include "stdafx.h"
#include "TestPlayer.h"

#include "Export_Function.h"
#include "CubeDra.h"
#include "Camera.h"

CTestPlayer::CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
	, m_vLook(0.f, 0.f, 0.f)
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
	m_pTransform->m_vInfo[Engine::INFO_POS].y = 50.f;

	return S_OK;
}

int CTestPlayer::Update_Object(const float& fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	Ride_Terrain();
	
	m_pCamera->Update_Component(fTimeDelta, m_pGraphicDev, m_pTransform->m_vInfo[Engine::INFO_POS], &m_vLook, &m_vUp, m_pTerrain);
	Key_Input(fTimeDelta);

	//

	return 0;
}

void CTestPlayer::Render_Object(void)
{
	m_pTransform->Set_Transform(m_pGraphicDev);
	m_pBufferCom->Render_Buffer();
}

void CTestPlayer::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CTestPlayer::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	// buffer
	pComponent = m_pBufferCom = dynamic_cast<Engine::CCubeDra*>
		(Engine::Clone(RESOURCE_STATIC, L"CubeDra"));
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
		vDir += m_vUp;
		/*m_pTransform->m_vInfo[Engine::INFO_POS].y += fTimeDelta*m_fSpeed;*/
		m_bland = false;
	}
	D3DXVec3Normalize(&vDir, &vDir);
	if (GetAsyncKeyState(VK_SHIFT))
	{
		vDir *= 20.f;
	}
	if (bCheck)
	{
		vDir *= fTimeDelta*m_fSpeed;;
		if (m_bland)
		{
			m_pTransform->m_vInfo[Engine::INFO_POS].x += vDir.x;
			m_pTransform->m_vInfo[Engine::INFO_POS].z += vDir.z;
			float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
			float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
			float fAngleX = acosf(fPlaneDis / fDis);
			if (0 < vDir.y)
				fAngleX *= -1;
			//m_pTransform->m_vAngle.x = fAngleX;
			m_pTransform->m_vAngle.x = 0.f;
			float fAngleY = acosf(vDir.z / fPlaneDis);
			if (0 > vDir.x)
				fAngleY *= -1;
			//m_pTransform->m_vAngle.y = fAngleY;
			m_pTransform->m_vAngle.y = m_pCamera->m_fAngleY;

			bCheck = false;
		}
		else
		{
			m_pTransform->m_vInfo[Engine::INFO_POS] += vDir;
			float fDis = sqrtf(vDir.x*vDir.x + vDir.y*vDir.y + vDir.z*vDir.z);
			float fPlaneDis = sqrtf(vDir.x*vDir.x + vDir.z*vDir.z);
			float fAngleX = acosf(fPlaneDis / fDis);
			if (0 < vDir.y)
				fAngleX *= -1;
			//m_pTransform->m_vAngle.x = fAngleX;
			m_pTransform->m_vAngle.x = m_pCamera->m_fAngleX;
			float fAngleY = acosf(vDir.z / fPlaneDis);
			if (0 > vDir.x)
				fAngleY *= -1;
			//m_pTransform->m_vAngle.y = fAngleY;
			m_pTransform->m_vAngle.y = m_pCamera->m_fAngleY;

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

	int Vernum = (int(vPos->x) + 129*int(vPos->z));

	D3DXVECTOR3 Vertex1 = { float(int(vPos->x)), 0.f, float(int(vPos->z)) };
	D3DXVECTOR3 Vertex2 = { float(int(vPos->x) + 1), 0.f, float(int(vPos->z)) };
	D3DXVECTOR3 Vertex3 = { float(int(vPos->x)), 0.f, float(int(vPos->z) - 1) };
	D3DXVECTOR3 Vertex4 = { float(int(vPos->x) + 1), 0.f, float(int(vPos->z) - 1) };


	D3DXVECTOR3 vTemp1 = *vPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = m_pTerrain->Get_TerrainHeight()[Vernum] * 0.05f;
		Vertex2.y = m_pTerrain->Get_TerrainHeight()[Vernum + 1] * 0.05f;
		Vertex3.y = m_pTerrain->Get_TerrainHeight()[Vernum + 129] * 0.05f;

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		if(m_bland)
			m_pTransform->m_vInfo[Engine::INFO_POS].y = fTerrainHieght;
		else if (m_pTransform->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght+1)
			m_bland = true;
	}
	else
	{
		Vertex2.y = m_pTerrain->Get_TerrainHeight()[Vernum + 1] * 0.05f;
		Vertex3.y = m_pTerrain->Get_TerrainHeight()[Vernum + 129] * 0.05f;
		Vertex4.y = m_pTerrain->Get_TerrainHeight()[Vernum + 130] * 0.05f;

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex2);
		float fTerrainHieght = (fConst - vNorm.x*vPos->x - vNorm.z*vPos->z) / vNorm.y;

		if (m_bland)
			m_pTransform->m_vInfo[Engine::INFO_POS].y = fTerrainHieght;
		else if (m_pTransform->m_vInfo[Engine::INFO_POS].y <= fTerrainHieght + 1)
			m_bland = true;
	}
}


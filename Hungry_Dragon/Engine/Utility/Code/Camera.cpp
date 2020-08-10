#include "Camera.h"
#include "BaseLand.h"

USING(Engine)

Engine::CCamera::CCamera(void)
{
}

Engine::CCamera::~CCamera(void)
{

}

HRESULT Engine::CCamera::Ready_Camera(void)
{
	m_tCenter = { LONG(WINCX*0.5), LONG(WINCY*0.5) };
	SetCursorPos(m_tCenter.x, m_tCenter.y);
	return S_OK;
}

_int Engine::CCamera::Update_Camera(const _float& fTimeDelta, LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up, CBaseLand* _pTerrain)
{
	//Move_Camera_InMFC(pGraphicDev, _vPos, _vLook, _Up);
		Move_Camera(pGraphicDev, _vPos, _vLook, _Up);
		//지형타기
		Ride_Terrain(_pTerrain);

//#ifndef MFC_h__
//	//카메라 이동
//	Move_Camera(pGraphicDev, _vPos, _vLook, _Up);
//	//지형타기
//	Ride_Terrain(_pTerrain);
//#else
//	Move_Camera_InMFC(pGraphicDev, _vPos, _vLook, _Up);
//#endif

	//m_vDir = m_vPos + m_vDir;

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp1);
	pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
}

_int CCamera::Update_CameraMFC(LPDIRECT3DDEVICE9 & _pGraphicDev, _vec3 _vPos, _vec3 * _vLook, _vec3 * _vUp) {
	Move_Camera_InMFC(_pGraphicDev, _vPos, _vLook, _vUp);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp1);
	_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
}

void CCamera::Move_Camera(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, _vec3 * _vLook, _vec3 * _Up)
{
	POINT tPos = {};
	GetCursorPos(&tPos);
	m_fAngleY += (tPos.x - m_tCenter.x)*0.01f*cosf(m_fAngleZ) + (tPos.y - m_tCenter.y)*0.01f*sinf(m_fAngleZ);
	m_fAngleX += (tPos.y - m_tCenter.y)*0.01f*cosf(m_fAngleZ) + -(tPos.x - m_tCenter.x)*0.01f*sinf(m_fAngleZ);

	D3DXMATRIX vRotZ;
	D3DXMatrixRotationZ(&vRotZ, m_fAngleZ);
	D3DXVec3TransformNormal(&m_vUp, &m_vUpOrigin, &vRotZ);

	D3DXMATRIX vRotX, vRotY, vRotTotal;
	D3DXMatrixRotationX(&vRotX, m_fAngleX);
	D3DXMatrixRotationY(&vRotY, m_fAngleY);

	vRotTotal = vRotX*vRotY;
	D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRotTotal);
	//업백터
	D3DXVec3TransformNormal(&m_vUp1, &m_vUp, &vRotTotal);
	*_Up = m_vUp1;

	SetCursorPos(m_tCenter.x, m_tCenter.y);

	m_vDir1 = m_vDir;
	memcpy(_vLook, &m_vDir, sizeof(D3DXVECTOR3));

	m_vPos = _vPos - m_vDir*m_fCameraDis;

	m_vDir = m_vPos + m_vDir;
}

void CCamera::Move_Camera_InMFC(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, _vec3 * _vLook, _vec3 * _Up)
{
	POINT tPos = {};
	GetCursorPos(&tPos);
	m_fCameraDis = 0.f;
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_fAngleY += (tPos.x - m_tCenter.x)*0.01f*cosf(m_fAngleZ) + (tPos.y - m_tCenter.y)*0.01f*sinf(m_fAngleZ);
		m_fAngleX += (tPos.y - m_tCenter.y)*0.01f*cosf(m_fAngleZ) + -(tPos.x - m_tCenter.x)*0.01f*sinf(m_fAngleZ);

		D3DXMATRIX vRotZ;
		D3DXMatrixRotationZ(&vRotZ, m_fAngleZ);
		D3DXVec3TransformNormal(&m_vUp, &m_vUpOrigin, &vRotZ);

		D3DXMATRIX vRotX, vRotY, vRotTotal;
		D3DXMatrixRotationX(&vRotX, m_fAngleX);
		D3DXMatrixRotationY(&vRotY, m_fAngleY);

		vRotTotal = vRotX*vRotY;
		D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRotTotal);
		//업백터
		D3DXVec3TransformNormal(&m_vUp1, &m_vUp, &vRotTotal);
		*_Up = m_vUp1;

		m_vDir1 = m_vDir;
		memcpy(_vLook, &m_vDir, sizeof(D3DXVECTOR3));

		m_vPos = _vPos - m_vDir*m_fCameraDis;

		m_vDir = m_vPos + m_vDir;
	}
	m_tCenter = tPos;
	SetCursorPos(m_tCenter.x, m_tCenter.y);
}

void CCamera::Ride_Terrain(CBaseLand* _pTerrain)
{
	int Vernum = (int(m_vPos.x*INVERSETILESIZE) + VERTEXSIZE*int(m_vPos.z*INVERSETILESIZE));

	if (0 > Vernum || VERTEXSIZE*(VERTEXSIZE - 1) - 1 < Vernum)
	{
	}
	else
	{
		D3DXVECTOR3 Vertex1 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
		D3DXVECTOR3 Vertex2 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
		D3DXVECTOR3 Vertex3 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };
		D3DXVECTOR3 Vertex4 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };


		D3DXVECTOR3 vTemp1 = m_vPos - Vertex3;
		D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
		if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
		{
			Vertex1.y = _pTerrain->Get_TerrainHeight()[Vernum] + 1.f;
			Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1] + 1.f;
			Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129] + 1.f;

			vTemp1 = Vertex2 - Vertex1;
			vTemp2 = Vertex3 - Vertex1;
			D3DXVECTOR3 vNorm = {};
			D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

			float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
			float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

			if (m_vPos.y < fTerrainHieght)
			{
				m_fCameraDis = 0.f;
				if (m_fCameraDis < 0.f)
					m_fCameraDis = 0.f;
			}
			else if (m_fCameraDis < 15.f)
				m_fCameraDis += m_fCameraDisSpeed;
		}
		else
		{
			Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1] + 1.f;
			Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129] + 1.f;
			Vertex4.y = _pTerrain->Get_TerrainHeight()[Vernum + 130] + 1.f;

			vTemp1 = Vertex3 - Vertex4;
			vTemp2 = Vertex2 - Vertex4;
			D3DXVECTOR3 vNorm = {};
			D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

			float fConst = D3DXVec3Dot(&vNorm, &Vertex2);
			float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

			if (m_vPos.y < fTerrainHieght)
			{
				m_fCameraDis = 0.f;
				if (m_fCameraDis < 0.f)
					m_fCameraDis = 0.f;
			}
			else if (m_fCameraDis < 15.f)
				m_fCameraDis += m_fCameraDisSpeed;
		}
	}
}

CCamera* Engine::CCamera::Create(void)
{
	CCamera*	pInstance = new CCamera;

	if (FAILED(pInstance->Ready_Camera()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CCamera::Free(void)
{

}

CComponent* Engine::CCamera::Clone(void)
{
	return new CCamera(*this);
}

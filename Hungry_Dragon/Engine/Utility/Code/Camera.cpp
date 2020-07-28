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

	return S_OK;
}

_int Engine::CCamera::Update_Component(const _float& fTimeDelta, LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, _vec3* _vLook, _vec3* _Up, CBaseLand* _pTerrain)
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
	//¾÷¹éÅÍ
	D3DXVec3TransformNormal(&m_vUp1, &m_vUp, &vRotTotal);
	*_Up = m_vUp1;

	SetCursorPos(m_tCenter.x, m_tCenter.y);

	m_vDir1 = m_vDir;
	memcpy(_vLook, &m_vDir, sizeof(D3DXVECTOR3));

	m_vPos = _vPos - m_vDir*m_fCameraDis;

	//faskjfsadlkfjaldskjf
	/*int Vernum = (int(m_vPos.x*INVERSETILESIZE) + VERTEXSIZE*int(m_vPos.z*INVERSETILESIZE));

	D3DXVECTOR3 Vertex1 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex2 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ) };
	D3DXVECTOR3 Vertex3 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };
	D3DXVECTOR3 Vertex4 = { float(int(m_vPos.x*INVERSETILESIZE)*TILECX + TILECX), 0.f, float(int(m_vPos.z*INVERSETILESIZE)*TILECZ + TILECZ) };


	D3DXVECTOR3 vTemp1 = m_vPos - Vertex3;
	D3DXVECTOR3	vTemp2 = { -1.f,0.f,-1.f };
	if (D3DXVec3Dot(&vTemp1, &vTemp2) > 0)
	{
		Vertex1.y = _pTerrain->Get_TerrainHeight()[Vernum];
		Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1];
		Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129];

		vTemp1 = Vertex2 - Vertex1;
		vTemp2 = Vertex3 - Vertex1;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex1);
		float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

		if (m_vPos.y < fTerrainHieght)
		{
			m_fCameraDis -= 0.5f;
			if (m_fCameraDis < 0.f)
				m_fCameraDis = 0.f;
		}
		else if (m_fCameraDis < 10.f)
			m_fCameraDis += 0.5f;
	}
	else
	{
		Vertex2.y = _pTerrain->Get_TerrainHeight()[Vernum + 1];
		Vertex3.y = _pTerrain->Get_TerrainHeight()[Vernum + 129];
		Vertex4.y = _pTerrain->Get_TerrainHeight()[Vernum + 130];

		vTemp1 = Vertex3 - Vertex4;
		vTemp2 = Vertex2 - Vertex4;
		D3DXVECTOR3 vNorm = {};
		D3DXVec3Cross(&vNorm, &vTemp1, &vTemp2);

		float fConst = D3DXVec3Dot(&vNorm, &Vertex2);
		float fTerrainHieght = (fConst - vNorm.x*m_vPos.x - vNorm.z*m_vPos.z) / vNorm.y;

		if (m_vPos.y < fTerrainHieght)
		{
			m_fCameraDis -= 0.5f;
			if (m_fCameraDis < 0.f)
				m_fCameraDis = 0.f;
		}
		else if (m_fCameraDis < 10.f)
			m_fCameraDis += 0.5f;
	}*/
	//sadkfjdsalkjfalkdsjfaldsk

	m_vDir = m_vPos + m_vDir;

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp1);
	pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
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

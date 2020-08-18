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
	m_fCameraDis = 100.f;
	return S_OK;
}

_int Engine::CCamera::Update_Camera(const _float& _fTimeDelta, float* _fAngleX, float* _fAngleY, _vec3* _vLook, _vec3* _vUp, CBaseLand* _pTerrain)
{
	if (GetAsyncKeyState(VK_F1) & 0x0001)
		m_bLock = !m_bLock;

	Move_Camera(_fAngleX, _fAngleY, _vLook, _vUp);
	//지형타기
	//Ride_Terrain(_pTerrain);

	return 0;
}

_int CCamera::Update_CameraMFC(LPDIRECT3DDEVICE9 & _pGraphicDev, _vec3 _vPos, _vec3 * _vLook, _vec3 * _vUp) {
	Move_Camera_InMFC(_pGraphicDev, _vPos, _vLook, _vUp);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp);
	_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
}

void CCamera::Move_Camera(float* _fAngleX, float* _fAngleY, _vec3* _vLook, _vec3* _vUp)
{
	if (m_bLock)
		return;
	POINT tPos = {};
	GetCursorPos(&tPos);
	//짜증나는코드
	float fYPlus;
	if(cosf(m_vAfterAngle.x) > 0)
		fYPlus = ((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0005f;
	else
		fYPlus = -((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0005f;
	//끝
	m_vAfterAngle.y += fYPlus;
	m_vAfterAngle.x += ((tPos.y - m_tCenter.y)*cosf(m_vAngle.z) - (tPos.x - m_tCenter.x)*sinf(m_vAngle.z))*0.0005f;
	memcpy(_fAngleX, &m_vAfterAngle.x, sizeof(float));
	memcpy(_fAngleY, &m_vAfterAngle.y, sizeof(float));

	float DeltaAngleX = m_vAfterAngle.x - m_vAngle.x;
	float DeltaAngleY = m_vAfterAngle.y - m_vAngle.y;

	m_vAngle.x += DeltaAngleX*0.05f;
	m_vAngle.y += DeltaAngleY*0.05f;

	D3DXMATRIX vRotZ;
	D3DXMatrixRotationZ(&vRotZ, m_vAngle.z);
	D3DXVec3TransformNormal(&m_vUp, &m_vUpOrigin, &vRotZ);

	D3DXMATRIX vRotX, vRotY, vRotTotal;
	D3DXMatrixRotationX(&vRotX, m_vAngle.x);
	D3DXMatrixRotationY(&vRotY, m_vAngle.y);

	vRotTotal = vRotX*vRotY;
	D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRotTotal);
	memcpy(_vLook, &m_vDir, sizeof(_vec3));
	//업백터
	D3DXVec3TransformNormal(&m_vUp, &m_vUp, &vRotTotal);
	memcpy(_vUp, &m_vUp, sizeof(_vec3));
	SetCursorPos(m_tCenter.x, m_tCenter.y);
}

void CCamera::Move_Camera_InMFC(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, _vec3 * _vLook, _vec3 * _Up)
{
	POINT tPos = {};
	GetCursorPos(&tPos);
	m_fCameraDis = 0.f;
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_vAngle.y += (tPos.x - m_tCenter.x)*0.01f*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*0.01f*sinf(m_vAngle.z);
		m_vAngle.x += (tPos.y - m_tCenter.y)*0.01f*cosf(m_vAngle.z) + -(tPos.x - m_tCenter.x)*0.01f*sinf(m_vAngle.z);

		D3DXMATRIX vRotZ;
		D3DXMatrixRotationZ(&vRotZ, m_vAngle.z);
		D3DXVec3TransformNormal(&m_vUp, &m_vUpOrigin, &vRotZ);

		D3DXMATRIX vRotX, vRotY, vRotTotal;
		D3DXMatrixRotationX(&vRotX, m_vAngle.x);
		D3DXMatrixRotationY(&vRotY, m_vAngle.y);

		vRotTotal = vRotX*vRotY;
		D3DXVec3TransformNormal(&m_vDir, &m_vLook, &vRotTotal);
		//업백터
		D3DXVec3TransformNormal(&m_vUp, &m_vUp, &vRotTotal);
		*_Up = m_vUp;

		memcpy(_vLook, &m_vDir, sizeof(D3DXVECTOR3));
		m_vPos = _vPos - m_vDir*m_fCameraDis;
		m_vDir = m_vPos + m_vDir;
	}
	m_tCenter = tPos;
	SetCursorPos(m_tCenter.x, m_tCenter.y);
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

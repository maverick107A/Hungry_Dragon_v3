#include "CaveCamera.h"
#include "BaseLand.h"

USING(Engine)

Engine::CCaveCamera::CCaveCamera(void)
{
}

Engine::CCaveCamera::~CCaveCamera(void)
{

}

HRESULT Engine::CCaveCamera::Ready_Camera(void)
{
	m_tCenter = { LONG(WINCX*0.5), LONG(WINCY*0.5) };
	SetCursorPos(m_tCenter.x, m_tCenter.y);
	return S_OK;
}

_int Engine::CCaveCamera::Update_Camera(const _float& fTimeDelta, LPDIRECT3DDEVICE9& pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY, CBaseLand* _pTerrain)
{
	if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		m_bShock = true;
		m_fShockAngle = 5.f;
	}

	Shock_Cam();

	switch (m_ePhase)
	{
	case Engine::CCaveCamera::PHASE_ZERO:
		Move_Phase01(pGraphicDev, _vPos, _fAngleX, _fAngleY);
		break;
	case Engine::CCaveCamera::PHASE_ONE:
		Move_Phase01(pGraphicDev, _vPos, _fAngleX, _fAngleY);
		break;
	case Engine::CCaveCamera::PHASE_TWO:
		Move_Phase2(pGraphicDev, _vPos, _fAngleX, _fAngleY);
		break;
	}

	//Move_Camera(pGraphicDev, _vPos, _fAngleX, _fAngleY);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &m_vPos, &m_vDir, &m_vUp);
	pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
}

void CCaveCamera::Move_Camera(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY)
{
	if (m_bLock)
		return;
	//POINT tPos = {};
	//GetCursorPos(&tPos);
	//m_vAfterAngle.y += (tPos.x - m_tCenter.x)*0.004f*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*0.004f*sinf(m_vAngle.z);
	//m_vAfterAngle.x += (tPos.y - m_tCenter.y)*0.004f*cosf(m_vAngle.z) + -(tPos.x - m_tCenter.x)*0.004f*sinf(m_vAngle.z);
	*_fAngleX = m_vAfterAngle.x;
	*_fAngleY = m_vAfterAngle.y;

	float DeltaAngleX = m_vAfterAngle.x - m_vAngle.x;
	float DeltaAngleY = m_vAfterAngle.y - m_vAngle.y;
	float DeltaAngleZ = m_vAfterAngle.z - m_vAngle.z + m_fShockAngle;

	m_vAngle.x += DeltaAngleX*0.05f;
	m_vAngle.y += DeltaAngleY*0.05f;
	m_vAngle.z += DeltaAngleZ*0.03f;

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

	//SetCursorPos(m_tCenter.x, m_tCenter.y);
	m_vPos = _vPos - m_vDir*m_fCameraDis;
	m_vDir = m_vPos + m_vDir;
}

void CCaveCamera::Move_Phase01(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, float * _fAngleX, float * _fAngleY)
{
	*_fAngleX = m_vAfterAngle.x;
	*_fAngleY = m_vAfterAngle.y;

	float DeltaAngleX = m_vAfterAngle.x - m_vAngle.x;
	float DeltaAngleY = m_vAfterAngle.y - m_vAngle.y;
	float DeltaAngleZ = m_fShockAngle;

	m_vAngle.x += DeltaAngleX*0.05f;
	m_vAngle.y += DeltaAngleY*0.05f;
	m_vAngle.z += DeltaAngleZ*0.03f;

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

	m_vPos = _vPos - m_vDir*m_fCameraDis;
	m_vDir = m_vPos + m_vDir;
}

void CCaveCamera::Move_Phase2(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, float * _fAngleX, float * _fAngleY)
{
	*_fAngleX = m_vAfterAngle.x;
	*_fAngleY = m_vAfterAngle.y;

	float DeltaAngleX = m_vAfterAngle.x - m_vAngle.x;
	float DeltaAngleY = m_vAfterAngle.y - m_vAngle.y;
	float DeltaAngleZ = m_vAfterAngle.z - m_vAngle.z + m_fShockAngle;

	m_vAngle.x += DeltaAngleX*0.07f;
	m_vAngle.y += DeltaAngleY*0.07f;
	m_vAngle.z += DeltaAngleZ*0.03f;

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

	//SetCursorPos(m_tCenter.x, m_tCenter.y);
	m_vPos = _vPos - m_vDir*m_fCameraDis;
	m_vDir = m_vPos + m_vDir;
}

void CCaveCamera::Switch_Phase(int _iPhase)
{
	switch (_iPhase)
	{
	case 0:
		m_vAfterAngle.x = 0.f;
		m_vAfterAngle.y = 0.f;
		m_vAfterAngle.z = 0.f;
		m_fCameraDis = 25.f;
		m_ePhase = PHASE::PHASE_ZERO;
		break;
	case 1:
		m_vAfterAngle.x = 0.f;
		m_vAfterAngle.y = -D3DX_PI*0.5f;
		m_vAfterAngle.z = 0.f;
		m_fCameraDis = 23.f;
		m_ePhase = PHASE::PHASE_ONE;
		break;
	case 2:
		m_vAfterAngle.x = 0.f;
		m_vAfterAngle.y = 0.f;
		m_vAfterAngle.z = 0.f;
		m_fCameraDis = 25.f;
		while (true)
		{
			if (abs(m_vAfterAngle.z - m_vAngle.z) < D3DX_PI)
				break;
			if (m_vAfterAngle.z > m_vAngle.z)
				m_vAngle.z += D3DX_PI*2.f;
			else
				m_vAngle.z -= D3DX_PI*2.f;
		}
		m_ePhase = PHASE::PHASE_TWO;
		break;
	}
}

CCaveCamera* Engine::CCaveCamera::Create(void)
{
	CCaveCamera*	pInstance = new CCaveCamera;

	if (FAILED(pInstance->Ready_Camera()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CCaveCamera::Free(void)
{

}

CComponent* Engine::CCaveCamera::Clone(void)
{
	return new CCaveCamera(*this);
}

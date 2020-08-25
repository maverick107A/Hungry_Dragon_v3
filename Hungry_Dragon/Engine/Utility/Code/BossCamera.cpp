#include "BossCamera.h"
#include "BaseLand.h"
#include "MonsterMain.h"
#include "Transform.h"

USING(Engine)

Engine::CBossCamera::CBossCamera(void)
{
}

Engine::CBossCamera::~CBossCamera(void)
{

}

HRESULT Engine::CBossCamera::Ready_Camera(void)
{
	m_tCenter = { LONG(WINCX*0.5), LONG(WINCY*0.5) };
	SetCursorPos(m_tCenter.x, m_tCenter.y);
	return S_OK;
}

_int CBossCamera::Update_Camera(const _float & _fTimeDelta, float * _fAngleX, float * _fAngleY, _vec3 * _vLook, _vec3 * _vUp, CPlayerMain* _pPlayer)
{
	//Shock_Cam();

	switch (m_ePhase)
	{
	case Engine::CBossCamera::PHASE_ZERO:
		Move_Phase01(_fAngleX, _fAngleY, _vLook, _vUp);
		break;
	case Engine::CBossCamera::PHASE_ONE:
		Move_Phase2(_fAngleX, _fAngleY, _vLook, _vUp, _pPlayer);
		break;
	}

	return 0;
}

void CBossCamera::Move_Camera(LPDIRECT3DDEVICE9 & pGraphicDev, _vec3 _vPos, float* _fAngleX, float* _fAngleY)
{
	if (m_bLock)
		return;
	POINT tPos = {};
	GetCursorPos(&tPos);
	m_vAfterAngle.y += (tPos.x - m_tCenter.x)*0.004f*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*0.004f*sinf(m_vAngle.z);
	m_vAfterAngle.x += (tPos.y - m_tCenter.y)*0.004f*cosf(m_vAngle.z) + -(tPos.x - m_tCenter.x)*0.004f*sinf(m_vAngle.z);
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

	SetCursorPos(m_tCenter.x, m_tCenter.y);
	m_vPos = _vPos - m_vDir*m_fCameraDis;
	m_vDir = m_vPos + m_vDir;
}

void CBossCamera::Move_Phase01(float * _fAngleX, float * _fAngleY, _vec3 * _vLook, _vec3 * _vUp)
{
	if (m_bLock)
		return;
	POINT tPos = {};
	GetCursorPos(&tPos);
	//짜증나는코드
	float fYPlus;
	if (cosf(m_vAfterAngle.x) > 0)
		fYPlus = ((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0003f;
	else
		fYPlus = -((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0003f;
	//끝
	m_vAfterAngle.y += fYPlus;
	m_vAfterAngle.x += ((tPos.y - m_tCenter.y)*cosf(m_vAngle.z) - (tPos.x - m_tCenter.x)*sinf(m_vAngle.z))*0.0003f;
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

void CBossCamera::Move_Phase2(float * _fAngleX, float * _fAngleY, _vec3 * _vLook, _vec3 * _vUp, CPlayerMain* _pPlayer)
{
	if (m_bLock)
		return;
	POINT tPos = {};
	GetCursorPos(&tPos);
	//짜증나는코드
	float fYPlus;
	if (cosf(m_vAfterAngle.x) > 0)
		fYPlus = ((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0003f;
	else
		fYPlus = -((tPos.x - m_tCenter.x)*cosf(m_vAngle.z) + (tPos.y - m_tCenter.y)*sinf(m_vAngle.z))*0.0003f;
	//끝
	m_vAfterAngle.y += fYPlus;
	m_vAfterAngle.x += ((tPos.y - m_tCenter.y)*cosf(m_vAngle.z) - (tPos.x - m_tCenter.x)*sinf(m_vAngle.z))*0.0003f;
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

	if (_pPlayer->Get_Boss())
	{	
		_vec3 vRight;
		m_vDir = _pPlayer->Get_Boss()->Get_Transform()->m_vInfo[Engine::INFO_POS] - _pPlayer->Get_Transform()->m_vInfo[Engine::INFO_POS];
		m_vDir.y += 1000.f;
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		D3DXVec3Cross(&vRight, &_vec3(0.f, 1.f, 0.f), &m_vDir);
		D3DXVec3Cross(&m_vUp, &m_vDir, &vRight);
		D3DXVec3Normalize(&m_vUp, &m_vUp);
	}
	
}

void CBossCamera::Switch_Phase(int _iPhase)
{
	switch (_iPhase)
	{
	case 0:
		m_ePhase = PHASE::PHASE_ZERO;
		break;
	case 1:
		m_ePhase = PHASE::PHASE_ONE;
		break;
	}
}

void CBossCamera::Swap_Phase()
{
	if (m_ePhase)
		m_ePhase = PHASE::PHASE_ZERO;
	else
		m_ePhase = PHASE::PHASE_ONE;
}

CBossCamera* Engine::CBossCamera::Create(void)
{
	CBossCamera*	pInstance = new CBossCamera;

	if (FAILED(pInstance->Ready_Camera()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CBossCamera::Free(void)
{

}

CComponent* Engine::CBossCamera::Clone(void)
{
	return new CBossCamera(*this);
}

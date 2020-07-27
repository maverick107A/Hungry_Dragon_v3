#include "PlayerState.h"

USING(Engine)

Engine::CPlayerState::CPlayerState(void)
	: m_vScale(1.f, 1.f, 1.f)
	, m_vAngle(0.f, 0.f, 0.f)
{
	
}

Engine::CPlayerState::CPlayerState(const CPlayerState& rhs)
	: m_vScale(rhs.m_vScale)
	, m_vAngle(rhs.m_vAngle)	
{

}

Engine::CPlayerState::~CPlayerState(void)
{

}

HRESULT Engine::CPlayerState::Ready_State(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	return S_OK;
}

_int Engine::CPlayerState::Update_State(const _float& fTimeDelta)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_POS; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	// 크기 변환
	for (_uint i = 0; i < INFO_POS; ++i)
	{
		D3DXVec3Normalize(&m_vInfo[i], &m_vInfo[i]);
		m_vInfo[i] *= *(((_float*)&m_vScale) + i);
	}

	// 회전
	_matrix		matRot[ROT_END];
	D3DXMatrixRotationX(&matRot[ROT_X], m_vAngle.x);
	D3DXMatrixRotationY(&matRot[ROT_Y], m_vAngle.y);
	D3DXMatrixRotationZ(&matRot[ROT_Z], m_vAngle.z);

	for (_uint i = 0; i < INFO_POS; ++i)
	{
		for (_uint j = 0; j < ROT_END; ++j)
		{
			D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRot[j]);
		}
	}

	for(_uint i = 0; i < INFO_END ;++i)
		memcpy(&m_matWorld.m[i][0], &m_vInfo[i], sizeof(_vec3));

	return 0;
}

CPlayerState* Engine::CPlayerState::Create(void)
{
	CPlayerState*	pInstance = new CPlayerState;

	if (FAILED(pInstance->Ready_State()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CPlayerState::Free(void)
{

}

CComponent* Engine::CPlayerState::Clone(void)
{
	return new CPlayerState(*this);
}

void Engine::CPlayerState::Set_State(LPDIRECT3DDEVICE9& pGraphicDev)
{
	if (nullptr == pGraphicDev)
		return;

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void Engine::CPlayerState::Get_Info(INFO eType, _vec3* pInfo)
{
	memcpy(pInfo, &m_matWorld.m[eType][0], sizeof(_vec3));
}

void Engine::CPlayerState::Rotation(ROTATION eType, const _float& fAngle)
{
	*(((_float*)&m_vAngle) + eType) += fAngle;
}

const _matrix * CPlayerState::Compute_LookAtTarget(const _vec3 * pTargetPos)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	_vec3		vAxis, vUp;
	_matrix		matRotAxis;

	return D3DXMatrixRotationAxis(&matRotAxis, 
								D3DXVec3Cross(&vAxis, &m_vInfo[INFO_UP], &vDir),
								acosf(D3DXVec3Dot(D3DXVec3Normalize(&vUp, &m_vInfo[INFO_UP]),
												  D3DXVec3Normalize(&vDir, &vDir))));
}

void CPlayerState::Chase_Target(const _vec3 * pTargetPos, const _float & fSpeed)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;

	_matrix		matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	matRot = *Compute_LookAtTarget(pTargetPos);
	D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);

	m_matWorld = matScale * matRot * matTrans;
}


#include "Transform.h"

USING(Engine)

Engine::CTransform::CTransform(void)
	: m_vScale(1.f, 1.f, 1.f)
	, m_vAngle(0.f, 0.f, 0.f)
	, m_vInCamPos(0.f,0.f,0.f)
{
	
}

Engine::CTransform::CTransform(const CTransform& rhs)
	: m_vScale(rhs.m_vScale)
	, m_vAngle(rhs.m_vAngle)	
{

}

Engine::CTransform::~CTransform(void)
{

}

void CTransform::Add_Trans(const _vec3 * const pDir) {
	m_vInfo[INFO_POS] += *pDir;
}

void CTransform::Add_Trans(const _float * const _x, const _float * const _y, const _float * const _z) {
	_vec3 moveVec = (_x,_y,_z);
	m_vInfo[INFO_POS] += moveVec;
}

void CTransform::Set_Trans(const _vec3 * const newPos) {
	_vec3		vPos = *newPos;
	m_vInfo[INFO_POS] = vPos;
}

void CTransform::Set_Scale(const _float _Scale)
{
	m_vScale.x = _Scale;
	m_vScale.y = _Scale;
	m_vScale.z = _Scale;

}


void CTransform::Set_Add_Scale(const _float _Scale)
{
	m_vScale.x += _Scale;
	m_vScale.y += _Scale;
	m_vScale.z += _Scale;

}

void CTransform::Set_World(_matrix * _matWorld)
{
	memcpy(&m_matWorld, _matWorld,sizeof(_matrix));
}

HRESULT Engine::CTransform::Ready_Transform(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	return S_OK;
}

_int Engine::CTransform::Update_Component(const _float& fTimeDelta)
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


	//추가이동
	for (int i = 0; i < 3; ++i)
	{
		m_matWorld.m[INFO_POS][i] += m_vInCamPos[i];
	}
	//여기까지
	//이동기 관련
	//m_vInfo[INFO_POS] += m_vInCamPos*0.1f;
	m_vInCamPos *= 0.9f;
	return 0;
}

CTransform* Engine::CTransform::Create(void)
{
	CTransform*	pInstance = new CTransform;

	if (FAILED(pInstance->Ready_Transform()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CTransform::Free(void)
{

}

CComponent* Engine::CTransform::Clone(void)
{
	return new CTransform(*this);
}

void Engine::CTransform::Set_Transform(LPDIRECT3DDEVICE9& pGraphicDev)
{
	if (nullptr == pGraphicDev)
		return;

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void Engine::CTransform::Get_Info(INFO eType, _vec3* pInfo)
{
	memcpy(pInfo, &m_matWorld.m[eType][0], sizeof(_vec3));
}

_matrix CTransform::Get_World()
{
	return m_matWorld;
}

void Engine::CTransform::Rotation(ROTATION eType, const _float& fAngle)
{
	*(((_float*)&m_vAngle) + eType) += fAngle;
}

const _matrix * CTransform::Compute_LookAtTarget(const _vec3 * pTargetPos)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	_vec3		vAxis, vUp;
	_matrix		matRotAxis;

	return D3DXMatrixRotationAxis(&matRotAxis, 
								D3DXVec3Cross(&vAxis, &m_vInfo[INFO_UP], &vDir),
								acosf(D3DXVec3Dot(D3DXVec3Normalize(&vUp, &m_vInfo[INFO_UP]),
												  D3DXVec3Normalize(&vDir, &vDir))));
}

void CTransform::Chase_Fly_Target(const _vec3 * pTargetPos, const _float & fSpeed)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];
 	
	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;

	//_matrix		matScale, matRot, matTrans;

	//D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	//matRot = *Compute_LookAtTarget(pTargetPos);
	//D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);
	//
	//m_matWorld = matScale * matRot * matTrans;
}

void CTransform::Chase_Target(const _vec3 * pTargetPos, const _float & fSpeed)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];
	vDir.y = 0;
	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;
}

void CTransform::Chase_RotaionTarget(const _vec3 * pTargetPos)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * 0.1f;

	_matrix		matScale, matRot, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	matRot = *Compute_LookAtTarget(pTargetPos);
	D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);

	m_matWorld = matScale * matRot * matTrans;
}

void CTransform::Dir_Fly(const _vec3 * pTargetPos, const _float & fSpeed)
{
	_vec3		vDir = *pTargetPos;

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;

	

}
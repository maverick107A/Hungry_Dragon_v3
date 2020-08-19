#include "AnimationTransform.h"

USING(Engine)

Engine::CAnimationTransform::CAnimationTransform(void)
{
	
}

CAnimationTransform::CAnimationTransform(const CAnimationTransform & rhs)
{
}


Engine::CAnimationTransform::~CAnimationTransform(void)
{

}

HRESULT Engine::CAnimationTransform::Ready_Transform(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	return S_OK;
}

_int Engine::CAnimationTransform::Update_Component(const _float& fTimeDelta)
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

CAnimationTransform* Engine::CAnimationTransform::Create(void)
{
	CAnimationTransform*	pInstance = new CAnimationTransform;

	if (FAILED(pInstance->Ready_Transform()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void Engine::CAnimationTransform::Free(void)
{

}

CComponent* Engine::CAnimationTransform::Clone(void)
{
	return new CAnimationTransform(*this);
}

void Engine::CAnimationTransform::Set_Transform(LPDIRECT3DDEVICE9& pGraphicDev)
{
	if (nullptr == pGraphicDev)
		return;

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void Engine::CAnimationTransform::Rotation(ROTATION eType, const _float& fAngle)
{
	*(((_float*)&m_vAngle) + eType) += fAngle;
}

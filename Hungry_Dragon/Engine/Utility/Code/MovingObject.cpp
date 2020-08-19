#include "MovingObject.h"

USING(Engine)

CMovingObject::CMovingObject(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMovingObject::~CMovingObject(void)
{
}

HRESULT CMovingObject::Ready_Object(void)
{
	return S_OK;
}

void CMovingObject::Initialize_Object(void)
{
}

int CMovingObject::Update_Object(const float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	MOVEMENT nowMovement, nextMovement;
	_matrix worldPosMatrix;
	if (m_pAnimator != nullptr)
	{
		for (size_t i = 0; i < m_pMeshTransform.size(); ++i)
		{
			float nowFrame = m_pAnimator->Get_NowFrame();

			nowMovement = m_pAnimator->Get_Movement(i, (int)nowFrame);
			
			if (nowFrame >= m_pAnimator->Get_TotalMaxFrame())	//끝 프레임이면 처음 프레임을 다음 프레임으로 한다.
			{
				nextMovement = m_pAnimator->Get_Movement(i, 0);
			}
			else
			{
				nextMovement = m_pAnimator->Get_Movement(i, (int)nowFrame + 1);
			}

			worldPosMatrix = m_pMeshTransform[i]->m_matWorld;

			//여기서 건네주면 됨.
		}
	}
	return 0;
}

void CMovingObject::LateUpdate_Object(const _float & fTimeDelta)
{
	CGameObject::LateUpdate_Object(fTimeDelta);
}

void CMovingObject::Render_Object(void)
{
	if (m_pAnimator != nullptr)
	{
		for (size_t i = 0; i < m_pMeshTransform.size(); ++i)
		{
			m_pMeshTransform[i]->Set_Transform(m_pGraphicDev);
			m_pMeshArray[i]->Render_Buffer();
		}
	}
}

CMovingObject * CMovingObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return new CMovingObject(pGraphicDev);
}

void CMovingObject::Free(void)
{
	CGameObject::Free();
}

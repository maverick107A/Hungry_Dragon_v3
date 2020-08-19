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
	return 0;
}

void CMovingObject::LateUpdate_Object(const _float & fTimeDelta)
{
	CGameObject::LateUpdate_Object(fTimeDelta);
}

void CMovingObject::Render_Object(void)
{
	
}

CMovingObject * CMovingObject::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return new CMovingObject(pGraphicDev);
}

void CMovingObject::Free(void)
{
}

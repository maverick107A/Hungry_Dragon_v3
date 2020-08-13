#include "PlayerMain.h"


Engine::CPlayerMain::CPlayerMain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	//, m_vLook(0.f, 0.f, 0.f)
{

}

Engine::CPlayerMain::~CPlayerMain(void)
{

}

void Engine::CPlayerMain::Free(void)
{
	Engine::CGameObject::Free();
}

Engine::CPlayerMain* Engine::CPlayerMain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerMain*		pInstance = new CPlayerMain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);
 
	return pInstance;
}
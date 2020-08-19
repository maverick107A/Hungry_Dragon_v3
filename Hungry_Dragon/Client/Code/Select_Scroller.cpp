#include "stdafx.h"
#include "Select_Scroller.h"

#include "Export_Function.h"
#include "Select_Map.h"

USING(Engine)

CSelect_Scroller::CSelect_Scroller(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev) {

}

CSelect_Scroller::~CSelect_Scroller(void) {

}

HRESULT CSelect_Scroller::Ready_Object(void) {
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	for (int i = 0; i < 10; ++i)
	{
		m_arrSelect[i] = CSelect_Map::Create(m_pGraphicDev);
		m_arrSelect[i]->Set_MapNum(i);
		m_arrSelect[i]->Set_LerpX(0.6f * i);
		m_arrSelect[i]->Set_PosX(0.6f * i);
	}
	m_arrSelect[0]->Set_Focus(true);

	return S_OK;
}

int CSelect_Scroller::Update_Object(const float& fTimeDelta) {

	
	Engine::CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(Engine::RENDER_UI, this);

	for(auto& pObj : m_arrSelect)
	{
		pObj->Update_Object(fTimeDelta);
	}

	return 0;
}

void CSelect_Scroller::Render_Object(void) {
	
	for (auto& pObj : m_arrSelect)
	{
		pObj->Render_Object();
	}
}

void CSelect_Scroller::Set_Focus(int _iFocus)
{
	for (int i = 0; i < 10; ++i)
	{
		m_arrSelect[i]->Set_LerpX(0.6f * (i- _iFocus));
		m_arrSelect[i]->Set_Focus(false);
	}
	m_arrSelect[_iFocus]->Set_Focus(true);
}

void CSelect_Scroller::Free(void) {
	Engine::CGameObject::Free();
	for (auto& pObj : m_arrSelect)
	{
		Safe_Release(pObj);
	}
}


HRESULT CSelect_Scroller::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	

	return S_OK;
}

CSelect_Scroller* CSelect_Scroller::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	CSelect_Scroller*		pInstance = new CSelect_Scroller(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

